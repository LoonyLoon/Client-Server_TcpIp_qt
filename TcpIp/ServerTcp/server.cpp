#include "server.h"
#include "ui_server.h"

Server::Server(int nPort, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

    mTcpServer = new QTcpServer(this);
       if (!mTcpServer->listen(QHostAddress::Any, nPort))
       {
           QMessageBox::critical(0,"Server Error",
                                 "Unable to start the server:"
                                 + mTcpServer->errorString()
                                );
           mTcpServer->close();
           return;
       }
       connect(mTcpServer, SIGNAL(newConnection()),
               this,         SLOT(slotNewConnection())
              );




}

Server::~Server()
{
    delete ui;
}

void Server::slotRead()
{


    QDataStream in(mTcpSocket);
    in.setVersion(QDataStream::Qt_5_12);
    if (m_blockSize == 0) {
            if (mTcpSocket->bytesAvailable() < sizeof(quint32))
            return;
            in >> m_blockSize;
        }
        if (mTcpSocket->bytesAvailable() < m_blockSize)
            return;


        QString fileName;
        // get sending file name
        in >> fileName;
        qDebug()<<fileName;
        QByteArray line = mTcpSocket->readAll();
        QByteArray ll;
        ll.append(line);
        qDebug()<<"LINE SIZE"<<ll.size();

        QFile target("C:/" + fileName);



        if (!target.open(QIODevice::WriteOnly)) {
            qDebug() << "Can't open file for written";
            return;
        }
        target.write(ll);
        target.close();

}

void Server::slotNewConnection()
{

    QMessageBox::information(0,"Info","Status connect - succsesfull");

            mTcpSocket = mTcpServer->nextPendingConnection();

       connect(mTcpSocket, SIGNAL(disconnected()),
               mTcpSocket, SLOT(deleteLater()));

       connect(mTcpSocket, SIGNAL(readyRead()),
               this, SLOT(slotRead()));

//       connect(mTcpSocket,&QTcpSocket::readyRead,this,
//               &Server::slotRead);

      // sendToClient(pClientSocket, "Server Response: Connected!");


}

