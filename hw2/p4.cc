// Program 4 - HW2
// Author: <Fabiola Li Wu>

#include <iostream>
#include <string>

#include "image.h"
using namespace ComputerVisionProjects;

struct items{
  int label;
  double xCenter;
  double yCenter;
  double e_min;
  int area;
  double roundness;
  double theta1_degrees;
};

int main(int argc, char **argv){
  if (argc!=4) {
    std::cout << "Usage: " <<
      argv[0] << " {input_image_name} {input descriptions} {output_image_name}" << std::endl;
    return 0;
  }
  const std::string input_file(argv[1]);
  const std::string input_object_descriptions(argv[2]);
  const std::string output_file(argv[3]);

  std::cout << "Running p4 " << input_file << " " 
            << input_object_descriptions << " " << output_file << std::endl;
  
  //image unput
  Image inputImage;
  if(ReadImage(input_file, &inputImage) == 0){
    std::cout << "Invalid Image. " << std::endl;
    return 1;
  }


  for(int row =0; row < inputImage.num_rows(); row++){
    for(int column =0; column < inputImage.num_columns(); column++){

    }
  }
  


  //writing the image to the output
  if(!WriteImage(output_file, inputImage)){
    std::cout << "Could not write " << std::endl;
    return 1;
  }

  return 0;
}










// #include <iostream>
// #include <fstream>
// #include <string>
// #include <cmath>
// #include <vector>
// #include "image.h"
// #include "DisjSets.h"

// using namespace std;
// using namespace ComputerVisionProjects;

// struct ObjectDescription {
//     int id;
//     double x_center;
//     double y_center;
//     double area;
//     double perimeter;
//     double circularity;
//     double orientation;
// };

// bool ReadObjectDescriptions(const string &filename, vector<ObjectDescription> &objectDescriptions) {
//     ifstream infile(filename);
//     if (!infile.is_open()) {
//         cerr << "Error: Could not open object descriptions file." << endl;
//         return false;
//     }

//     ObjectDescription obj;
//     while (infile >> obj.id >> obj.x_center >> obj.y_center >> obj.area >> obj.perimeter >> obj.circularity >> obj.orientation) {
//         objectDescriptions.push_back(obj);
//     }

//     infile.close();
//     return true;
// }

// bool CompareObjects(const ObjectDescription &model, const ObjectDescription &detected, double threshold = 0.1) {
//     // Compare positions (X and Y)
//     double position_diff = sqrt(pow(model.x_center - detected.x_center, 2) + pow(model.y_center - detected.y_center, 2));
    
//     // Compare area
//     double area_diff = fabs(model.area - detected.area);
    
//     // Compare circularity
//     double circularity_diff = fabs(model.circularity - detected.circularity);
    
//     // Compare orientation (we allow some small tolerance in orientation difference)
//     double orientation_diff = fabs(model.orientation - detected.orientation);
//     if (orientation_diff > 180.0) {
//         orientation_diff = 360.0 - orientation_diff; // Handle wrap-around for angles
//     }

//     // If all differences are below a certain threshold, consider it a match
//     if (position_diff < threshold && area_diff < threshold && circularity_diff < threshold && orientation_diff < threshold) {
//         return true;
//     }

//     return false;
// }

// int main(int argc, char **argv) {
//     if (argc != 4) {
//         cout << "Usage: " << argv[0] << " {input_labeled_image} {input_object_descriptions} {output_image}" << endl;
//         return 0;
//     }

//     const string input_image_filename(argv[1]);
//     const string input_descriptions_filename(argv[2]);
//     const string output_image_filename(argv[3]);

//     // Read input labeled image
//     Image labeledImage;
//     if (!ReadImage(input_image_filename, &labeledImage)) {
//         cerr << "Error: Could not read input labeled image." << endl;
//         return 1;
//     }

//     // Read object descriptions from the model database
//     vector<ObjectDescription> modelObjects;
//     if (!ReadObjectDescriptions(input_descriptions_filename, modelObjects)) {
//         cerr << "Error: Could not read object descriptions." << endl;
//         return 1;
//     }

//     // Compare objects in the labeled image with the model database
//     for (int row = 0; row < labeledImage.num_rows(); ++row) {
//         for (int col = 0; col < labeledImage.num_columns(); ++col) {
//             int object_id = labeledImage.GetPixel(row, col);
//             if (object_id != 0) { // If it's part of an object
//                 // Gather the object's properties
//                 ObjectDescription detected;
//                 detected.id = object_id;
//                 detected.x_center = row;
//                 detected.y_center = col;
//                 detected.area = 1; // Placeholder, you would calculate the area based on connected components
//                 detected.perimeter = 1; // Placeholder, you would calculate the perimeter
//                 detected.circularity = 1; // Placeholder, calculate circularity
//                 detected.orientation = 0; // Placeholder, calculate orientation

//                 // Compare this object with the model objects
//                 for (const auto &model : modelObjects) {
//                     if (CompareObjects(model, detected)) {
//                         // If it matches, mark it in the output image
//                         DrawLine(detected.x_center, detected.y_center,
//                                  detected.x_center + 35 * cos(detected.orientation),
//                                  detected.y_center + 35 * sin(detected.orientation),
//                                  255, &labeledImage);
//                     }
//                 }
//             }
//         }
//     }

//     // Write the output image with recognized objects
//     if (!WriteImage(output_image_filename, labeledImage)) {
//         cerr << "Error: Could not write output image." << endl;
//         return 1;
//     }

//     cout << "Object recognition completed successfully." << endl;
//     return 0;
// }
