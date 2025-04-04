README FILE

<Fabiola Li Wu>

s1:
What I did: 
- Read the input file
- Convert the image to binary image based on the threshold
- Calculate the centroid by passing through all the pixels and get x and y and divide it by the area which is the sum of all the pixels.
- Calculte the radius by using the formula provided in the slides
- Write the output to the file separated by a space.

Issues: 
I was running it with this command: ./s.cc sphere0.pgm 128 output.txt when I should have ran it with: ./s1 sphere0.pgm 128 output.txt
Running it with low threshold will have a greater radius because the program will think that the sphere is the whole image
Running it with medium threshold will have a circle of 219 367 81.
Running it with a high threshold will make the radium of the circle smaller because after the binary scan, will detect more black spot
than white spot.


s2:



s3:

