#include "RGBA/png.h"
#include "RGBA/rgbapixel.h"

#include <string>
#include <cmath>

void rotate(const std::string & inputFile, const std::string & outputFile) {
	PNG pic(inputFile);
	// Your code here
	unsigned width = pic.width();
	unsigned height = pic.height();

	PNG rotatedPic(height, width); // Flip the height and width

	// Rotate by 90 degrees
	for (unsigned x = 0; x < width; x++) {
		for (unsigned y = 0; y < height; y++) {
    	rotatedPic(y, width - 1 - x) = pic(x, y); 
    }
  
  }
		
	rotatedPic.writeToFile(outputFile);
} 

PNG myArt(unsigned int width, unsigned int height) {
	PNG png(width, height);
	// Your code here

	return png;
}
