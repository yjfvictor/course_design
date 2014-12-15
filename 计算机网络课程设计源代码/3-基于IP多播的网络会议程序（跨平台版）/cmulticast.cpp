#include "cmulticast.h"
#include "dialog.h"
#include <QtGui/QPlainTextEdit>
#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtGui/QScrollBar>

#define     MULTICAST_PORT_NUM      8000

CMulticast::CMulticast( Dialog * parent )
    : QUdpSocket( parent ), parent( parent )
{
    bind( MULTICAST_PORT_NUM, QUdpSocket::ShareAddress );
    connect( this, SIGNAL(readyRead()), this, SLOT(RecvDiagram()) );
}

void CMulticast::RecvDiagram( )
{
    QString textRecved;
    QByteArray datagram;
    QHostAddress hostAddress;
    quint16 port;

    while ( hasPendingDatagrams() )
    {
        datagram.resize( pendingDatagramSize());
        readDatagram(datagram.data(), datagram.size(), &hostAddress, &port);
        textRecved = QString("来自%1:%2的消息：\n%3\n\n\n")
                .arg(hostAddress.toString()).arg(port).arg(QString(datagram));
        parent->getTxtRecv()->appendPlainText(textRecved);
        parent->getTxtRecv()->verticalScrollBar()->setValue(parent->getTxtRecv()->verticalScrollBar()->maximumHeight());
    }
}

void CMulticast::SendDiagram( const QString & txtSend )
{
    QByteArray byteArray = txtSend.toAscii();
    writeDatagram( byteArray.data(), byteArray.size(), QHostAddress::Broadcast, MULTICAST_PORT_NUM );
}
