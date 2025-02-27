// Program 3 - HW2
// Author: <YOUR NAME>

#include <iostream>
#include <string>
#include <vector>
#include "image.h"
#include <map>
#include <cmath>
#include <fstream>
using namespace ComputerVisionProjects;

int main(int argc, char **argv){ 
  if (argc != 4) {
    std::cout << "Usage: " <<
      argv[0] << " {input_image_name} {output descriptions} {output_image_name}" << std::endl;
    return 0;
  }
  const std::string input_file(argv[1]);
  const std::string output_object_descriptions(argv[2]);
  const std::string output_file(argv[3]);

  std::cout << "Running p3 " << input_file << " " 
            << output_object_descriptions << " " << output_file << std::endl;

  // reading input image in to labeledImage
  Image labeledImage;
  if(ReadImage(input_file, &labeledImage) == 0){
    std::cout << "Invalid Image. " << std::endl;
    return 1;
  }
  
  std::map <int, int> area;
  std::map <int, double> xSum, ySum, xxSum, xySum, yySum;
  for(int row = 0; row < labeledImage.num_rows(); row++){
    for(int column = 0; column < labeledImage.num_columns(); column++){
      if(labeledImage.GetPixel(row, column) != 0){
        xSum[labeledImage.GetPixel(row, column)]+= row;
        ySum[labeledImage.GetPixel(row, column)]+= column;
        area[labeledImage.GetPixel(row, column)]++;
        xxSum[labeledImage.GetPixel(row, column)]+= row*row;
        xySum[labeledImage.GetPixel(row, column)]+= row*column;
        yySum[labeledImage.GetPixel(row, column)]+= column*column;
      }
    }
  }
  std::ofstream outputFile(output_object_descriptions);
  if (!outputFile) {
    std::cerr << "Error: Could not open output file." << std::endl;
    return 1;
  }

  for(auto x: area){
    double xCenter = xSum[x.first]/area[x.first];
    double yCenter = ySum[x.first]/area[x.first];

    // based on the formulas in the slides
    double a = xxSum[x.first] - area[x.first] * pow(xCenter, 2);;
    double b = 2 * (xySum[x.first] - area[x.first] * xCenter * yCenter);
    double c = yySum[x.first] - area[x.first] * pow(yCenter, 2);
    const double theta1 = atan2(b, a-c) / 2.0;
    const double theta1_degrees = 180.0 * theta1 / M_PI;
    const double e_min = a * sin(theta1) * sin(theta1) - b *sin(theta1) * cos(theta1) + c * cos(theta1) * cos(theta1);

    // Angle maximizing E
    const double theta2 = theta1 + M_PI / 2.0;

    // => Emax (same as Emin, but use theta2)
    const double e_max = a * sin(theta2) * sin(theta2) - b*sin(theta2) * cos(theta2) + c * cos(theta2) * cos(theta2);
    
    // Roundness
    const double roundness = e_min / e_max;
    DrawLine(xCenter, yCenter, (int)(xCenter + 35 * cos(theta1)), (int)(yCenter + 35 * sin(theta1)), 255, &labeledImage);
    outputFile << x.first << " " <<  xCenter << " " << yCenter << " " << e_min 
                << " " << area[x.first]<< " " << roundness << " " << theta1_degrees <<std::endl;
  }
  outputFile.close();

  //writing the image to the output
  if(!WriteImage(output_file, labeledImage)){
    std::cout << "Could not write " << std::endl;
    return 1;
  }
  return 0;
}
