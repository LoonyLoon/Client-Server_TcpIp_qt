#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDataStream>




namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(const QString& strHost, int nPort, QWidget *parent = 0);
    ~Client();

private slots:

    void on_ChangeFile_clicked();
    void slotConnected();
    void on_SendFile_clicked();

private:
    Ui::Client *ui;

    QTcpSocket  *m_pTcpSocket;
    QFile       *m_File;
    QString      m_PathFile;
    QString      m_nameFile;
    QString      m_Host;

    int m_port;
    quint32 m_sizeFile;

    void sendToServer();


};

#endif // CLIENT_H
