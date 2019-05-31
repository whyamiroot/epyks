#include <iostream>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <miniupnpc/miniupnpc.h>

#include <jrtplib3/rtpsession.h>
#include <jrtplib3/rtpsessionparams.h>
#include <jrtplib3/rtpudpv4transmitter.h>

using namespace boost::asio::ip;
using namespace jrtplib;

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

    RTPSession s;
    RTPSessionParams sessionparams;
    sessionparams.SetOwnTimestampUnit(1.0/8000.0);
    RTPUDPv4TransmissionParams transparams;
    transparams.SetPortbase(8000);
    int status = s.Create(sessionparams,&transparams);
    if (status < 0) {
        std::cerr << RTPGetErrorString(status) << std::endl;
        exit(-1);
    }
    return 0;
}

