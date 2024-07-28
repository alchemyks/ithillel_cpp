#include <iostream>
#include <string>
#include "lib/filewraper.h"



int main(int argc, char** argv){
    FileWrapper file("test.txt");
    file.write("Some text");
}