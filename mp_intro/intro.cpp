#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG inputImage, result;
  inputImage.readFromFile(inputFile);
  result = inputImage;

  unsigned width = inputImage.width();
  unsigned height = inputImage.height();

  for (unsigned i = 0; i < width; i++) {

    for (unsigned j = 0; j < height; j++) {

      result.getPixel(width - i - 1, height - j - 1) = inputImage.getPixel(i, j);
    }
  }

  result.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned i = 0; i < png.width(); i++) {
    for (unsigned j = 0; j < png.height(); j++) {
      cs225::HSLAPixel &pixel = png.getPixel(i, j);
      pixel.h = (double) (j/3 + i/3);
      pixel.s = 0.5;
      pixel.l = 0.5;
      pixel.a = 0.5;
      if ((i-400)*(i-400)/2 + (j-400)*(j-400)/3 - 200 < 400) {
        pixel.h = 216;
      }
      if ((i-400)*(i-400)/2 + (j-400)*(j-400)/3 - 800 < 400) {
        pixel.h = 11;
      }
    }
  }

  return png;
}
