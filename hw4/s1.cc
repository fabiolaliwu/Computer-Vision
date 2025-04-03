// Program 1 - HW4
// Author: <YOUR NAME>

#include "image.h"
#include <string>
#include <iostream>

using namespace ComputerVisionProjects;

int main(int argc, char **argv) {
    if (argc != 4) {
      std::cout << "Usage: "<<
        argv[0] << " {gray-level-sphere-file} {gray-level-threshold} {output-parameters-file}" << std::endl; 
        return 0;
    }
    const std::string input_file(argv[1]);
    const int threshold = atoi(argv[2]);
    const std::string output_file(argv[3]);

    std::cout << "Running s1 " << input_file << " " << threshold << " " << output_file << std::endl;
    return 0;
}
