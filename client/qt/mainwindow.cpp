#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "logindialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loginDialog = new LoginDialog(this);
    loginDialog->show();
    connect(loginDialog, &LoginDialog::signinSuccess, this, &MainWindow::onSigninSuccess);
}

void MainWindow::onSigninSuccess()
{
    this->show();
    loginDialog->hide();
}

MainWindow::~MainWindow()
{
    delete loginDialog;
    delete ui;
}

