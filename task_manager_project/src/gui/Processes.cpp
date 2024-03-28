#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <dirent.h>
#include "Processes.h"

//stat has virtual memory resident memory and start time
//to find if user's process use getuid and compare that to first value in status/uid
/*class processInfo {
};*/

void getName(std::string pid, processInfo& process) {
  //std::cout << "function run" << '\n';
  std::string filePath = "/proc/";
  filePath.append(pid);
  filePath.append("/status");
  
  std::ifstream file;
  file.open(filePath);
  
  std::string line;
  if (file.is_open()) {
    while (file) {
      std::getline (file,line);
      if (line.find("Name") != std::string::npos) {
        int pos = line.find('\t');
        process.name = line.substr(pos + 1, line.length() - 1);
        //std::cout << "name: " << process.name << '\n';
        //std::cout << line << '\n';
      }
    }
  }

}

void getStatus(std::string pid, processInfo& process) {
  std::string filePath = "/proc/";
  filePath.append(pid);
  filePath.append("/status");

  std::ifstream file;
  file.open(filePath);

  std::string line;
  if (file.is_open()) {
    while (file) {
      std::getline (file,line);
      if (line.find("State") != std::string::npos) {
        int pos = line.find('(');
	int end = line.find(')');
        process.status = line.substr(pos + 1, 8);
        //std::cout << "status: " << process.status << '\n';
	      //std::cout << line << '\n';
      }
    }
  }

}

void getCpuTime(std::string pid, processInfo& process) {
  std::string filePath = "/proc/";
  filePath.append(pid);
  filePath.append("/status");

  std::ifstream file;
  file.open(filePath);

  std::string line;
  if (file.is_open()) {
    while (file) {
      std::getline (file,line);
      if (line.find("State") != std::string::npos) {
        //std::cout << line << '\n';
      }
    }
  }

}


void getStatFields(std::string pid, processInfo& process) {
  std::string filePath = "/proc/";
  filePath.append(pid);
  filePath.append("/stat");

  std::ifstream file;
  file.open(filePath);

  std::string line;
  if (file.is_open()) {
    while (file) {
      std::getline (file,line);
      std::string token;
      size_t pos = 0;
      int count = 0;
      
      while((pos = line.find(" ")) != std::string::npos) {
        token = line.substr(0, pos);
	//std::cout << token << '\n';
	if (count == 13) {
	  process.utime = token;
	} else if (count == 14) {
	  process.stime = token;
	} else if (count == 21) {
	  process.dateStart = token;
	} else if (count == 22) {
	  process.virtualMem = token;
	} else if (count == 23) {
 	  process.residentMem = token;
	}
	line.erase(0, pos + 1);
	count++;
	//13 14 21 22 23
      }
      //std::cout << "utime: " << process.utime << '\n';
      //std::cout << "stime: " << process.stime << '\n';
      //std::cout << "start time: " << process.dateStart << '\n';
      //std::cout << "virtual mem: " << process.virtualMem << '\n';
      //std::cout << "resident mem: " << process.residentMem << '\n';
      break;
    }
  }

}

void getPid(std::string pid, processInfo& process) {
  std::string filePath = "/proc/";
  filePath.append(pid);
  filePath.append("/status");

  std::ifstream file;
  file.open(filePath);

  std::string line;
  if (file.is_open()) {
    while (file) {
      std::getline (file,line);
      if (line.find("Pid") != std::string::npos) {
        int pos = line.find('\t');
        process.pid = line.substr(pos + 1, line.length() - 1);
        //std::cout << "pid: " << process.pid << '\n';
        break;
      }
    }
  }

}

void getPPid(std::string pid, processInfo& process) {
  std::string filePath = "/proc/";
  filePath.append(pid);
  filePath.append("/status");

  std::ifstream file;
  file.open(filePath);

  std::string line;
  if (file.is_open()) {
    while (file) {
      std::getline (file,line);
      if (line.find("PPid") != std::string::npos) {
        int pos = line.find('\t');
        process.ppid = line.substr(pos + 1, line.length() - 1);
        //std::cout << "PPid: " << process.ppid << '\n';
	//std::cout << line << '\n';
        break;
      }
    }
  }

}

void getUID(std::string pid, processInfo& process) {
  std::string filePath = "/proc/";
  filePath.append(pid);
  filePath.append("/status");

  std::ifstream file;
  file.open(filePath);

  std::string line;
  if (file.is_open()) {
    while (file) {
      std::getline (file,line);
      if (line.find("Uid") != std::string::npos) {
        int pos = line.find_first_of("1234567890");
        line.erase(0, pos);
	pos = line.find('\t');
	line = line.substr(0,pos);
	
	std::string result;
	std::string command = "id -nu ";
	command = command + line;
	try {
	  std::system((command + " > output.txt").c_str());
	  std::ifstream ifs("output.txt");
	  ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	  std::getline(ifs, result);
	} catch (const std::exception& e) {
          std::cout << e.what() << '\n';
	}
	//std::cout << result << '\n';
        break;
      }
      
    }
  }

}

void getMemory(std::string pid, processInfo& process) {
  std::string filePath = "/proc/";
  filePath.append(pid);
  filePath.append("/status");

  std::ifstream file;
  file.open(filePath);

  std::string line;
  if (file.is_open()) {
    while (file) {
      std::getline (file,line);
      if (line.find("VmSize") != std::string::npos) {
        int pos = line.find('\t');
	process.virtualMem = line.substr(pos + 3, line.length() - 1);
	//std::cout << "virtual memory: " << process.virtualMem << '\n';
        break;
      }
    }
  }

}

