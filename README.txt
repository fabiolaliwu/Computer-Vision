Author: <Fabiola Li Wu>
CSCI 49369 - Computational Vision

# Provide short descriptions of your algorithms / problem you encountered.

p1
 What I did:
 I basically convert the input file into an image with the Image class that is given.
 I used a condition so it exits with error if the file could not be converted into image.
 I go through each pixel of the image by using a nested for loop whcih takes a time complexity of O(n^2)
 I check the pixel and if it is greater than the threshold, then I set it to 255 which is white color,
 otherwise, I set it to 255 whcih is white color.
 At the end I write back teh changes I did in the Iamge object using the function in the Image class.

 Isuue: 
 For Program 1, I set a default Threshold value to 250 but it was too high so 
 I saw the image all black, that was thefirst issue I encounter.


p2
What I did: 
I did the same as in program one which I converted the input file into image, but this time I did it twice.
I set a label counter because we do not want to use the same label for each item in the image. 
I did two passes and on the first pass, I went through all the pixels starting from pixel one and only doing the ones in white color because we basically do not care about the background.
I used the techniqye taught in class which is checking all the neighbor to see if they are all background, if so then we set a new label for the obejct that we have encountered.
Otherwise, we check the other cases explained in class.
On the second pass, I iterate through every pixel of the labeled image obeject that we initialized. 
Then for each pixel of the image, we find the root label using disjSets.find(), ensuring all equivalent labels are resolved. and we assigns the root label to every pixel, replacing initial labels with their labels.

Issues: 
I was seeing different scales of grey, and I thought that I messed up at the end becaseu I couldnt see the other objects, bit it was because tehy were "hidden"
I did not read the disjoin class, so I had no clue on how to do it until I sought help from our professor.
I was writing the convertedImage and not the labeledImage to the output file, so I thought that my code was not working.
 
p3
What I did:
I did the same as in p1 and p2 which is to read the unput file at the very beginnign and write the converted image to the output file using the fucntion in the Image class
Then the next thing I did it is to go through every pixel of theimage and every row, column, area, multplying x and y, y and y, and x and x, which we will need later.
We open the text file to start doing the math and writing into the results to the file.
I start off by setting the x and y of the center, then we the rest of the variables, all these formulas used are on the slides that professor taught in class.
Our professor also provided us the code from line 61-72 so all these lines of code are taken from his slides.
Then I use the DrawLine function given in the Image class in order to draw a line of the orientation of the object/item labeled.
Then, I close the file and write teh image to the output image.

Isuues: 
The main issue here was only trying to figure out the variables and how to write the formulas from the slides to c++ language because
every other things are given, which I have not had a issue compiling it.


p4

 ...
