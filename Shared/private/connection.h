#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QHostAddress>
#include <QTimerEvent>

static const int MaxBufferSize = 1024000;

class Connection : public QTcpSocket
{
    Q_OBJECT
public:
    // Connection states
    // WaitingForGreeting -> ReadingGreeting -> ReadyForUse
    enum ConnectionState
    {
        WaitingForGreeting,
        ReadingGreeting,
        ReadyForUse
    };

    // Supported datatypes
    enum DataType
    {
        PlainText,
        Ping,
        Pong,
        Greeting,
        Undefined
    };

    /**
     * @brief Connection Create a new TcpSocket
     * @param username Username to be sent in the greeting
     * @param parent
     */
    explicit Connection(QString username, QObject *parent = 0);

    /**
     * @brief getName Get foreign username
     * @return
     */
    QString getName() const;

    /**
     * @brief sendMessage Send a message. Does not check the connection's state.
     * @param message
     * @return
     */
    bool sendMessage(const QString &message);

    /**
     * @brief Connection::getGreetingMessage Get the username that was sent to the other end
     * @return
     */
    QString getGreetingMessage() const;

signals:
    /**
     * @brief readyForUse Emitted when greetings have been exchanged
     */
    void readyForUse();

    /**
     * @brief newMessage Emitted when a new message is received through the protocol
     * @param from
     * @param message
     */
    void newMessage(const QString &from, const QString &message);

protected:
    /**
     * @brief timerEvent Aborts a data transfer if the transfer timer expires
     * @param timerEvent
     */
    void timerEvent(QTimerEvent *timerEvent);

private slots:
    /**
     * @brief processReadyRead Process the ready read signal. Handles the Connection state and receiving the username.
     */
    void processReadyRead();

    /**
     * @brief sendPing Send the keep-alive message
     */
    void sendPing();

    /**
     * @brief sendGreetingMessage Sends the greeting message
     */
    void sendGreetingMessage();

private:
    /**
     * @brief readDataIntoBuffer Reads data into buffer
     * @param maxSize
     * @return Number of bytes read
     */
    int readDataIntoBuffer(int maxSize = MaxBufferSize);

    /**
     * @brief dataLengthForCurrentDataType Get the number of bytes that the full message will be from the protocol
     * @return Number of bytes
     */
    int dataLengthForCurrentDataType();

    /**
     * @brief readProtocolHeader Read the datatype and size from the message
     * @return
     */
    bool readProtocolHeader();

    /**
     * @brief hasEnoughData Return false if full message hasn't been read, or there are no bytes left, true otherwise
     * @return
     */
    bool hasEnoughData();

    /**
     * @brief processData Process datatype, and emit newMessage, send keep-alive, or restart the pong timer. Resets datatype afterwards.
     */
    void processData();

    // Message to send in greeting, this is "your" username
    QString greetingMessage;

    // Foreign username
    QString username;

    // Keep-alive timer
    QTimer pingTimer;
    QTime pongTime;

    // Buffer for data
    QByteArray buffer;

    // Current date of the connection
    ConnectionState state;

    // Currently processing datatype
    DataType currentDataType;

    // Length of the current message
    int numBytesForCurrentDataType;

    // Kill timer for transfers
    int transferTimerId;

    // Sent greeting status
    bool isGreetingMessageSent;
};

#endif // CONNECTION_H
