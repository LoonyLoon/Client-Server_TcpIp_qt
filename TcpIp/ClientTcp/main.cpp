#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client w("127.0.0.1",5555);

    w.show();

    return a.exec();
}
