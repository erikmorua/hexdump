#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>

class xbd{

private:
    long length;
public:
    unsigned char* readFile(const char*);
    void binPrint(unsigned char*, long);
   std::string convert(int);
    void hexPrint(unsigned char*, long);
};
