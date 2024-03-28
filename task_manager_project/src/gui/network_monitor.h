// network_monitor.h

#ifndef NETWORK_MONITOR_H
#define NETWORK_MONITOR_H

#include <string>
#include <vector>

class NetworkMonitor {
public:
    NetworkMonitor(const std::string &interface);
    std::vector<double> getNetworkRates();

private:
    bool readValues(double &rxBytes, double &txBytes);
    std::string interface;
};

#endif // NETWORK_MONITOR_H
