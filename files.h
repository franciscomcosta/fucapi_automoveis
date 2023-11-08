#ifndef FILES_H
#define FILES_H

using namespace std;

#include <string>
#include <fstream>

class Fs{
    void createFile(string fileName);
    bool fileExist(string path);
};

#endif