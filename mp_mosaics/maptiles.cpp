/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    unsigned rows = theSource.getRows();
    unsigned cols = theSource.getColumns();
    MosaicCanvas * canvas = new MosaicCanvas(rows, cols);
    
    // Build k-d tree and point-tileImage map
    std::vector<Point<3>> newPoints;
    std::map<Point<3>, TileImage*> tilesMap;

    for (auto it = theTiles.begin(); it != theTiles.end(); it++) {
        LUVAPixel pix = it->getAverageColor();
        Point<3> point = convertToXYZ(pix);
        //std::cout << "{" << point << ", " << &*it << "}" << std::endl;
        newPoints.push_back(point);
        tilesMap.insert({point, &*it});
    }
    KDTree<3> tilesTree(newPoints);

    // Set tiles
    for (unsigned x = 0; x < rows; x++) {
        for (unsigned y = 0; y < cols; y++) {
            LUVAPixel currPix = theSource.getRegionColor(x, y);
            Point<3> currPoint = convertToXYZ(currPix);
            Point<3> nearestPoint = tilesTree.findNearestNeighbor(currPoint);
            TileImage * currTile = tilesMap.at(nearestPoint);
            // std::cout << currTile << endl;
            canvas->setTile(x, y, currTile);
        }
    }
    
    return canvas;
}

