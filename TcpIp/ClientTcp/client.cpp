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

    connect(m_pTcpSocket, SIGNAL(connected()),
            this,SLOT(slotConnected()));
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
    m_File     = new QFile(m_PathFile);

}

void Client::slotConnected()
{

    QMessageBox::information(0,"Info",QString("Соединение установлено с %1:%2")
                             .arg(m_Host).arg(m_port));
}


void Client::sendToServer()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);


    if(!m_File->open(QIODevice::ReadOnly)) {
        QMessageBox::critical(0,"Error",QString("%1 Невозможно открыть!")
                              .arg(m_Host));
        return;
    } else {
        out << (qint64)0 << m_nameFile;

        data.append(m_File->readAll());
        m_File->close();

        out.device()->seek(0);
        out << (qint64)(data.size() - sizeof(qint64));

        qint64 x = 0;
        while (x < data.size()) {
            quint64 y = m_pTcpSocket->write(data);
            x += y;
        }
    }
}


void Client::on_SendFile_clicked()
{
    sendToServer();
}

