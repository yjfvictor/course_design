#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui/QDialog>
class CMulticast;
class QPlainTextEdit;
class QPushButton;

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QPlainTextEdit * getTxtRecv();

protected:
    bool eventFilter(QObject * obj, QEvent * e );

private slots:
    void on_btnClose_clicked();

    void on_btnSend_clicked();

    void on_btnClear_clicked();

private:
    Ui::Dialog *ui;
    CMulticast * multicast;
};

#endif // DIALOG_H
