#ifndef CPU_GRAPHS_H
#define CPU_GRAPHS_H

#include <vector>
#include <string>

class CPUGraphs {
public:
    static std::vector<double> executeMPStatAndParse();
private:
    static void parse(const std::string& output, std::vector<double>& idlePercentages);
};

#endif // CPU_GRAPHS_H

