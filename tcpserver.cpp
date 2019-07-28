#include "tcpserver.h"
#include "quiwidget.h"
#include <QDebug>

TcpClient::TcpClient(QObject *parent) :  QTcpSocket(parent)
{
    ip = "127.0.0.1";
    port = 6000;

    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(deleteLater()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    connect(this, SIGNAL(readyRead()), this, SLOT(socketReadData()));
}

void TcpClient::setIP(const QString &ip)
{
    this->ip = ip;
}

QString TcpClient::getIP() const
{
    return this->ip;
}

void TcpClient::setPort(int port)
{
    this->port = port;
}

int TcpClient::getPort() const
{
    return this->port;
}

void TcpClient::socketReadData()
{
    QByteArray data = this->readAll();
    if (data.length() <= 0) {
        return;
    }

    emit receiveData(data);

}

void TcpClient::socketsendData(const QString &data)
{
    QByteArray buffer;
    buffer = QUIHelper::asciiStrToByteArray(data);

    this->write(buffer);
    emit sendData(ip, port, data);
}

TcpServer::TcpServer(QObject *parent) : QTcpServer(parent)
{
}

void TcpServer::incomingConnection(qintptr handle)
{
    TcpClient *client = new TcpClient(this);
    client->setSocketDescriptor(handle);
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(client, SIGNAL(sendData(QString, int, QString)), this, SIGNAL(sendData(QString, int, QString)));
    connect(client, SIGNAL(receiveData(QByteArray)), this, SIGNAL(receiveData(QByteArray)));

    QString ip = client->peerAddress().toString();
    int port = client->peerPort();
    client->setIP(ip);
    client->setPort(port);
    emit clientConnected(ip, port);

    qDebug()<<"get one"<<endl;
    //连接后加入链表
    clients.append(client);
}

void TcpServer::disconnected()
{
    TcpClient *client = (TcpClient *)sender();
    QString ip = client->getIP();
    int port = client->getPort();
    emit clientDisconnected(ip, port);
    emit sendData(ip, port, "客户端下线");

    //断开连接后从链表中移除
    clients.removeOne(client);
}

bool TcpServer::start(quint16 port)
{
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
    bool ok = listen(QHostAddress::AnyIPv4,port);
#else
    bool ok = listen(QHostAddress::Any,port);
#endif

    return ok;
}

void TcpServer::stop()
{
    foreach (TcpClient *client, clients) {
        client->disconnectFromHost();
    }

    this->close();
}

QString TcpServer::get_localmachine_ip(){
    QString ipAddress;
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
        // use the first non-localhost IPv4 address
        for (int i = 0; i < ipAddressesList.size(); ++i) {
            if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
                ipAddress = ipAddressesList.at(i).toString();
                break;
            }
        }
        // if we did not find one, use IPv4 localhost
        if (ipAddress.isEmpty())
            ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
        return ipAddress;
}

void TcpServer::writeData(const QString &ip, int port, const QString &data)
{
    foreach (TcpClient *client, clients) {
        if (client->peerAddress().toString() == ip && client->peerPort() == port) {
            client->socketsendData(data);
            break;
        }
    }
}

void TcpServer::writeData(const QString &data)
{
    foreach (TcpClient *client, clients) {
        client->socketsendData(data);
    }
}
