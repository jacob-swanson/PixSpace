#include "connection.h"

static const int TransferTimeout = 30 * 1000;
static const int PongTimeout = 60 * 1000;
static const int PingInterval = 5 * 1000;
static const char SeparatorToken = ' ';

Connection::Connection(QObject *parent) :
    QTcpSocket(parent)
{
    // TODO: Get greeting from config
    this->greetingMessage = "PIXSPACE 0.1";
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
    return this->username;
}

void Connection::setGreetingMessage(const QString &message)
{
    this->greetingMessage = message;
}

bool Connection::sendMessage(const QString &message)
{
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
    if (timerEvent->timerId() == transferTimerId)
    {
        this->abort();
        killTimer(this->transferTimerId);
        this->transferTimerId = 0;
    }
}

void Connection::processReadyRead()
{
    if (this->state == WaitingForGreeting)
    {
        if (!this->readProtocolHeader())
        {
            return;
        }

        if (this->currentDataType != Greeting)
        {
            this->abort();
            return;
        }
        this->state = ReadingGreeting;
    }

    if (this->state == ReadingGreeting)
    {
        if (!this->hasEnoughData())
        {
            return;
        }

        this->buffer = read(this->numBytesForCurrentDataType);
        if (buffer.size() != this->numBytesForCurrentDataType)
        {
            this->abort();
            return;
        }

        username = QString(buffer) + '@' + this->peerAddress().toString() + ":" + QString::number(this->peerPort());
        this->currentDataType = Undefined;
        this->numBytesForCurrentDataType = 0;
        this->buffer.clear();

        if (!this->isValid())
        {
            this->abort();
            return;
        }

        if (!this->isGreetingMessageSent)
        {
            this->sendGreetingMessage();
        }

        this->pingTimer.start();
        this->pongTime.start();
        this->state = ReadyForUse;
        emit readyForUse();
    }

    do {
        if (this->currentDataType == Undefined)
        {
            if (!this->readProtocolHeader())
            {
                return;
            }
        }

        if (!this->hasEnoughData())
        {
            return;
        }

        this->processData();
    } while (this->bytesAvailable() > 0);
}

void Connection::sendPing()
{
    if (this->pongTime.elapsed() > PongTimeout)
    {
        this->abort();
        return;
    }

    this->write("PING 1 p");
}

void Connection::sendGreetingMessage()
{
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
    if (this->bytesAvailable() <= 0 || this->readDataIntoBuffer() <= 0 || !this->buffer.endsWith(SeparatorToken))
    {
        return 0;
    }

    this->buffer.chop(1);
    int number = this->buffer.toInt();
    this->buffer.clear();
    return number;
}

bool Connection::readProtocolHeader()
{
    if (this->transferTimerId)
    {
        killTimer(this->transferTimerId);
        this->transferTimerId = 0;
    }

    if (this->readDataIntoBuffer() <= 0)
    {
        this->transferTimerId = this->startTimer(TransferTimeout);
        return false;
    }

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
        this->currentDataType = Undefined;
        this->abort();
        return false;
    }

    this->buffer.clear();
    this->numBytesForCurrentDataType = this->dataLengthForCurrentDataType();
    return true;
}

bool Connection::hasEnoughData()
{
    if (this->transferTimerId)
    {
        QObject::killTimer(this->transferTimerId);
        this->transferTimerId = 0;
    }

    if (this->numBytesForCurrentDataType <= 0)
    {
        this->numBytesForCurrentDataType = this->dataLengthForCurrentDataType();
    }

    if (this->bytesAvailable() < this->numBytesForCurrentDataType || this->numBytesForCurrentDataType <= 0)
    {
        this->transferTimerId = this->startTimer(TransferTimeout);
        return false;
    }

    return true;
}

void Connection::processData()
{
    this->buffer = this->read(this->numBytesForCurrentDataType);
    if (this->buffer.size() != this->numBytesForCurrentDataType)
    {
        this->abort();
        return;
    }

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

    this->currentDataType = Undefined;
    this->numBytesForCurrentDataType = 0;
    this->buffer.clear();
}
