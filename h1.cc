// Program 1 - HW3
// Author: Fabiola Li Wu

#include "image.h"
#include <iostream>

using namespace ComputerVisionProjects;


int main(int argc, char **argv){
    if (argc != 3) {
      std::cout << "Usage: " <<
        argv[0] << " {input_image_name} {output_edge_image_name}" << std::endl;
        return 0;
    }

    const std::string input_file(argv[1]);
    const std::string output_file(argv[2]);

    std::cout << "Running h1 " << input_file << " " << output_file << std::endl;

    return 0;
}
