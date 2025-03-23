/**
 * @file processImage.cpp
 *
 * @author Elmeri Uotila
 * @author Anna LaValle
 * @date Created: Spring 2025
 * @date Modified from UIUC data structures course assignments
*/

#include <iostream>
#include <stdexcept> 
#include <memory>
#include "png.h"


// Returns my favorite color
RGBAPixel myFavoriteColor(int intensity)
{
	return RGBAPixel(0, intensity/2, intensity);
}


// Sets up the output image
std::unique_ptr<PNG> setupOutput(int w, int h) {
    return std::make_unique<PNG>(w, h); // Using smart pointers
}

// Improved coloring function using a shared pointer
std::unique_ptr<PNG> colorize(std::unique_ptr<PNG> original) {
    int width = original->width();
    int height = original->height();

    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            RGBAPixel &p = (*original)(x, y);
            if (p.red == 0 && p.green == 0 && p.blue == 0) {
	      p = myFavoriteColor(x+y);
            }
        }
    }
    return original;
}

// Borders function using unique_ptr for ownership transfer
std::unique_ptr<PNG> addBorders(std::unique_ptr<PNG> original) {
    int width = original->width();
    int height = original->height();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float fromBorder = std::min(width/2 - std::abs(x - width/2), height/2 - std::abs(y - height/2));
            RGBAPixel &pixel = (*original)(x, y);
            float factor = std::min(fromBorder * 0.03f, 1.0f);
            pixel.red *= factor;
            pixel.green *= factor;
            pixel.blue *= factor;
        }
    }
    return original;
}



std::unique_ptr<PNG> sketchify(std::unique_ptr<PNG> original){
std::cout << "Reached line " <<__LINE__ << __FILE__ << std::endl;
	int width  = original->width();
	int height = original->height();
	
	std::unique_ptr<PNG> output = setupOutput(width, height);
	
  
	// Go over the whole image, and if a pixel differs from that to its upper
	// left, color it my favorite color in the output
	for (int y = 1; y < height; y++)
	{
		for (int x = 1; x < width; x++)
		{
			// Calculate the pixel difference
			
			RGBAPixel & prev = (*original)(x-1, y-1);
			
			RGBAPixel & curr = (*original)(x  , y  );
			
			int diff = abs(curr.red   - prev.red  ) +
					   abs(curr.green - prev.green) +
					   abs(curr.blue  - prev.blue );

			// If the pixel is an edge pixel,
			// color the output pixel with black
			
			RGBAPixel & myPixel = (*output)(x,y);
			if (diff > 70)
			  myPixel = RGBAPixel(0, 0, 0);
		}
	}
	return output;

}



 void processImage()
{
	// Load in.png
	// We only use raw pointer once, for demo purposes, for the original PNG  
        PNG* original = new PNG();
        std::cout << "Reached line " <<__LINE__ << __FILE__ << std::endl;
	      	      std::cout << "Reached line " <<__LINE__ << __FILE__ << std::endl;
        if (!original->readFromFile("in.png")) {
            throw std::runtime_error("Failed to load the image file in.png.");
        }
        std::cout << "Reached line " <<__LINE__ << __FILE__ << std::endl;
	
	//wrap raw pointer asap and create the unique pointer from it for the output PNG
	std::unique_ptr<PNG> output(original);
	std::cout << "Reached line " <<__LINE__ << __FILE__ << std::endl;

	//Sketchify, colorize, and add borders
	output = sketchify(move(output));
	
  std::cout << "Reached line " <<__LINE__ << __FILE__ << std::endl;	
  output = colorize(move(output));
  std::cout << "Reached line " <<__LINE__ << __FILE__ << std::endl;	
  output = addBorders(move(output));
	
	
	
	// Save the output file
        if (!output->writeToFile("out.png")) {
            throw std::runtime_error("Failed to write to image file out.png.");
        }
  	}
