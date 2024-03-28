#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include <vector>
#include <string>

std::vector<std::string> getSystemInfo();
struct SystemInfo {
    std::string hostname;
    std::string operatingSystem;
    std::string kernel;
    std::string architecture;
};

SystemInfo parseSystemInfo(const std::vector<std::string>& outputLines);

#endif
