#include "cpuGraphs.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <sstream>

std::vector<double> CPUGraphs::executeMPStatAndParse() {
    // run mpstat at interval write to stderr if fails
    FILE* pipe = popen("mpstat -P ALL 1 1", "r");
    if (!pipe) {
        std::cerr << "Error running command" << std::endl;
        return {};
    }
    //read from the  output
    char buffer[256];
    std::string output;
    ssize_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), pipe)) > 0) {
        output.append(buffer, bytesRead);
    }
    pclose(pipe);
    std::vector<double> idlePercentages;
    // Parse the output to extract CPU idle percentages
    parse(output, idlePercentages);

    return idlePercentages;
}

void CPUGraphs::parse(const std::string& output, std::vector<double>& idlePercentages) {
    std::istringstream iss(output);
    std::string line;
    // skip first three lines cuz its not needed
    for (int i = 0; i < 3; ++i) {
        std::getline(iss, line);
    }
    double idlePercentage;
    // scanf for the field we want which is idle percent
    while (std::getline(iss, line)) {
        if (sscanf(line.c_str(), "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lf", &idlePercentage) == 1) {
            //subtract from 100 to get usage
            idlePercentages.push_back(100.00 - idlePercentage);
        }
    }
}

//int main() {
//    CPUGraphs cpuGraphs;
//    std::vector<double> idlePercentages = cpuGraphs.executeMPStatAndParse();

//    // Print the parsed values
//    std::cout << "Idle Percentages: ";
//    for (double percentage : idlePercentages) {
//        std::cout << percentage << " ";
//    }
//    std::cout << std::endl;

//    return 0;
//}
