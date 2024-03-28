// network_monitor.cpp

#include "network_monitor.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <chrono>
#include <thread>

// constructor for class is empty but needed to declare global interface
NetworkMonitor::NetworkMonitor(const std::string &interface) : interface(interface) {}

// reading the values from the proc filesytem
bool NetworkMonitor::readValues(double &rxBytes, double &txBytes) {
    // opn input stream for fule
    std::ifstream file("/proc/net/dev");
    std::string line;
    // skip first two lines
    for (int i = 0; i < 2; ++i) {
        getline(file, line);
    }

    while (getline(file, line)) {
        char iface[32];
        double rxBytesValue, txBytesValue;
        //scan this line by line grabbing only the fields interface and incoming and outgoing bytes
        if (sscanf(line.c_str(), "%s %lf %*d %*d %*d %*d %*d %*d %*d %lf %*d %*d %*d %*d %*d %*d %*d", iface, &rxBytesValue, &txBytesValue) == 3 && strcmp(iface, interface.c_str()) == 0) {
            rxBytes = rxBytesValue;
            txBytes = txBytesValue;
            return true; 
        }
    }

    file.close();
    return false;
}

// in order to get B/s we need to do a calculation
std::vector<double> NetworkMonitor::getNetworkRates() {
    // old and new to calculate rates
    double rxBytesStart, txBytesStart;
    double rxBytesEnd, txBytesEnd;
    if (!readValues(rxBytesStart, txBytesStart)) {
        std::cerr << "Problem w reading" << std::endl;
        return {};
    }
    // sleep for a second to poll
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    if (!readValues(rxBytesEnd, txBytesEnd)) {
        std::cerr << "Error reading values after 1 second." << std::endl;
        return {};
    }
    // calculate B/s incoming and outgoing
    double rxRate = (rxBytesEnd - rxBytesStart) / 1.0; 
    double txRate = (txBytesEnd - txBytesStart) / 1.0; 

    return {rxRate/1024, txRate/1024};
}

//int main() {
//    std::string interface = "eth0:";
//    NetworkMonitor networkMonitor(interface);
//    std::vector<double> rates = networkMonitor.getNetworkRates();
//    std::cout << "Interface: " << interface << " | RX Rate: " << rates[0] << " B/s | TX Rate: " << rates[1] << " B/s" << std::endl;
//    return 0;
//}
