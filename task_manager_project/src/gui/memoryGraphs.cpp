#include "memoryGraphs.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sstream>
#include <iomanip>
#include <iostream>

// output is in different metrics make all the same using KB
double convertToKilobytes(const std::string& value, const std::string& unit) {
  double multiplier = 1.0;

  if (unit == "B") {
    multiplier = 1.0 / 1024.0;  
  } else if (unit == "Mi") {
    multiplier = 1024.0;  
  } else if (unit == "Gi") {
    multiplier = 1024.0 * 1024.0; 
  }
  return std::stod(value) * multiplier;
}

// parse the output from the free command and convert units to common to get percents
void parseFreeOutput(std::istream& input,
    std::string& totalMem, std::string& usedMem, std::string& freeMem,
  std::string& totalSwap, std::string& usedSwap, std::string& freeSwap) {
  std::string line;
  
  // Skip the first two lines
  std::getline(input, line);
  std::getline(input, line);

  // Parse memory and swap info
  std::istringstream lineStreamMem(line);
  std::string memType;
  lineStreamMem >> memType >> totalMem >> usedMem >> freeMem;
  std::getline(input, line);
  std::istringstream lineStreamSwap(line);
  lineStreamSwap >> memType >> totalSwap >> usedSwap >> freeSwap;

  // convert to kilobytes
  size_t swapUsedUnitPos = usedSwap.find_first_of("BKMGT");
  if (swapUsedUnitPos != std::string::npos) {
    // take only the values that occur before B Kb Mi Gi T
    std::string swapUsedValue = usedSwap.substr(0, swapUsedUnitPos);
    std::string swapUsedUnit = usedSwap.substr(swapUsedUnitPos);
    double swapUsedKB = convertToKilobytes(swapUsedValue, swapUsedUnit);
    usedSwap = std::to_string(swapUsedKB);
  }
  size_t swapTotalUnitPos = totalSwap.find_first_of("BKMGT");
  if (swapTotalUnitPos != std::string::npos) {
    // take only the values that occur before B Kb Mi Gi T
    std::string swapTotalValue = totalSwap.substr(0, swapTotalUnitPos);
    std::string swapTotalUnit = totalSwap.substr(swapTotalUnitPos);
    double swapTotalKB = convertToKilobytes(swapTotalValue, swapTotalUnit);
    totalSwap = std::to_string(swapTotalKB);
  }
  //std::cout << totalSwap << "/" << usedSwap << "\n" ;

}

// execute command shell stuff 
// return set size array
std::array<double, 2> MemoryGraphs::executeCommandAndParse() {
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    perror("Pipe Creation");
    exit(EXIT_FAILURE);
  }
  // fork to create new process
  pid_t pid = fork();

  if (pid == -1) {
    perror("Forking");
    exit(EXIT_FAILURE);
  } else if (pid != 0) {
    close(pipefd[1]);

    // Watch child process to see if succesful execution
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
    } else {
      std::cerr << "Failed Execution";
      exit(-1);
    }
    // redirect back to read end to use for parsing
    close(STDIN_FILENO);
    dup(pipefd[0]);
    close(pipefd[0]);

    std::string totalMem, usedMem, freeMem, totalSwap, usedSwap, freeSwap;
    // parse output after its redirected
    parseFreeOutput(std::cin, totalMem, usedMem, freeMem, totalSwap, usedSwap, freeSwap);
    double memUsedPercent = std::stod(usedMem) / std::stod(totalMem) * 100.0;
    double swapUsedPercent = std::stod(usedSwap) / std::stod(totalSwap) * 100.0;

    // return our array of 2 for percents
    return {memUsedPercent, swapUsedPercent};

  } else {
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    // uses execve to execute free -hw
    const char* cmd = "/usr/bin/free";
    char* const args[] = {(char*)cmd, (char*)"-hw", nullptr};
    if (execve(cmd, args, environ) == -1) {
      perror("execve");
      _Exit(-1);
    }
  }
}

//int main() {
//  std::array<double, 2> result = MemoryGraphs::executeCommandAndParse();
//  std::cout << "Used Memory Percentage: " << std::fixed << std::setprecision(2) << result[0] << "%\n";
//  std::cout << "Used Swap Percentage: " << std::fixed << std::setprecision(2) << result[1] << "%\n";

//  return 0;
//}
