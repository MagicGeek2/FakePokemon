#include "tcpserver.h"
#include <QApplication>
#include "sql.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpServer win;
    win.setWindowTitle("Pokemon Server");
    win.show();

    return a.exec();
}
