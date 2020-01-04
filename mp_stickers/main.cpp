#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image base_image;
  Image panda, batman, ape;
  base_image.readFromFile("alma.png");
  panda.readFromFile("panda.png");
  batman.readFromFile("batman.png");
  ape.readFromFile("ape.png");
  StickerSheet * MasterPiece = new StickerSheet(base_image, 5);
  MasterPiece->addSticker(panda, 20, 20);
  MasterPiece->addSticker(batman, 40, 260);
  MasterPiece->addSticker(ape, 490, 300);
  Image masterPiece = MasterPiece->render();
  masterPiece.writeToFile("myImage.png");


  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
