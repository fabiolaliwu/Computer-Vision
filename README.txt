# CS493-HW3

## To compile: make all
Alternatively: make h1, make h2, make h3, make h4

--> Add information based on your programs

Working parts: all of the parts are compiling in my computer, the output of some of the are 
slightly different from the sample ones, but I asked professor and he said that it is fine.

h1.cc:  
It gets an image as input and it outputs an edged image.
1. Reads the image from the file and I declare an extra variable called outputImage so that 
I do not write on the input image.
2. I declared a table which is the sobel filter in order to go through the input image and find 
the edges of the image.
3. I go through the image and for each pixel, I add them to x and y and when itis done, then I 
use the given formula of mag equal to square root of x square plus y square. If the total is 
greater than 255, then print a white pixel in the outputImage, else print what ever was in mag.
4. I wrote back the outputImage to the outputfile.
ISSUES:
1. First issue that I encounter when I was doing this part of the homework it was that I was 
starting to check from 0, when I should have started from -1. I was not checking the pixels 
that were in the border of the image.


h2.cc:
It gets as input the reuslt of h1 and a threshold, and it outputs a binary image.
1. Starts by reading the input image and store it in the image object called convertedImage.
2. It goes through each pixel of the convertedImage, and if the pixel is greater than the
threshold, then, it outputs a white pixel, otherwise it outputs a black pixel.
3. Writes the convertedImage to the output_file.
ISSUES:
1. I input 150 for threshold and parts of the images were "lost", so instead of inputing 150 
as threshold, I input 50 and a lot of parts were still missing, so I input 25 and it was 
slightly better.

h3.cc: 
It gets the binary image from h2.cc as the input and it outputs a Hough image and a text file
of voting array.
1. Put the input image in inputImage Image object.
2. Declare rhoRes equal to the equation that is on the slides.
3. Declare thetaRes as 180 because it goes form 0 to pi, but we know that pi is 180 degrees.
4. Declare an accumulator which will store the votes of rho and theta.
5. It iterates through the image and voting. It checks if the pixel is not 0, if is non-zero 
pixel, then it calculates the theta and rho, and go through 0-rhoRes in order to set it to 
the accumulator.

