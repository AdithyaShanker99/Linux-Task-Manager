#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

class MemoryGraphs {
public:
    static std::array<std::string, 6> executeCommandAndParse();
};

void parseFreeOutput(std::istream& input,
                     std::string& totalMem, std::string& usedMem, std::string& freeMem,
                     std::string& totalSwap, std::string& usedSwap, std::string& freeSwap) {
    std::string line;

    // Skip the header line
    std::getline(input, line);

    // Read the line containing memory information
    std::getline(input, line);
    std::istringstream lineStreamMem(line);
    std::string memType;
    lineStreamMem >> memType >> totalMem >> usedMem >> freeMem;

    // Read the line containing swap information
    std::getline(input, line);
    std::istringstream lineStreamSwap(line);
    lineStreamSwap >> memType >> totalSwap >> usedSwap >> freeSwap;
}

std::array<std::string, 6> MemoryGraphs::executeCommandAndParse() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid != 0) {
        close(pipefd[1]);

        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        } else {
            std::cerr << "Error: Command execution failed.\n";
            exit(EXIT_FAILURE);
        }

        close(STDIN_FILENO);
        dup(pipefd[0]);
        close(pipefd[0]);

        std::array<std::string, 6> result;
        std::string totalMem, usedMem, freeMem, totalSwap, usedSwap, freeSwap;
        parseFreeOutput(std::cin, totalMem, usedMem, freeMem, totalSwap, usedSwap, freeSwap);

        result[0] = totalMem;
        result[1] = usedMem;
        result[2] = freeMem;
        result[3] = totalSwap;
        result[4] = usedSwap;
        result[5] = freeSwap;

        return result;

    } else {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        const char* cmd = "/usr/bin/free";
        char* const args[] = {(char*)cmd, (char*)"-hw", nullptr};
        if (execve(cmd, args, environ) == -1) {
            perror("execve");
            _Exit(127);
        }
    }
}

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
