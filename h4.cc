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
    // std::cout << "Input image: " << input_filenm << std::endl;
    // std::cout << "Input Hough array: " << input_array_filenm << std::endl;

    std::fstream inputVector(input_array_filenm);
    if(!inputVector){
      std::cout << "File does not exist."<< std::endl;
      return 1;
    }
    
    //inputVector >> rhoRes >> thetaRes;
    //std::cout << "rhoRes: " << rhoRes << ", thetaRes: " << thetaRes << std::endl;
    int thetaRes = 180;
    int rhoRes = (int)std::sqrt(pow(inputImage.num_rows(), 2) + pow(inputImage.num_columns(), 2));


    std::vector<std::vector<int>> accumulator(thetaRes, std::vector<int>(rhoRes, 0));
    //std::cout << accumulator.size() << " " << accumulator[0].size();
    for(int row = 0; row < accumulator.size(); row ++){
      for(int column = 0; column < accumulator[0].size(); column++){
        
        inputVector >> accumulator[row][column];
        //std::cout << "Checking accumulator[" << row << "][" << column << "]: " << accumulator[row][column] << std::endl;

        //std::cout << accumulator[row][column] << " ";
      }
      //  std::cout << std::endl;
    }
    inputVector.close();

    //std::cout << "Ran until here? " << std::endl;
    Image outputImage = inputImage; 
    //outputImage.AllocateSpaceAndSetSize(inputImage.num_rows(), inputImage.num_columns());
    std::cout << "Image Row:  " << outputImage.num_rows() << " Image Column: " << outputImage.num_columns() << std::endl;
    //outputImage.SetNumberGrayLevels(255);
    //std::cout << "running here?" <<std::endl;
    //std::cout << "Checking accumulator[" << accumulator.size() << "][" << accumulator[0].size() << "]: " << accumulator[row][column] << std::endl;


    for (int row = 1; row < thetaRes - 1; row++) { 
      for (int column = 1; column < rhoRes - 1; column++) { 
        //std::cout << "running here?" <<std::endl;
        if (accumulator[row][column] > threshold &&
              accumulator[row][column] > accumulator[row-1][column] &&  
              accumulator[row][column] > accumulator[row+1][column] &&  
              accumulator[row][column] > accumulator[row][column-1] &&  
              accumulator[row][column] > accumulator[row][column+1] &&  
              accumulator[row][column] > accumulator[row-1][column-1] && 
              accumulator[row][column] > accumulator[row-1][column+1] && 
              accumulator[row][column] > accumulator[row+1][column-1] && 
              accumulator[row][column] > accumulator[row+1][column+1]) {
              double theta = (row * M_PI) / 180.0;
              int rho = column;
              int x = outputImage.num_rows() - 1;
              int y = outputImage.num_columns() - 1;

              std::vector<std::pair<int, int>> validPairs;
              pair<int, int> first = {0, std::lround(rho / std::sin(theta))};
              if (first.second <= y && first.second >= 0)
                  validPairs.push_back(first);

              pair<int, int> second = {std::lround(rho / std::cos(theta)), 0};
              if ((second.first <= x) && second.first >= 0)
                  validPairs.push_back(second);

              pair<int, int> third = {x, std::lround((rho - x * std::cos(theta)) / std::sin(theta))};
              if ((third.second <= y) && (third.second >= 0))
                  validPairs.push_back(third);

              pair<int, int> fourth = {std::lround((rho - y * std::sin(theta)) / std::cos(theta)), y};
              if ((fourth.first <= x) && (fourth.first >= 0))
                  validPairs.push_back(fourth);

              if (validPairs.size() >= 2){                
                //std::cout << validPairs[0].first << " " << validPairs[0].second << " " << validPairs[1].first << " "<< validPairs[1].second << std::endl;
                DrawLine(validPairs[0].first, validPairs[0].second, validPairs[1].first, validPairs[1].second, 100, &outputImage);
              }
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

