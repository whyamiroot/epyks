#include "qt/mainwindow.h"

#include "../proto/msg.pb.h"

#include <iostream>

#include <QApplication>
#include <QtWidgets>

int main(int argc, char* argv[]) {
    proto::SigninRequest request;

    QApplication a(argc, argv);
    MainWindow mainWindow;
    return a.exec();
}

