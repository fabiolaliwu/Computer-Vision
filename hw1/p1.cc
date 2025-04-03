// Program 1 - HW2
// Author: Fabiola Li Wu

#include <iostream>
#include <string>

#include "image.h"
using namespace ComputerVisionProjects;

int main(int argc, char **argv){
  // given code
  if (argc != 4) {
    std::cout << "Usage: " <<
      argv[0] << " {input_image_name} {threshold} {output_image_name}" << std::endl;
    return 0;
  }
  const std::string input_file(argv[1]);
  const int threshold = std::stoi(argv[2]);
  const std::string output_file(argv[3]);

  std::cout << "Running p1 " << input_file << " " 
            << threshold << " " << output_file << std::endl;

  // reading input image in to convertedImage
  Image convertedImage;
  if(ReadImage(input_file, &convertedImage) == 0){
    std::cout << "Invalid Image. " << std::endl;
    return 1;
  }
   
  //changing colors of the image
  for(int r = 0; r < convertedImage.num_rows(); r++){
    for(int c = 0; c < convertedImage.num_columns(); c++){
      if(convertedImage.GetPixel(r, c) < threshold)
        convertedImage.SetPixel(r, c, 0);
      else
        convertedImage.SetPixel(r, c, 255);
    }
  }
  
  //writing the image to the output
  if(!WriteImage(output_file, convertedImage)){
    std::cout << "Could not write " << std::endl;
    return 1;
  }
  return 0;
}
