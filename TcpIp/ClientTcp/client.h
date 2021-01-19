#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDataStream>
#include <QThread>




namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(const QString& strHost, int nPort, QWidget *parent = 0);
    ~Client();

    int m_port;
    QString m_Host;

    quint32 m_sizeFile;
    QString m_nameFile;


private slots:

    void on_ChangeFile_clicked();
    void slotConnected();
    void slotError(QAbstractSocket::SocketError);
    void slotSendToServer();


    void on_SendFile_clicked();

private:
    Ui::Client *ui;

    QTcpSocket* m_pTcpSocket;
    QFile *m_File;
    QString m_PathFile;

    QThread *send;




};

#endif // CLIENT_H
