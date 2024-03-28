#include "memoryGraphs.h"
#include <iostream>

int main() {
    std::array<std::string, 6> result = MemoryGraphs::executeCommandAndParse();

    // Print the parsed values
    std::cout << "Total Memory: " << result[0] << "\n";
    std::cout << "Used Memory: " << result[1] << "\n";
    std::cout << "Free Memory: " << result[2] << "\n";
    std::cout << "Total Swap: " << result[3] << "\n";
    std::cout << "Used Swap: " << result[4] << "\n";
    std::cout << "Free Swap: " << result[5] << "\n";

    return 0;
}
