// Program 2 - HW4
// Author: <Fabiola Li Wu>

#include "image.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace ComputerVisionProjects;

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

    
    




   

    std::cout << "Running s2 " << parameters_file << " " << sphere_image1 << " " << sphere_image2
              << " " << sphere_image3 << " " << output_directions_file << std::endl;
    return 0;
}
