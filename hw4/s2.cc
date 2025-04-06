// Program 2 - HW4
// Author: <Fabiola Li Wu>

#include "image.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace ComputerVisionProjects;

std::vector<double> lightDirection(Image &sphere, int circlex, int circley, int circleRadius) {
  // find brightest pixel in the circle
  int maxPixel = 0, maxRow = 0, maxCol = 0;
  for(int row = 0; row < sphere.num_rows(); row++){
    for(int col = 0; col <sphere.num_columns(); col++){
      if(sphere.GetPixel(row, col) > maxPixel){
        int dist = (int)(std::sqrt(pow((circlex - row),2) + pow((circley - col),2)));
        if(dist < circleRadius){
          maxPixel = sphere.GetPixel(row, col);
          maxRow = row;
          maxCol = col;
        }
      }
    }
  }
  double x = (double)(maxRow - circlex);
  double y = (double)(maxCol - circley);
  double z = std::sqrt(circleRadius * circleRadius - x * x - y * y);
  return {x, y, z};
}

int main(int argc, char **argv) {
    if (argc != 6) {
      std::cout << "Usage: " << argv[0] <<
        " {input-parameters-file} {sphere-image-1} {sphere-image-2} {sphere-image-3} {output-directions-file}" 
                << std::endl;
      return 0;
    }

    const std::string parameters_file(argv[1]);
    const std::string sphere_image1(argv[2]);
    const std::string sphere_image2(argv[3]);
    const std::string sphere_image3(argv[4]);
    const std::string output_directions_file(argv[5]);

    // Read the parameters
    int circlex, circley, circleRadius;
    std::ifstream param_file(parameters_file);
    if (param_file.is_open()) {
        param_file >> circlex >> circley >> circleRadius;
        param_file.close();
    } else {
        std::cerr << "Error opening parameters file: " << parameters_file << std::endl;
        return 1;
    }
    param_file.close();

    // read circle images
    Image sphere1, sphere2, sphere3;
    if (ReadImage(sphere_image1, &sphere1) == 0) {
        std::cerr << "Error reading sphere image 1: " << sphere_image1 << std::endl;
        return 1;
    }
    if (ReadImage(sphere_image2, &sphere2) == 0) {
        std::cerr << "Error reading sphere image 2: " << sphere_image2 << std::endl;
        return 1;
    }
    if (ReadImage(sphere_image3, &sphere3) == 0) {
        std::cerr << "Error reading sphere image 3: " << sphere_image3 << std::endl;
        return 1;
    }

    std::vector<std::vector<double>> lightDirections;
    lightDirections.push_back(lightDirection(sphere1, circlex, circley, circleRadius));
    lightDirections.push_back(lightDirection(sphere2, circlex, circley, circleRadius));
    lightDirections.push_back(lightDirection(sphere3, circlex, circley, circleRadius));

    // write the output
    std::ofstream outputFile(output_directions_file);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file: " << output_directions_file << std::endl;
        return 1;
    }
    for (auto x : lightDirections)
        outputFile << x[0] << " " << x[1] << " " << x[2] << std::endl;
    outputFile.close();
    std::cout << "Running s2 " << parameters_file << " " << sphere_image1 << " " << sphere_image2
              << " " << sphere_image3 << " " << output_directions_file << std::endl;
    return 0;
}
