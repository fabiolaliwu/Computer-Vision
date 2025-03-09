// Program 3 - HW3
// Author: <YOUR NAME>

#include "image.h"
#include <iostream>
#include <string>

using namespace ComputerVisionProjects;

int main(int argc, char **argv){
    if (argc != 4) {
       std::cout << "Usage: " <<
         argv[0] << " {input_binary_image_name} {output_hough_image_name} {output_hough_array_name}" << std::endl;
        return 0;
    }
    const std::string input_filenm(argv[1]);
    const std::string output_pgm_filenm(argv[2]);
    const std::string output_txt_filenm(argv[3]);

    std::cout << "Running h3: " << input_filenm << " " << output_pgm_filenm << " " << output_txt_filenm << std::endl;
    return 0;
}
