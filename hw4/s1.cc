// Program 1 - HW4
// Author: <Fabiola Li Wu>

#include "image.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

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

    Image inputImage;
    if(ReadImage(input_file, &inputImage) == 0){
      std::cout << "Invalid Image. " << std::endl;
      return 1;
    }
    Image binaryImage = inputImage;

    // Convert to binary image based on threshold
    for(int r = 0; r < inputImage.num_rows(); r++){
      for(int c = 0; c < inputImage.num_columns(); c++){
        int pixel = inputImage.GetPixel(r, c);
        if(pixel > threshold)
          binaryImage.SetPixel(r, c, 255);
        else
          binaryImage.SetPixel(r, c, 0);
      }
    }

    // calculate teh centroid
    int sumx = 0, sumy = 0, area = 0;
    for(int r = 0; r < binaryImage.num_rows(); r++){
      for(int c = 0; c < binaryImage.num_columns(); c++){
        int pixel = binaryImage.GetPixel(r, c);
        if(pixel == 255){
          sumx += r;
          sumy += c;
          area++;
        }
      }
    }
    int centroidX = sumx / area;
    int centroidY = sumy / area;
    // radius
    int radius = 0;
    for(int r = 0; r < binaryImage.num_rows(); r++){
      for(int c = 0; c < binaryImage.num_columns(); c++){
        int pixel = binaryImage.GetPixel(r, c);
        if(pixel == 255){
          int dist = (int)(std::sqrt(pow((centroidX - r),2) + pow((centroidY - c),2)));
          if(dist > radius)
            radius = dist;
        }
      }
    }
    // write the output
    std::ofstream outputFile(output_file);
    if(!outputFile.is_open()){
      std::cout << "Could not write " << std::endl;
      return 1;
    }
    outputFile << centroidX << " " << centroidY << " "  << radius << std::endl;
    outputFile.close();
    std::cout << "Running s1 " << input_file << " " << threshold << " " << output_file << std::endl;
    return 0;
}
