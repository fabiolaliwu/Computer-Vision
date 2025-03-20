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
    int rhoRes = (int)std::sqrt(pow(inputImage.num_rows(), 2) + pow(inputImage.num_columns(), 2));
    int thetaRes = 180;
    // accumulator 
    std::vector<std::vector<int>> accumulator(thetaRes, std::vector<int>(rhoRes, 0));
    for (int row = 0; row < inputImage.num_rows(); row++) {
        for (int column = 0; column < inputImage.num_columns(); column++) {
            if (inputImage.GetPixel(row, column) != 0) { 
                for (int t = 0; t < thetaRes; t++) {
                    double theta = (t * M_PI) / 180.0;
                    double rho = row * cos(theta) + column * sin(theta);
                    int rhoIndex = (int)(rho);
                    if (rhoIndex >= 0 && rhoIndex < rhoRes) {
                        // std::cout << "Vote " << rhoIndex << " " << t << std::endl;
                        accumulator[t][rhoIndex]++;
                    }
                }
            }
        }
    }
    Image outputImage; 
    outputImage.AllocateSpaceAndSetSize(thetaRes, rhoRes);
    outputImage.SetNumberGrayLevels(255);
    for (int row = 0; row < thetaRes; row++) {
        for (int column = 0; column < rhoRes; column++) {
            //if (accumulator[row][column] > 100) std::cout << accumulator[row][column] << std::endl;
            outputImage.SetPixel(row, column, accumulator[row][column]);
        }
    }
   std::ofstream outFile(output_txt_filenm);
    if (!outFile)
        return 1;

    // output Hough–voting array
    for(int row = 0; row < accumulator.size(); row ++){
        for(int column = 0; column < accumulator[0].size(); column++)
            outFile << accumulator[row][column] << " ";
    }
    outFile.close();
    if (!WriteImage(output_pgm_filenm, outputImage)) {
        std::cout << "Could not write Hough space image." << std::endl;
        return 1;
    }
    return 0;
}
