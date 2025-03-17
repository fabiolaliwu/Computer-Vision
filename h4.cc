// Program 4 - HW3
// Author: Fabiola Li Wu

#include <iostream>
#include <string>
#include <fstream>
#include "image.h"
#include "DisjSets.h"
#include <cmath>
using namespace ComputerVisionProjects;

int main(int argc, char **argv){
    if (argc != 5) {
      std::cout << " Usage: " <<
        argv[0] << " input_image input_hough_array input_threshold output_line_image" << std::endl;
      return 0;
    }
    const std::string input_filenm(argv[1]);
    const std::string input_array_filenm(argv[2]);
    const int threshold = std::stoi(argv[3]);
    const std::string output_line_filenm(argv[4]);

    std::cout << "Running h4: " << input_filenm << " " << input_array_filenm << " " << threshold
              << "  " << output_line_filenm << std::endl;

    Image inputImage;
    if(ReadImage(input_filenm, &inputImage) == 0){
      std::cout << "Invalid Iamge" << std::endl;
      return 1;
    }
    std::cout << "Input image: " << input_filenm << std::endl;
    std::cout << "Input Hough array: " << input_array_filenm << std::endl;

    std::fstream inputVector(input_array_filenm);
    if(!inputVector){
      std::cout << "File does not exist."<< std::endl;
      return 1;
    }
    int rhoRes, thetaRes;
    inputVector >> rhoRes >> thetaRes;
    std::cout << "rhoRes: " << rhoRes << ", thetaRes: " << thetaRes << std::endl;

    std::vector<std::vector<int>> accumulator(rhoRes, std::vector<int>(thetaRes, 0));
    for(int row = 0; row < accumulator.size(); row ++){
      for(int column = 0; column < accumulator[0].size(); column++)
        inputVector >> accumulator[row][column];
    }
    inputVector.close();

    std::cout << "Ran until here? " << std::endl;
    Image outputImage = inputImage; 
    outputImage.AllocateSpaceAndSetSize(inputImage.num_rows(), inputImage.num_columns());
    std::cout << "Row:  " << outputImage.num_rows() << " Column: " << outputImage.num_columns() << std::endl;
    outputImage.SetNumberGrayLevels(255);
    for (int row = 1; row < outputImage.num_rows() - 1; row++) {
        for (int column = 1; column < outputImage.num_columns() - 1; column++) {
            if (accumulator[row][column] > accumulator[row-1][column] &&
                accumulator[row][column] > accumulator[row-1][column-1] &&
                accumulator[row][column] > accumulator[row-1][column+1] &&
                accumulator[row][column] > accumulator[row+1][column+1] &&
                accumulator[row][column] > accumulator[row][column+1] &&
                accumulator[row][column] > accumulator[row+1][column] &&
                accumulator[row][column] > accumulator[row+1][column-1] &&
                accumulator[row][column] > accumulator[row][column-1] &&
                accumulator[row][column] > threshold) {
                double theta = (column * M_PI) / 180.0;
                double rho = row;
                double x = outputImage.num_columns() - 1;
                double y = outputImage.num_rows() - 1;
                std::vector<std::pair<int, int>> validPairs;
                pair<double, double> first = {0, rho/std::sin(theta)};
                if(rho/std::sin(theta) > y)
                  validPairs.push_back(first);
                pair<double, double> second = {(rho/std::cos(theta)), 0};
                if((rho/std::cos(theta)) > x)
                  validPairs.push_back(second);
                pair<double, double> third = {x, (rho - x * std::cos(theta))/std::sin(theta)};
                if((rho - x * std::cos(theta))/std::sin(theta) > y)
                  validPairs.push_back(third);
                pair<double, double> fourth = {(rho - y * std::sin(theta))/std::cos(theta), y};
                if((rho - y * std::sin(theta))/std::cos(theta) > x)
                  validPairs.push_back(fourth);
                if(validPairs.size() >= 2)
                  DrawLine(validPairs[0].first, validPairs[0].second, validPairs[1].first, validPairs[1].second, 130, &outputImage);
                
            }
        }
    }

    // std::cout << "Writing image to: " << output_line_filenm << std::endl;
    if (!WriteImage(output_line_filenm, outputImage)) {
        std::cout << "Could not write Hough space image." << std::endl;
        return 1;
    }
    return 0;
}

