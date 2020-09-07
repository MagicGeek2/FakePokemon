#ifndef SOCKET_M_H
#define SOCKET_M_H

#include <QObject>
#include<QTcpSocket>

class socket_m : public QTcpSocket
{
    Q_OBJECT
public:
    explicit socket_m(qintptr p);

signals:

public slots:
    void on_discon();
};

#endif // SOCKET_M_H
