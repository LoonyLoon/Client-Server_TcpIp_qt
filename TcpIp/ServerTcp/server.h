#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDataStream>
#include <QDir>
#include <QVector>
#include <QFile>
#include <QIODevice>

namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(int nPort, QWidget *parent = 0);
    ~Server();

private:
    Ui::Server *ui;

    QTcpServer * mTcpServer;
    QTcpSocket * mTcpSocket;
    qint32      m_blockSize = 0;


private slots:
    void slotRead();
    void slotNewConnection();

};

#endif // SERVER_H
