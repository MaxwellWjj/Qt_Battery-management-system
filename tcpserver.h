#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QtNetwork>
#include <QHostAddress>

class TcpClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = 0);

private:
    QString ip;
    int port;

public:
    void setIP(const QString &ip);
    QString getIP()const;

    void setPort(int port);
    int getPort()const;

private slots:
    void socketReadData();

signals:
    void sendData(const QString &ip, int port, const QString &data);
    void receiveData(QByteArray data);

public slots:
    void socketsendData(const QString &data);

};

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);

    QString get_localmachine_ip();

private:
    QList<TcpClient *> clients;

protected:
    void incomingConnection(qintptr handle);
private slots:
    void disconnected();

signals:
    void sendData(const QString &ip, int port, const QString &data);
    void receiveData(QByteArray data);

    void clientConnected(const QString &ip, int port);
    void clientDisconnected(const QString &ip, int port);

public slots:
    //启动服务
    bool start(quint16 port);
    //停止服务
    void stop();

    //指定连接发送数据
    void writeData(const QString &ip, int port, const QString &data);
    //对所有连接发送数据
    void writeData(const QString &data);

};

#endif // TCPSERVER_H
