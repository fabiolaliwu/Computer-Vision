// Program 1 - HW3
// Author: Fabiola Li Wu

#include "image.h"
#include <iostream>
#include <vector>
#include <cmath>

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

    // reading input image in to convertedImage
    Image inputImage;
    if(ReadImage(input_file, &inputImage) == 0){
      std::cout << "Invalid Image. " << std::endl;
      return 1;
    }
    Image outputImage = inputImage;
    const std::vector<const std::vector<int>> gradientX = {{-1, 0, 1},
                                              {-2, 0, 2},
                                              {-1, 0, 1}};
    const std::vector<const std::vector<int>> gradientY = {{1, 2, 1},
                                              {0, 0, 0},
                                              {-1, -2, -1}};
    for(int r = 1; r < inputImage.num_rows() - 1; r++){
      for(int c = 1; c < inputImage.num_columns() - 1; c++){
        int x = 0, y = 0;
        // Sobel filter
        for (int j = -1; j <= 1; ++j) {
            for (int i = -1; i <= 1; ++i) {
                int pixel = inputImage.GetPixel(r + i, c + j);
                x += (pixel * gradientX[j + 1][i + 1]);
                y += (pixel * gradientY[j + 1][i + 1]);
            }
        }
        int mag = (int)(std::sqrt(pow(x,2) + pow(y,2)));
        if(mag > 255)
          outputImage.SetPixel(r, c, 255);
        else
          outputImage.SetPixel(r, c, mag);
      }
    }
    //writing the image to the output
    if(!WriteImage(output_file, outputImage)){
      std::cout << "Could not write " << std::endl;
      return 1;
    }
    return 0;
}
