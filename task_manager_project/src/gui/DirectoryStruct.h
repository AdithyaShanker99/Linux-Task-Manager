// DirectoryStruct.h
#ifndef DIRECTORYSTRUCT_H
#define DIRECTORYSTRUCT_H

#include <string>
#include <vector>

struct Directory {
    std::string filesystem;
    std::string type;
    std::string size;
    std::string used;
    std::string avail;
    std::string usePercentage;
    std::string mountedOn;
};

std::vector<Directory> executeAndParseDf();

#endif 
