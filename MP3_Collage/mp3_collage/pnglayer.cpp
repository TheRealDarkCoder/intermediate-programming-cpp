/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 */

#include "pnglayer.h"

PNGLayer::PNGLayer(size_t x, size_t y, const Vector2& position, const Vector2& scale, const RGBAPixel& color, const std::string& name) 
						: position_(position), scale_(scale), color_(color), name_(name) {
	resize(x, y);
	// TODO Initialize the pixels transparent so when drawing shapes, the background is transparent
	// Your code here
}

RGBAPixel PNGLayer::getBlendedPixel(size_t x, size_t y) const{
	RGBAPixel copy = (*this)(x,y);

	// TODO Blend the pixel with color_
	// Multiply the colors per channel and divide by 255
	// Result should be stored in a copy so we don't modify the original PNG
	// This way the color can be easily changed later
	
	// Your code here
	return copy;
}

const Vector2& PNGLayer::getPosition() const{
	return position_;
}

const Vector2& PNGLayer::getScale() const{
	return scale_;
}

void PNGLayer::SetPosition(const Vector2& pos){
	position_ = pos;
}
