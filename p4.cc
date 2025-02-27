// Program 3 - HW2
// Author: <YOUR NAME>

#include <iostream>
#include <string>

#include "image.h"
using namespace ComputerVisionProjects;

int main(int argc, char **argv){
  if (argc!=4) {
    std::cout << "Usage: " <<
      argv[0] << " {input_image_name} {input descriptions} {output_image_name}" << std::endl;
    return 0;
  }
  const std::string input_file(argv[1]);
  const std::string input_object_descriptions(argv[2]);
  const std::string output_file(argv[3]);

  std::cout << "Running p4 " << input_file << " " 
            << input_object_descriptions << " " << output_file << std::endl;
  
  Image inputImage;
  if(ReadImage(input_file, &inputImage) == 0){
    std::cout << "Invalid Image. " << std::endl;
    return 1;
  }



  //writing the image to the output
  if(!WriteImage(output_file, inputImage)){
    std::cout << "Could not write " << std::endl;
    return 1;
  }

  return 0;
}








