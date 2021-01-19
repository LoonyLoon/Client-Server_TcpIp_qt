#include "client.h"
#include "ui_client.h"

#include <QDebug>

Client::Client(const QString& strHost, int nPort, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{

    ui->setupUi(this);

    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(strHost,nPort);

    m_port = nPort;
    m_Host = strHost;

    send  = new QThread();

    connect(m_pTcpSocket, SIGNAL(connected()),
            this,SLOT(slotConnected()));

    //Потоки
    //Поток передачи данных
    connect(send,SIGNAL(started()),
            this,SLOT(slotSendToServer()));

    connect(send,SIGNAL(finished()),
                        this,SLOT(slotSendToServer()));

}

Client::~Client()
{
    delete ui;
}

void Client::on_ChangeFile_clicked()
{
    m_PathFile = QFileDialog::getOpenFileName(0,"Выберите файл","","*");
    ui->File->setText(m_PathFile);

    m_sizeFile = QFileInfo(m_PathFile).size();
    m_nameFile = QFileInfo(m_PathFile).fileName();
    m_File = new QFile(m_PathFile);

    qDebug()<<QFileInfo(m_PathFile).size()
            <<QFileInfo(m_PathFile).fileName();


}

void Client::slotConnected()
{

    QMessageBox::information(0,"Info",QString("Соединение установлено с %1:%2")
                             .arg(m_Host).arg(m_port));


}

void Client::slotError(QAbstractSocket::SocketError)
{

}

void Client::slotSendToServer()
{
    QByteArray SendDataBytes;
    QDataStream out(&SendDataBytes, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    if(!m_File->open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(0,"Error",QString("%1 Невозможно открыть!")
                              .arg(m_Host));
        qDebug()<<"ok to transfer";
        return;
    }
    else
    {
        out << (quint32)0 << m_nameFile;

        qDebug()<<"SendDataBytes.size"<<SendDataBytes.size();

        QByteArray q = m_File->readAll();
        SendDataBytes.append(q);
        m_File->close();

        qDebug()<<"SendDataBytes.size q"<<SendDataBytes.size();

        out.device()->seek(0);
        out << (quint32)(SendDataBytes.size() - sizeof(quint32));

        qint32 x = 0;
        while (x < SendDataBytes.size())
        {
            qint32 y = m_pTcpSocket->write(SendDataBytes);
            x += y;
        }
        qDebug() << x;    // summary size you send

    }


}



void Client::on_SendFile_clicked()
{

// Запустить поток передачи данных
    slotSendToServer();


}

