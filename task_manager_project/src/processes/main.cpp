#include "sysInfo.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "Processes.h"
//#include <cstring>
#include <unistd.h>
#include <string>
#include <sys/statvfs.h>
//#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include<sys/utsname.h>


int main() {

	sysInfo answer;
    answer.parseSystemInfo();

    // Access the parsed data through the class's fields
    std::cout << "Total Memory: " << answer.totalMemory << '\n';
    std::cout << "Processor Version: " << answer.processorVersion << '\n';
    std::cout << "Kernel Version: " << answer.kernelVersion << '\n';
    std::cout << "OS Release Name: " << answer.osReleaseName << '\n';
    std::cout << "OS Release Machine: " << answer.osReleaseMachine << '\n';
     
    DIR * dir;
  struct dirent * entry;

  dir = opendir("/proc");
  if (dir == NULL) {
    perror("opendir");
    exit(EXIT_FAILURE);
  }

  while (( entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_DIR && atoi(entry->d_name) != 0) {
      processInfo process;
      process.getProcessInfo(entry->d_name, process);
      //std::cout << process.name << '\n';
      if (process.memoryMap.size() != 0) {
	      std::cout << process.memoryMap.size() << '\n';
      }

	      /*getName(entry->d_name, process);
      getStatus(entry->d_name, process);
      getStatFields(entry->d_name, process);
      getPid(entry->d_name, process);
      getPPid(entry->d_name, process);
      getUID(entry->d_name, process);
      getMemory(entry->d_name, process);
      getSharedMem(entry->d_name, process);
      std::cout << "\n\n\n\n\n";*/
      //memoryMap(entry->d_name);
      //std::cout << "Process ID: " << entry->d_name << std::endl;
      //break;
    }
  }

  closedir(dir);

    return 0;




}
