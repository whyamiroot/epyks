#include <iostream>

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

int main(int argc, char** argv) {
    std::cout << "Test" << std::endl;
    UPNPDev* devList = upnpDiscover(1000, nullptr, nullptr, 0, 0, nullptr);
    printDevList(devList);
    freeUPNPDevlist(devList);
    return 0;
}

