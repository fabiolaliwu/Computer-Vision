// Program 3 - HW4
// Author: <Fabiola Li Wu>

#include "image.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace ComputerVisionProjects;

int main(int argc, char **argv) {
    if (argc != 9) {
      std::cout << "Usage: " << argv[0] <<
        " {input-directions-file} {image1} {image2} {image3} {step} {threshold} {normals-output-file} {albedo-output-file}"
                << std::endl;
        return 0;
    }

    const std::string directions_file(argv[1]);
    const std::string image1_file(argv[2]);
    const std::string image2_file(argv[3]);
    const std::string image3_file(argv[4]);
    const int step = atoi(argv[5]);
    const int threshold = atoi(argv[6]);
    const std::string normals_output_file(argv[7]);
    const std::string albedo_output_file(argv[8]);

    Image image1, image2, image3;
    if (ReadImage(image1_file, &image1) == 0 ||ReadImage(image2_file, &image2) == 0 || ReadImage(image3_file, &image3) == 0) {
        std::cerr << "Error reading image." << std::endl;
        return 1;
    }
    // read directions
    std::ifstream directions_file_stream(directions_file);
    if (!directions_file_stream.is_open()) {
        std::cerr << "Error opening directions file: " << directions_file << std::endl;
        return 1;
    }
    std::vector<std::vector<double>> directions;
    while(directions_file_stream){
        std::vector<double> direction;
        double x, y, z;
        directions_file_stream >> x >> y >> z;
        if(directions_file_stream.eof())
            break;
        direction.push_back(x);
        direction.push_back(y);
        direction.push_back(z);
        directions.push_back(direction);
    }
    directions_file_stream.close();
  // for(int r = 0; r < directions.size(); r++){
  //   for(int c = 0; c < directions[r].size(); c++){
  //     std::cout << directions[r][c] << " ";
  //   }
  //   std::cout << std::endl;
  // }

   


    std::cout << "Running s3: " << directions_file << " " << image1_file <<  " " << image2_file << " " << image3_file
              << " " << step << " " << threshold << " " << normals_output_file << " "
              <<  " " << albedo_output_file << std::endl;
    return 0;
}
