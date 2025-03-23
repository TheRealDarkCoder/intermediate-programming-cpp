#include "RGBA/png.h"
#include "RGBA/rgbapixel.h"

#include <string>
#include <cmath>
#include <complex>

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
	// Newton Fractals
	// https://en.wikipedia.org/wiki/Newton_fractal

	// Parameters
	const int maxIterations = 50;
	const double tolerance = 1e-6;
	const int numRoots = 3; // Cubic polynomial

	// Roots of Unity
	// I used claude.ai for this part
	// Prompt: In C++ how do i represent the 3 roots of unity for z^2 - 1 = 0?
	std::complex<double> roots[numRoots] = {
		std::complex<double>(1, 0),
		std::complex<double>(-0.5, 0.866025404),
		std::complex<double>(-0.5, -0.866025404)
	};

	// Colors
	RGBAPixel colors[numRoots];
	colors[0] = RGBAPixel(255, 0, 0);
	colors[1] = RGBAPixel(0, 255, 0);
	colors[2] = RGBAPixel(0, 0, 255);


	double xScale = 4.0 / width;
	double yScale = 4.0 / height;

	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++){
			double real = (x * xScale) - 2.0;
			double imaginary = (y * yScale) - 2.0;
			std::complex<double> z(real,imaginary);


			// Skip points close to root
			bool closeToRoot = false;
			for (int i = 0; i < numRoots; i++){
				if (std::abs(z - roots[i]) < tolerance) {
					png(x, y) = colors[i];
					closeToRoot = true;
					break;
				}	
			}

			if (closeToRoot) continue;

			// Newton's method from wikipedia
			int iterations = 0;
			int rootFound = -1;
			while (iterations < maxIterations && rootFound == -1) {
				std::complex<double> z_cubed = z * z * z;
				std::complex<double> z_squared = z * z;
				z = z - (z_cubed - 1.0) / (3.0 * z_squared);


				// Check for convergence
				for (int i = 0; i < numRoots; i++){
					if (std::abs(z - roots[i]) < tolerance) {
          	rootFound = i;
            break;
          }
				}

				iterations++;
				
			}

			if (rootFound != -1) {
				double intensity = 1.0 - (double)iterations / maxIterations;
        uint8_t r = std::max(20, int(colors[rootFound].red * intensity));
        uint8_t g = std::max(20, int(colors[rootFound].green * intensity));
        uint8_t b = std::max(20, int(colors[rootFound].blue * intensity));
        png(x, y) = RGBAPixel(r, g, b);
			}
			// No convergence
			else {
				png(x, y) = RGBAPixel(0, 0, 0);
			}
		}
  }
	return png;
}
