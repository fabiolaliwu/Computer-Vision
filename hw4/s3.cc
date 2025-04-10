// Program 3 - HW4
// Author: <Fabiola Li Wu>

#include "image.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
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
    std::vector<std::vector<double>> S;
    double matrix[3][3];
    while(directions_file_stream){
        std::vector<double> direction;
        double x, y, z;
        directions_file_stream >> x >> y >> z;
        if(directions_file_stream.eof())
            break;
        direction.push_back(x);
        direction.push_back(y);
        direction.push_back(z);
        S.push_back(direction);
    }
    directions_file_stream.close();
  // for(int r = 0; r < directions.size(); r++){
  //   for(int c = 0; c < directions[r].size(); c++){
  //     std::cout << directions[r][c] << " ";
  //   }
  //   std::cout << std::endl;
  // }
  // put the directions into a 3x3 matrix
    for(int i = 0; i < S.size(); i++){
        matrix[i][0] = S[i][0];
        matrix[i][1] = S[i][1];
        matrix[i][2] = S[i][2];
        //std::cout << matrix[i][0] << " " << matrix[i][1] << " " << matrix[i][2] << std::endl;
    }

    // invert matrix
    double det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
                 matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
                 matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    if (det == 0) {
        std::cerr << "Ematrix not inverted" << std::endl;
        return 1;
    }
    double inv_det = 1.0 / det;
    double inverted[3][3];
    inverted[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) * inv_det;
    inverted[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) * inv_det;
    inverted[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) * inv_det;
    inverted[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) * inv_det;
    inverted[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) * inv_det;
    inverted[1][2] = (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2]) * inv_det;
    inverted[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) * inv_det;
    inverted[2][1] = (matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1]) * inv_det;
    inverted[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) * inv_det;
    // std::cout << "det: " << det << std::endl;
    // std::cout << "inverted: " << inverted[0][0] << " " << inverted[0][1] << " " << inverted[0][2] << std::endl;
    // std::cout << "inverted: " << inverted[1][0] << " " << inverted[1][1] << " " << inverted[1][2] << std::endl;
    // std::cout << "inverted: " << inverted[2][0] << " " << inverted[2][1] << " " << inverted[2][2] << std::endl;
    
    Image normals =image1, albedo = image1;
    for(int r = 0; r < normals.num_rows(); r++){
        for(int c = 0; c < normals.num_columns(); c++){
            albedo.SetPixel(r, c, 0);
        }
    }
   
    for(int r = 0; r < image1.num_rows(); r++){
        for(int c = 0; c < image1.num_columns(); c++){
            if(image1.GetPixel(r, c) > threshold && image2.GetPixel(r, c) > threshold && image3.GetPixel(r, c) > threshold){
                double i1 = image1.GetPixel(r, c), i2 = image2.GetPixel(r, c), i3 = image3.GetPixel(r, c);
                std::vector<double> I = {i1, i2, i3}, N(3, 0.0), n(3, 0.0);
                // inverse S * I = N
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++)
                        N[i] += inverted[i][j] * I[j];
                }
                // |N| or rho
                double rho = sqrt(N[0]*N[0] + N[1]*N[1] + N[2]*N[2]);
                albedo.SetPixel(r, c, rho*98);
                //std::cout << "rho: " << rho << std::endl;
                if(r%step ==0 && c%step == 0){
                    //n = N/rho
                    for(int i = 0; i < 3; i++)
                        n[i] = N[i]/rho;

                    // calculate the end points
                    int end_r = (int)(r + 6 + n[0]), end_c = (int)(c + 6 + n[1]);
                    end_r = std::min<int>(std::max(end_r, 0), image1.num_rows() - 1);
                    end_c = std::min<int>(std::max(end_c, 0), image1.num_columns() - 1);

                    // draw the line and set the pixels
                    DrawLine(r, c, end_r, end_c, 250, &normals);
                    normals.SetPixel(r-1, c, 255);
                    normals.SetPixel(r+1, c, 255);
                    normals.SetPixel(r, c-1, 255);
                    normals.SetPixel(r, c+1, 255);
                    normals.SetPixel(r, c, 0);
                }
            }
        }
    }
    // write the output
    if(!WriteImage(normals_output_file, normals)){
        std::cerr << "Error writing normals image: " << normals_output_file << std::endl;
        return 1;
    }
    if(!WriteImage(albedo_output_file, albedo)){
        std::cerr << "Error writing albedo image: " << albedo_output_file << std::endl;
        return 1;
    }
    std::cout << "Running s3: " << directions_file << " " << image1_file <<  " " << image2_file << " " << image3_file
              << " " << step << " " << threshold << " " << normals_output_file << " "
              <<  " " << albedo_output_file << std::endl;
    return 0;
}
