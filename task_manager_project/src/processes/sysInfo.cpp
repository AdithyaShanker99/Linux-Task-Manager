#include "sysInfo.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
//#include <cstring>
#include <unistd.h>
#include <string>
#include <sys/statvfs.h>
//#include <string.h>
#include<sys/utsname.h>


//using namespace std;

/*class sysInfo {
  public:
	  std::string totalMemory;
	  std::string processorVersion;
	  std::string kernelVersion;
	  std::string osReleaseName;
	  std::string osReleaseMachine;
};*/
void sysInfo::parseSystemInfo() {


  std::string totalMem;
  std::ifstream file;
  std::string finalAnswer;
  std::string finalKernel;
  file.open("/proc/meminfo");
  std::string mystring;
  if (file.is_open()) {
    while (file) {
      std::getline (file, mystring);
      if (mystring.find("MemTotal") != std::string::npos) {
        int position = mystring.find_first_of("9012345678");
        totalMem = mystring.substr(position, totalMem.length() - 1);
        //std::string totalMem = str
        std::cout << totalMem << '\n';
      }
    }
  }

  file.close();
  //processor version

  std::ifstream processorFile;
  processorFile.open("/proc/cpuinfo");
  std::string processor;
  if (processorFile.is_open()) {
    while(processorFile) {
      std::getline(processorFile, processor);
      //std::cout << processor << '\n';
      if (processor.find("model name") != std::string::npos) {
        int position = processor.find(':');
        finalAnswer = processor.substr(position + 2, processor.length() - 1);
        //std::cout << finalAnswer << '\n';
        break;
      }
    }
  }
  processorFile.close();

  //Kernel version
  std::ifstream kernelFile;
  kernelFile.open("/proc/version");
  std::string kernel;
  if (kernelFile.is_open()) {
    while(kernelFile) {
      std::getline(kernelFile, kernel);
      //std::cout << kernel << '\n';
      int position = kernel.find('(');
      finalKernel = kernel.substr(0, position);
      //std::cout << finalKernel << '\n';
      //if (kernel.find("model name") != std::string::npos) {
      //  std::cout << kernel << '\n';
      //  break;
      //}
    }
  }
  kernelFile.close();

  //OS release versuion
  struct utsname uts;
  uname(&uts);
  //std::cout << uts.sysname << '\n';
  //std::cout << uts.machine<< '\n';
  //std::cout << uts.release << '\n';

 sysInfo answer;
 this->totalMemory = totalMem;
 this->processorVersion = finalAnswer;
 this->kernelVersion = finalKernel;
 this->osReleaseName = uts.sysname;
 this->osReleaseMachine = uts.machine;


}
/*
int main() {
  std::string totalMem;
  std::ifstream file;
  std::string finalAnswer;
  std::string finalKernel;
  file.open("/proc/meminfo");
  std::string mystring;
  if (file.is_open()) {
    while (file) {
      std::getline (file, mystring);
      if (mystring.find("MemTotal") != std::string::npos) {
        int position = mystring.find_first_of("9012345678");
	totalMem = mystring.substr(position, totalMem.length() - 1);
        //std::string totalMem = str
        std::cout << totalMem << '\n';
      }
    }
  }

  file.close();
  //processor version
  
  std::ifstream processorFile;
  processorFile.open("/proc/cpuinfo");
  std::string processor;
  if (processorFile.is_open()) {
    while(processorFile) {
      std::getline(processorFile, processor);
      std::cout << processor << '\n';
      if (processor.find("model name") != std::string::npos) {
        int position = processor.find(':');
	finalAnswer = processor.substr(position + 2, processor.length() - 1);
	std::cout << finalAnswer << '\n';
	break;
      }		   
    }
  }
  processorFile.close();

  //Kernel version
  std::ifstream kernelFile;
  kernelFile.open("/proc/version");
  std::string kernel;
  if (kernelFile.is_open()) {
    while(kernelFile) {
      std::getline(kernelFile, kernel);
      std::cout << kernel << '\n';
      int position = kernel.find('(');
      finalKernel = kernel.substr(0, position);
      std::cout << finalKernel << '\n';
      //if (kernel.find("model name") != std::string::npos) {
      //  std::cout << kernel << '\n';
      //  break;
      //}
    }
  }
  kernelFile.close();

  //OS release versuion
  struct utsname uts;
  uname(&uts); 
  std::cout << uts.sysname << '\n';
  std::cout << uts.machine<< '\n';
  std::cout << uts.release << '\n';

 sysInfo answer;
 answer.totalMemory = totalMem;
 answer.processorVersion = finalAnswer;
 answer.kernelVersion = finalKernel;
 answer.osReleaseName = uts.sysname;
 answer.osReleaseMachine = uts.machine;

  return 1;
}*/

