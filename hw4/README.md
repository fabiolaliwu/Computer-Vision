README FILE

<Fabiola Li Wu>
Working parts: Ran s1.cc, s2.cc, and s3.cc, and they are all working and printing the expected outputs.

s1:
What I did: 
- Read the input file
- Convert the image to binary image based on the threshold
- Calculate the centroid by passing through all the pixels and get x and y and divide it by the area which is the sum of all the pixels.
- Calculte the radius by using the formula provided in the slides
- Write the output to the file separated by a space.

Issues: 
- I was running it with this command: ./s.cc sphere0.pgm 128 output.txt when I should have ran it with: ./s1 sphere0.pgm 128 output.txt
- Running it with low threshold will have a greater radius because the program will think that the sphere is the whole image
- Running it with medium threshold will have a circle of 219 367 81.
- Running it with a high threshold will make the radium of the circle smaller because after the binary scan, will detect more black spot than white spot.


s2:
What I did: 
- get the parameters and place them in a variable.
- declare a vector of double vector calles lightDirections in order to store them.
- call a helper function called lightDirection in order to find the brightest pixel and find x by getting the difference of x brightest and x from the center, same for y, and for z, I used the formula provided in class which is to get the square root of the radius of the circle squared minus x squared minus y squared. 
- push back the vector of values maxPixel times x divided by the length, maxPixel times y divided by the length, maxPixel times z divided by the length to the lightDirections vector.
- Write the results to the output file.

Isuues: 
- I was confusing the x and the y because I was putting all the rows in x when they should be in y and I was putting all the columns in y when they should be in x.


s3:
- got all the images, steps, threshold, directions and put them in variables.
- declared a 3x3 matrix to store the directions, and inverteded the matrix.
- go through all the pixels, set vetor I with the pixels from the images.
- N is the multiplication of the inverse matrix and the I vector.
- set rho to be the square root of N[0] square, N[1] square, N[2] square.
- set the rho * 98 to be the pixel in the rho image because rho is VERY small.
- For the normals, normals equal to the N/rho.
- Then I calculted the endpoint of the line that I had to draw in the normals image. I also drew in the pixels above, below, right and left to make it look like more like a needle.
- Wrote the images to the output.

Issues:
- I did not make the albedo image to be all black before setiing the pixels, so I got the same background as image1.
- I was using a very low step that was making my image look almost all white, so finally I set it to 10
- making the threshold higher, will make the image look darker, and making it it lower will make the albedo image look brighter. Finally, I decided to have the threshold to be 84 to look exactly the same as the example output.