void getSharedMem(std::string pid, processInfo& process) {
  std::string filePath = "/proc/";
  filePath.append(pid);
  filePath.append("/statm");

  std::ifstream file;
  file.open(filePath);

  std::string line;
  if (file.is_open()) {
    while (file) {
      std::getline (file,line);
      std::string token;
      size_t pos = 0;
      int count = 0;

      while((pos = line.find(" ")) != std::string::npos) {
        token = line.substr(0, pos);
        //std::cout << token << '\n';
        if (count == 2) {
          process.sharedMem = token;
          //std::cout << "shared mem: " << process.sharedMem << '\n';
	} 
        line.erase(0, pos + 1);
        count++;
	//std::cout << "shared mem: " << process.sharedMem << '\n';
      }
    }
  }
}

void processInfo::getMemoryMap (std::string pid, processInfo& process) {
  std::string path = "/proc/";
  path = path + pid;
  path = path + "/smaps";
  std::string line;
  std::ifstream file;
  file.open(path);
  int count = 0;
  int flag = 0;
  int lineCount = 0;
  int sizeFlag = 0;
  memoryMapRow row;
  //std::cout << path << '\n';
  if (file.is_open()) {
    //std::cout << "new line" << "\n";
    while (file) {
	std::getline(file, line);

	if (line == "") {
          //std::cout << "porcess has no memeory map" << "\n";
	} else {
	  
	  if (line.find('-') != std::string::npos) {
	    //std::cout << line << '\n';
	    //std::cout << line.length() << '\n';
	    sizeFlag = 0;
	    int bracketPosition = line.find('[');
	    int slashPosition = line.find('/');
	    std::string correctPathname;
	    if (bracketPosition != std::string::npos) {
		//bracket
		    correctPathname = line.substr(bracketPosition);
	    } else if (slashPosition != std::string::npos) {
		//slash
		correctPathname = line.substr(slashPosition);
	    } else {
		correctPathname = "anonymous";
	    }
            lineCount = 0;
	    row = memoryMapRow();
            process.memoryMap.push_back(row);
	    //std::cout << process.memoryMap.size() << '\n';
	    std::string address;
	    std::string perms;
	    std::string offset;
	    std::string pathname;
	    std::istringstream iss(line);
	    iss >> address >> perms >> offset;

	    row.fileName = correctPathname;
	    row.vmStart = address;
	    row.flags = perms;
	    row.vmOffset = offset;
	  } else if (line.find("Size") != std::string::npos && sizeFlag == 0) {
		  //td::cout << line << '\n';
	    int position = line.find(":");
	    std::string sub = line.substr(position + 1);
	    int finalPos = sub.find_first_not_of(" \t\n\r");
	    std::string answer = sub.substr(finalPos);
	    //std::cout << answer << '\n';
	    sizeFlag = 1;
	    row.vmSize = answer;
	  } else if (line.find("Shared_Clean") != std::string::npos) {
	                int position = line.find(":");
            std::string sub = line.substr(position + 1);
            int finalPos = sub.find_first_not_of(" \t\n\r");
            std::string answer = sub.substr(finalPos);
            //std::cout << answer << '\n';
	    row.sharedClean = answer;
          } else if (line.find("Shared_Dirty") != std::string::npos) {
	                int position = line.find(":");
            std::string sub = line.substr(position + 1);
            int finalPos = sub.find_first_not_of(" \t\n\r");
            std::string answer = sub.substr(finalPos);
            //std::cout << answer << '\n';
	    row.sharedDirty = answer;
          } else if (line.find("Private_Clean") != std::string::npos) {
                        int position = line.find(":");
            std::string sub = line.substr(position + 1);
            int finalPos = sub.find_first_not_of(" \t\n\r");
            std::string answer = sub.substr(finalPos);
            //std::cout << answer << '\n';
	    row.privateClean = answer;
          } else if (line.find("Private_Dirty") != std::string::npos) {
	                int position = line.find(":");
            std::string sub = line.substr(position + 1);
            int finalPos = sub.find_first_not_of(" \t\n\r");
            std::string answer = sub.substr(finalPos);
            //std::cout << answer << '\n';
	    row.privateDirty = answer;
          }

	  //if (line.find("Flags") != std::string::npos) {
          //  count++;
	  //}
           //std::cout << line << '\n';
	}
	
	//std::cout << line << '\n';

    }
  }
  //if (count != 0) {
  //std::cout << count << '\n';

  //}
}

void openFiles () {

}

void processInfo::getProcessInfo(std::string pid, processInfo& process) {

      getName(pid, process);
      getMemoryMap(pid, process);
      getStatus(pid, process);
      getStatFields(pid, process);
      getPid(pid, process);
      getPPid(pid, process);
      getUID(pid, process);
      getMemory(pid, process);
      getSharedMem(pid, process);
	
}

/*int main() {
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
      getName(entry->d_name, process);
      getStatus(entry->d_name, process);
      getStatFields(entry->d_name, process);
      getPid(entry->d_name, process);
      getPPid(entry->d_name, process);
      getUID(entry->d_name, process);
      getMemory(entry->d_name, process);
      getSharedMem(entry->d_name, process);
      std::cout << "\n\n\n\n\n";	
      //memoryMap(entry->d_name);
      //std::cout << "Process ID: " << entry->d_name << std::endl;
      //break;
    }
  }

  closedir(dir);

}*/
