#ifndef PROCESSES_H
#define PROCESSES_H

#include <string>

/*struct Process {
};*/

class memoryMapRow {
  public:
    std::string fileName; //maps
    std::string vmStart;
    std::string vmEnd;
    std::string vmSize;
    std::string flags; //maps
    std::string vmOffset; //maps
    std::string privateClean;
    std::string privateDirty;
    std::string sharedClean;
    std::string sharedDirty;
    memoryMapRow() {
    }
};

class openFileRow {
  public:
    std::string fd;
    std::string type;
    std::string object;
};

class processInfo {
  public:
  std::string name;
  std::string status;
  std::string cpuPercent;
  std::string utime;
  std::string stime;
  std::string pid;
  std::string ppid;
  std::string memory;
  std::string user;
  std::string virtualMem;
  std::string residentMem;
  std::string sharedMem;
  std::string cpuTime;
  std::string dateStart;
  std::vector<processInfo> childProcess;
  std::vector<memoryMapRow> memoryMap;
  std::vector<openFileRow> openFiles;
  void getProcessInfo(std::string pid, processInfo& process);
  void getMemoryMap(std::string pid, processInfo& process);
  void getOpenFiles(std::string pid);
  processInfo() {
  }

};

/*class memoryMapRow {
};
*/
#endif // PROCESSES_H
