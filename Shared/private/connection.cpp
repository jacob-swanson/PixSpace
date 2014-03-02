#include "connection.h"

static const int TransferTimeout = 30 * 1000;
static const int PongTimeout = 60 * 1000;
static const int PingInterval = 5 * 1000;
static const char SeparatorToken = ' ';

Connection::Connection(QString username, QObject *parent) :
    QTcpSocket(parent)
{
    this->greetingMessage = username;
    this->username = "unknown";
    this->state = WaitingForGreeting;
    this->currentDataType = Undefined;
    this->numBytesForCurrentDataType = -1;
    this->transferTimerId = 0;
    this->isGreetingMessageSent = false;
    this->pingTimer.setInterval(PingInterval);

    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
    QObject::connect(this, SIGNAL(disconnected()), &pingTimer, SLOT(stop()));
    QObject::connect(&pingTimer, SIGNAL(timeout()), this, SLOT(sendPing()));
    QObject::connect(this, SIGNAL(connected()), this, SLOT(sendGreetingMessage()));
}

QString Connection::getName() const
{
    // Get foreign username
    return this->username;
}

bool Connection::sendMessage(const QString &message)
{
    // Send a message
    // TODO: Check for connection state (maybe)
    if (message.isEmpty())
    {
        return false;
    }

    QByteArray msg = message.toUtf8();
    QByteArray data = "MESSAGE " + QByteArray::number(msg.size()) + ' ' + msg;
    return this->write(data) == data.size();
}

void Connection::timerEvent(QTimerEvent *timerEvent)
{
    // Kill the current transfer if it's taking too long
    if (timerEvent->timerId() == transferTimerId)
    {
        this->abort();
        killTimer(this->transferTimerId);
        this->transferTimerId = 0;
    }
}

void Connection::processReadyRead()
{
    // Process the datatype depending on the current state of the Connection
    if (this->state == WaitingForGreeting)
    {
        if (!this->readProtocolHeader())
        {
            return;
        }

        // Ignore everything until Greeting is received
        if (this->currentDataType != Greeting)
        {
            this->abort();
            return;
        }
        // Set to next state
        this->state = ReadingGreeting;
    }

    // Process the greeting
    if (this->state == ReadingGreeting)
    {
        // All data received?
        if (!this->hasEnoughData())
        {
            return;
        }

        // Read into our buffer
        this->buffer = this->read(this->numBytesForCurrentDataType);
        if (buffer.size() != this->numBytesForCurrentDataType)
        {
            this->abort();
            return;
        }

        // Set username to <NAME>@<IP>:<PORT>
        username = QString(buffer) + '@' + this->peerAddress().toString() + ":" + QString::number(this->peerPort());
        this->currentDataType = Undefined;
        this->numBytesForCurrentDataType = 0;
        this->buffer.clear();

        // Check QTcpSocket to see if it's ready
        if (!this->isValid())
        {
            this->abort();
            return;
        }

        // Send the greeting if it hasn't already been sent
        if (!this->isGreetingMessageSent)
        {
            this->sendGreetingMessage();
        }

        // Start the keep-alive stuff
        this->pingTimer.start();
        this->pongTime.start();

        // Put Connection into ready state
        this->state = ReadyForUse;

        // Let everyone else know
        emit readyForUse();
    }

    // Data processing loop
    do {
        // Read the datatype first
        if (this->currentDataType == Undefined)
        {
            if (!this->readProtocolHeader())
            {
                return;
            }
        }

        // Read the data once it has all been received
        if (!this->hasEnoughData())
        {
            return;
        }

        this->processData();
    } while (this->bytesAvailable() > 0);
}

void Connection::sendPing()
{
    // Send ping
    if (this->pongTime.elapsed() > PongTimeout)
    {
        this->abort();
        return;
    }

    this->write("PING 1 p");
}

void Connection::sendGreetingMessage()
{
    // Send the greeting message
    QByteArray greeting = this->greetingMessage.toUtf8();
    QByteArray data = "GREETING " + QByteArray::number(greeting.size()) + ' ' + greeting;
    if (this->write(data) == data.size())
    {
        this->isGreetingMessageSent = true;
    }
}

int Connection::readDataIntoBuffer(int maxSize)
{
    if (maxSize > MaxBufferSize)
    {
        return 0;
    }

    int numBytesBeforeRead = buffer.size();
    if (numBytesBeforeRead == MaxBufferSize)
    {
        this->abort();
        return 0;
    }

    // Read received data into our buffer
    while (this->bytesAvailable() > 0 && this->buffer.size() < maxSize)
    {
        buffer.append(this->read(1));
        if (buffer.endsWith(SeparatorToken))
            break;
    }

    return this->buffer.size() - numBytesBeforeRead;
}

int Connection::dataLengthForCurrentDataType()
{
    // Checks for data
    if (this->bytesAvailable() <= 0 || this->readDataIntoBuffer() <= 0 || !this->buffer.endsWith(SeparatorToken))
    {
        return 0;
    }

    // Get the data length from the received message
    this->buffer.chop(1);
    int number = this->buffer.toInt();
    this->buffer.clear();
    return number;
}

bool Connection::readProtocolHeader()
{
    // Check transfer timer
    if (this->transferTimerId)
    {
        killTimer(this->transferTimerId);
        this->transferTimerId = 0;
    }

    // Read datatype into buffer
    if (this->readDataIntoBuffer() <= 0)
    {
        this->transferTimerId = this->startTimer(TransferTimeout);
        return false;
    }

    // Process the datatype in the buffer
    if (this->buffer == "PING ")
    {
        this->currentDataType = Ping;
    }
    else if (this->buffer == "PONG ")
    {
        this->currentDataType = Pong;
    }
    else if (this->buffer == "MESSAGE ")
    {
        this->currentDataType = PlainText;
    }
    else if (this->buffer == "GREETING ")
    {
        this->currentDataType = Greeting;
    }
    else
    {
        // Bad message was received
        this->currentDataType = Undefined;
        this->abort();
        return false;
    }

    // Move datatype out of the buffer for the rest of the message
    this->buffer.clear();
    this->numBytesForCurrentDataType = this->dataLengthForCurrentDataType();

    return true;
}

bool Connection::hasEnoughData()
{
    // Check transfer
    if (this->transferTimerId)
    {
        QObject::killTimer(this->transferTimerId);
        this->transferTimerId = 0;
    }

    // numBytesForCurrentDataType has not been set yet
    if (this->numBytesForCurrentDataType <= 0)
    {
        this->numBytesForCurrentDataType = this->dataLengthForCurrentDataType();
    }

    // Recieved part of a message
    if (this->bytesAvailable() < this->numBytesForCurrentDataType || this->numBytesForCurrentDataType <= 0)
    {
        this->transferTimerId = this->startTimer(TransferTimeout);
        return false;
    }

    return true;
}

void Connection::processData()
{
    // Only process when the full message is received
    this->buffer = this->read(this->numBytesForCurrentDataType);
    if (this->buffer.size() != this->numBytesForCurrentDataType)
    {
        this->abort();
        return;
    }

    // Handle the datatype received
    switch (this->currentDataType)
    {
    case PlainText:
        emit newMessage(this->username, QString::fromUtf8(this->buffer));
        break;
    case Ping:
        this->write("PONG 1 p");
        break;
    case Pong:
        this->pongTime.restart();
        break;
    default:
        break;
    }

    // Reset the Connection
    this->currentDataType = Undefined;
    this->numBytesForCurrentDataType = 0;
    this->buffer.clear();
}
