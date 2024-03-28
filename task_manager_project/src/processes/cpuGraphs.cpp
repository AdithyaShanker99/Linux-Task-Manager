#include "cpuGraphs.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sstream>

std::vector<double> CPUGraphs::executeMPStatAndParse() {
    int num_cores = sysconf(_SC_NPROCESSORS_ONLN);

    if (num_cores <= 0) {
        std::cerr << "Error getting the number of CPU cores." << std::endl;
        return {};
    }

    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        std::cerr << "Error creating pipe." << std::endl;
        return {};
    }

    pid = fork();

    if (pid == -1) {
        std::cerr << "Error forking process." << std::endl;
        return {};
    }

    if (pid == 0) { // Child process
        close(pipefd[0]); // Close unused read end of the pipe

        // Redirect stdout to the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        // Execute mpstat command
        execlp("mpstat", "mpstat", "-P", "ALL", "1", "1",  NULL);

        // If execlp fails
        perror("execlp");
        _Exit(EXIT_FAILURE);
    } else { // Parent process
        close(pipefd[1]); // Close unused write end of the pipe

        // Read from the pipe
        char buffer[256];
        std::string output;
        ssize_t bytesRead;

        while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            // Process and parse the output as needed
            output.append(buffer, bytesRead);
        }

        close(pipefd[0]); // Close read end of the pipe

        // Wait for the child process to finish
        waitpid(pid, NULL, 0);

        // Parse the output
        std::vector<double> idlePercentages;
        parse(output, idlePercentages);

        return idlePercentages;
    }
}

void CPUGraphs::parse(const std::string& output, std::vector<double>& idlePercentages) {
    std::istringstream iss(output);
    std::string line;

    // Skip the header lines
    for (int i = 0; i < 3; ++i) {
        std::getline(iss, line);
    }

    // Parse the data lines
    double idlePercentage;
    while (std::getline(iss, line)) {
        if (sscanf(line.c_str(), "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lf", &idlePercentage) == 1) {
            idlePercentages.push_back(100 - idlePercentage);
        }
    }
}

// Main class for testing
int main() {
    std::vector<double> idlePercentages = CPUGraphs::executeMPStatAndParse();

    // Print the parsed values
    std::cout << "Idle Percentages: ";
    for (double percentage : idlePercentages) {
        std::cout << percentage << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
