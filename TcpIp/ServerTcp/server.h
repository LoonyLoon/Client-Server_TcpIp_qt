#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDataStream>
#include <QFile>


namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(int nPort, QWidget *parent = 0);
    ~Server();

private slots:
    void slotRead();
    void slotNewConnection();

private:
    Ui::Server *ui;

    QTcpServer  *m_TcpServer;
    QTcpSocket  *m_TcpSocket;

    qint64       m_blockSize = 0;
};

#endif // SERVER_H
