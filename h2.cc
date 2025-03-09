// Program 2 - HW3
// Author: <YOUR NAME>

#include "image.h"
#include <iostream>
#include <string>

using namespace ComputerVisionProjects;

int main(int argc, char **argv){
  if (argc != 4) {
    std::cout << "Usage: " <<
      argv[0] << " {input_image_name} {threshold} {output_image_name}" << std::endl;
    return 0;
  }
  const std::string input_file(argv[1]);
  const int threshold = std::stoi(argv[2]);
  const std::string output_file(argv[3]);

  std::cout << "Running h2 " << input_file << " " 
            << threshold << " " << output_file << std::endl;
}
