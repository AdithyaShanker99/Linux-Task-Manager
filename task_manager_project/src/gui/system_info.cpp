#include "system_info.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unistd.h>
#include <algorithm>

// Bunch of shell stuff to execute hostname ctl
std::vector<std::string> getSystemInfo() {
    std::vector<std::string> outputLines;
    int pipe_fd[2];
    // pipe fail
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        exit(-1);
    }
    // fork fail
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork fail");
        exit(-1);
    }
    // child
    if (pid == 0) { 
        close(pipe_fd[0]); 
        dup2(pipe_fd[1], STDOUT_FILENO);
        execlp("hostnamectl", "hostnamectl", NULL);
        perror("execution faillllleeed");
        exit(-1);
    } 
    // parent
    else { 
        close(pipe_fd[1]);
        char buffer[4096];
        // read from pipe
        ssize_t bytesRead = read(pipe_fd[0], buffer, sizeof(buffer));

        // buffer is empty
        if (bytesRead == -1) {
            perror("Read from pipe failed");
            exit(-1);
        }
        std::istringstream iss(buffer);
        std::string line;
        while (std::getline(iss, line)) {
            outputLines.push_back(line);
        }
        close(pipe_fd[0]);
    }

    return outputLines;
}

SystemInfo parseSystemInfo(const std::vector<std::string>& outputLines) {
    SystemInfo systemInfo;

    // for each line in our output
    for (const auto& line : outputLines) {
        std::istringstream lineStream(line);
        std::string key, value;
        // split line by : splitting into key and value like server lab
        std::getline(lineStream, key, ':');
        std::getline(lineStream, value);

        // erase all white spaces
        key.erase(std::remove_if(key.begin(), key.end(), [](unsigned char c) {
            return std::isspace(c);
        }), key.end());

        // compare key to get relevant info
        if (key == "Statichostname") {
            systemInfo.hostname = value;
        } else if (key == "OperatingSystem") {
            systemInfo.operatingSystem = value;
        } else if (key == "Kernel") {
            systemInfo.kernel = value;
        } else if (key == "Architecture") {
            systemInfo.architecture = value;
        }
    }

    return systemInfo;
}

//int main() {
//    std::vector<std::string> output = getSystemInfo();

//    SystemInfo systemInfo = parseSystemInfo(output);

//    std::cout << "Hostname: " << systemInfo.hostname << std::endl;
//    std::cout << "Operating System: " << systemInfo.operatingSystem << std::endl;
//    std::cout << "Kernel: " << systemInfo.kernel << std::endl;
//    std::cout << "Architecture: " << systemInfo.architecture << std::endl;

//    return 0;
//}
