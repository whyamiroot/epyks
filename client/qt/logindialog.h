#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

signals:
    void signinSuccess();    

private slots:
    void signinButtonClicked();
    void registerButtonClicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
