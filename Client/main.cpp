#include "tcpclient.h"
#include <QApplication>
#include"fightmanager.h"
#include"pokemon.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpClient w;
    srand((unsigned)time(NULL));
    w.setWindowTitle("Pokemon 2020 (Designed by ZPF)");
    w.show();
    return a.exec();
}
