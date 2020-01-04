#include "Image.h"
#include <cmath>
using namespace cs225;

void Image::lighten() {
    _changeValueHelper('l', 0.1);
}

void Image::lighten(double amount) {
    _changeValueHelper('l', amount);
}

void Image::darken() {
    _changeValueHelper('l', -0.1);
}

void Image::darken(double amount) {
    _changeValueHelper('l', -amount);
}

void Image::saturate() {
    _changeValueHelper('s', 0.1);
}

void Image::saturate(double amount) {
    _changeValueHelper('s', amount);
}

void Image::desaturate() {
    _changeValueHelper('s', -0.1);
}

void Image::desaturate(double amount) {
    _changeValueHelper('s', -amount);
}

void Image::grayscale() {
    _changeValueHelper('s', -1.0);
}

void Image::rotateColor(double degrees) {
    _changeValueHelper('h', degrees);
}

void Image::illinify() {
    _changeValueHelper('i', 0);
}

void Image::scale(double factor) {
    _scaleHelper(factor);
}

void Image::scale(unsigned w, unsigned h) {
    double facW = (double) w / this->width();
    double facH = (double) h / this->height();
    double factor = 0;
    if (facW < facH) {
        factor = facW;
    } else {
        factor = facH;
    }
    _scaleHelper(factor);
}

// Helper function to change values in different HSLApixel chanels.
void Image::_changeValueHelper(char channel, double amount) {
    for (unsigned i = 0; i < this->width(); i++) {
        for (unsigned j = 0; j < this->height(); j++) {
            HSLAPixel & pixel = this->getPixel(i, j);
            // l: luminance; s: saturation; h: hue; i: illinify
            switch (channel) {
                case 'l': {// change luminance
                    pixel.l += amount;
                    if (pixel.l < 0.0) {
                        pixel.l = 0.0;
                    } else if (pixel.l > 1.0) {
                        pixel.l = 1.0;
                    }
                    break;
                }
                case 's': {// change saturation
                    pixel.s += amount;
                    if (pixel.s < 0.0) {
                        pixel.s = 0.0;
                    } else if (pixel.s > 1.0) {
                        pixel.s = 1.0;
                    }
                    break;
                }
                case 'h': {// change the hue -- increase color degrees
                    pixel.h += amount;
                    while (pixel.h < 0) {
                        pixel.h += 360;
                    }
                    while (pixel.h >= 360) {
                        pixel.h -= 360;
                    }
                    break;
                }
                case 'i': {// change the hue -- illinify
                    if (pixel.h < 113.5 || pixel.h > 293.5) {
                        pixel.h = 11;
                    } else {
                        pixel.h = 216;
                    }
                    break;
                }
            }
        }
    }
}

// Helper function to scale a picture.
void Image::_scaleHelper(double factor) {
    double scaledWidth = this->width() * factor;
    double scaledHeight = this->height() * factor;
    //std::cout << "Image.cpp line " << __LINE__ << std::endl;
    Image * scaledImage = new Image();
    //Image * scaledImage = (Image *) new PNG(scaledWidth, scaledHeight);
    scaledImage->resize(scaledWidth, scaledHeight);
    for (unsigned i = 0; i < scaledWidth; i++) {
        for (unsigned j = 0; j < scaledHeight; j++) {
            HSLAPixel & originPixel = this->getPixel(i / factor, j / factor);
            scaledImage->getPixel(i, j) = originPixel;
        }
    }
    //std::cout << "Image.cpp line " << __LINE__ << std::endl;
    *this = *scaledImage;
    delete scaledImage;    
}