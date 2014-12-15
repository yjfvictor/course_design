#ifndef CMULTICAST_H
#define CMULTICAST_H

#include <QtNetwork/QUdpSocket>
class Dialog;
class QPlainTextEdit;

class CMulticast : public QUdpSocket
{
    Q_OBJECT
public:
    CMulticast( Dialog * parent = 0 );
public slots:
    void RecvDiagram( );
    void SendDiagram( const QString & txtSend );
private:
    Dialog * parent;
};

#endif // CMULTICAST_H
