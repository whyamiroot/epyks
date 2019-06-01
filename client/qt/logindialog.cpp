#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->signinButton, SIGNAL(released()), this, SLOT(signinButtonClicked()));
    connect(ui->registerButton, SIGNAL(released()), this, SLOT(registerButtonClicked()));
}

void LoginDialog::signinButtonClicked()
{
    emit signinSuccess();
}

void LoginDialog::registerButtonClicked()
{
    ui->registerButton->setText("Registered");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

