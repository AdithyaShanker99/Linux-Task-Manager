#include <cstdlib>
#include <unistd.h>
#include <string>
#include <sys/statvfs.h>
#include<sys/utsname.h>


class sysInfo {
  public:
          std::string totalMemory;
          std::string processorVersion;
          std::string kernelVersion;
          std::string osReleaseName;
          std::string osReleaseMachine;
          void parseSystemInfo();

};



