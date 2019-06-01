#include "qt/logindialog.h"
#include "qt/mainwindow.h"
#include <iostream>

#include <QApplication>
#include <QtWidgets>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <miniupnpc/miniupnpc.h>

using namespace boost::asio::ip;

void printDevList(UPNPDev* devList) {
    if (devList == nullptr)
        return;

    std::cout << "Desc: " << devList->descURL << " St: " << devList->st << std::endl;
    printDevList(devList->pNext);
}

int main(int argc, char* argv[]) {
    /*UPNPDev* devList = upnpDiscover(100, nullptr, nullptr, 0, 0, nullptr);
    printDevList(devList);
    freeUPNPDevlist(devList);
    */
    QApplication a(argc, argv);
    MainWindow mainWindow;
    return a.exec();
}

