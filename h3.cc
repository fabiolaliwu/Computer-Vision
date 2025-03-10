// Program 3 - HW3
// Author: Fabiola Li Wu

#include "image.h"
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
using namespace ComputerVisionProjects;

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cout << "Usage: " <<
            argv[0] << " {input_binary_image_name} {output_hough_image_name} {output_hough_array_name}" << std::endl;
        return 0;
    }

    const std::string input_filenm(argv[1]);
    const std::string output_pgm_filenm(argv[2]);
    const std::string output_txt_filenm(argv[3]);

    std::cout << "Running h3: " << input_filenm << " " << output_pgm_filenm << " " << output_txt_filenm << std::endl;

    // Reading input image into inputImage
    Image inputImage;
    if (ReadImage(input_filenm, &inputImage) == 0) {
        std::cout << "Invalid Image. " << std::endl;
        return 1;
    }

    int rhoRes = (int)std::sqrt(pow(inputImage.num_columns(), 2) + pow(inputImage.num_rows(), 2));
    int thetaRes = 180;
    std::vector<std::vector<int>> houghSpace(rhoRes, std::vector<int>(thetaRes, 0));

    for (int row = 0; row < inputImage.num_rows(); row++) {
        for (int column = 0; column < inputImage.num_columns(); column++) {
            if (inputImage.GetPixel(row, column) != 0) { 
                for (int t = 0; t < thetaRes; t++) {
                    double theta = (t * M_PI) / thetaRes;
                    double rho = column * cos(theta) + row * sin(theta);
                    int rhoIndex = (int)(rho + rhoRes / 2);
                    if (rhoIndex >= 0 && rhoIndex < rhoRes) {
                        houghSpace[rhoIndex][t]++;
                    }
                }
            }
        }
    }


   std::ofstream outFile(output_txt_filenm);
    if (!outFile)
        return 1;

    // output Hough–voting array

    outFile.close();



    if (!WriteImage(output_pgm_filenm, inputImage)) {
        std::cout << "Could not write Hough space image." << std::endl;
        return 1;
    }

    return 0;
}
