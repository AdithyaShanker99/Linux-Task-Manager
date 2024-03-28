// DirectoryStruct.cpp
#include "DirectoryStruct.h"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

std::vector<Directory> executeAndParseDf() {
    std::vector<Directory> directories;

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return directories;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return directories;
    }

    if (pid == 0) { // Child process
        close(pipefd[0]); // Close unused read end

        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        // Execute the command using execlp
        execlp("df", "df", "-aTH", nullptr);
        perror("execlp");  // This should not be reached if execlp is successful
        exit(EXIT_FAILURE);
    } else { // Parent process
        close(pipefd[1]); // Close unused write end

        const int buffer_size = 256;
        char buffer[buffer_size];

        // Read and parse each line from the read end of the pipe
        FILE* pipeStream = fdopen(pipefd[0], "r");
        if (pipeStream == nullptr) {
            perror("fdopen");
            close(pipefd[0]);
            waitpid(pid, nullptr, 0);
            return directories;
        }

        // Skip the first line
        if (fgets(buffer, buffer_size, pipeStream) == nullptr) {
            perror("fgets");
            fclose(pipeStream);
            close(pipefd[0]);
            waitpid(pid, nullptr, 0);
            return directories;
        }

        // Read and parse each subsequent line
        while (fgets(buffer, buffer_size, pipeStream) != nullptr) {
            Directory dir;

            // Example parsing logic, adjust based on your actual output format
            char filesystem[256], type[256], size[256], used[256], avail[256], usePercentage[256], mountedOn[256];
            if (sscanf(buffer, "%255s %255s %255s %255s %255s %255s %255s",
                    filesystem, type, size, used, avail, usePercentage, mountedOn) == 7) {
                dir.filesystem = filesystem;
                dir.type = type;
                dir.size = size;
                dir.used = used;
                dir.avail = avail;
                dir.usePercentage = usePercentage;
                dir.mountedOn = mountedOn;

                // Add the parsed directory to the vector
                directories.push_back(dir);
            }
        }

        fclose(pipeStream);
        close(pipefd[0]);

        // Wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);
    }

    return directories;
}

int main() {
    std::vector<Directory> result = executeAndParseDf();

    // Display information
    for (const auto& dir : result) {
        printf("Filesystem: %s\n", dir.filesystem.c_str());
        printf("Type: %s\n", dir.type.c_str());
        printf("Size: %s\n", dir.size.c_str());
        printf("Used: %s\n", dir.used.c_str());
        printf("Avail: %s\n", dir.avail.c_str());
        printf("Use%%: %s\n", dir.usePercentage.c_str());
        printf("Mounted On: %s\n", dir.mountedOn.c_str());
        printf("-----------------------------\n");
    }

    return 0;
}
