
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG myImage;
  myImage.readFromFile("bape.png");
  FloodFilledImage * myFlood = new FloodFilledImage(myImage);

  ColorPicker * myPicker = new MyColorPicker(2);
  //ColorPicker * rainbPicker = new RainbowColorPicker(66.6);
  ImageTraversal * DFStrav = new DFS(myImage, Point(40, 20), 0.2);
  ImageTraversal * BFStrav = new BFS(myImage, Point(100, 100), 0.2);
  
  myFlood->addFloodFill(*DFStrav, *myPicker);
  myFlood->addFloodFill(*BFStrav, *myPicker);

  Animation animation = myFlood->animate(600);
  
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  


  return 0;
}
