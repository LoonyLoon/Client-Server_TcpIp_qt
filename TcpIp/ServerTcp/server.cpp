#include "server.h"
#include "ui_server.h"

Server::Server(int nPort, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

    m_TcpServer = new QTcpServer(this);

    //Start server
    if (!m_TcpServer->listen(QHostAddress::Any, nPort)) {

        QMessageBox::critical(0,"Error",
                              QString("Unable to start the server: %1").arg(m_TcpServer->errorString()));

        m_TcpServer->close();
        return;
    }


    connect(m_TcpServer, SIGNAL(newConnection()),
            this, SLOT(slotNewConnection()));

}

Server::~Server()
{
    delete ui;
}

void Server::slotRead()
{
    QDataStream in(m_TcpSocket);
    in.setVersion(QDataStream::Qt_5_12);
    if (m_blockSize == 0) {

        if (m_TcpSocket->bytesAvailable() < sizeof(qint64))
            return;

        in >> m_blockSize;
    }

    if (m_TcpSocket->bytesAvailable() < m_blockSize)
        return;

    QString fileName;
    in >> fileName;

    QByteArray packet = m_TcpSocket->readAll();
    QFile target("C:/" + fileName);

    if (!target.open(QIODevice::WriteOnly)) {
        return;
    }

    target.write(packet);
    target.close();

    m_blockSize = 0;
}

void Server::slotNewConnection()
{

    QMessageBox::information(0,"Info","Status connect - succsesfull");

    m_TcpSocket = m_TcpServer->nextPendingConnection();

    connect(m_TcpSocket, SIGNAL(disconnected()),
            m_TcpSocket, SLOT(deleteLater()));

    connect(m_TcpSocket, SIGNAL(readyRead()),
            this, SLOT(slotRead()));

}

