#include "dialog.h"
#include "ui_dialog.h"
#include "cmulticast.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog), multicast( new CMulticast(this) )
{
    ui->setupUi(this);
    installEventFilter(this);
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::eventFilter(QObject * obj, QEvent * e )
{
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *event = static_cast<QKeyEvent*>(e);
        if (event->key() == Qt::Key_Return && (event->modifiers() & Qt::ControlModifier))
        {
            emit on_btnSend_clicked();
            return true;
        }
    }
    return false;
}

QPlainTextEdit * Dialog::getTxtRecv()
{
    return ui->txtRecv;
}

void Dialog::on_btnClose_clicked()
{
    emit close();
}

void Dialog::on_btnSend_clicked()
{
    multicast->SendDiagram(ui->txtSend->toPlainText());
    ui->txtSend->clear();
    ui->txtSend->setFocus();
}

void Dialog::on_btnClear_clicked()
{
    ui->txtRecv->clear();
}
