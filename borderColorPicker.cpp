/**
 * @file borderColorPicker.cpp
 * @description Implements the BorderColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "borderColorPicker.h"

/**
 * Constructs a new BorderColorPicker.
 *
 * @param width        Number of pixels to color around border.
 * @param inputimage   Image for referencing original image colors.
 * @param scolor       Color of seed point, for checking fill region
 * @param bcolor       Color to be used for painting the fill border.
 * @param tol          Tolerance used to determine the border of the fill.
 */
BorderColorPicker::BorderColorPicker(unsigned int width, PNG& inputimage, RGBAPixel scolor, RGBAPixel bcolor, double tol)
{
    borderwidth = width;
    img = inputimage;
    seedcolor = scolor;
    bordercolor = bcolor;
    tolerance = tol;
}



/**
 * Picks the color for pixel at point. If the x or y coordinate is
 * at or within an Euclidean radius of borderwidth pixels from the border of
 * the fill region, it will be colored with the required border color.
 * Otherwise, its color will not be changed.
 *
 * @param p   The point for which you're picking a color.
 * @return    The color chosen for (p).
 */
RGBAPixel BorderColorPicker::operator()(PixelPoint p)
{


    //There are two “borders” you need to consider for this function 
    //1) the border of the overall png, easy, that is just the perimeter of the png 
    //2) the border of the “image”


    //NOTE!!!
    // the description given above is very confusing!
    // the filler.cpp will only add pixels whose color is within tolerance 
    // range to the seed point color into the stack/queue, so this BorderColorPicker
    // actually get these stored pixels, and we need to check if these pixels are 
    // <= borderwidth away from any pixel which is either on perimeter or 
    // the non-filled pixels (that have radically different color than seedcolor).


    // check whether p at/within distance to outer frame perimeter
    if ((p.x < borderwidth)||(p.x >= img.width() - borderwidth)||
    (p.y < borderwidth) || (p.y >= img.height() - borderwidth)) {
        p.color = bordercolor;
        //check if it is already image border
        // RGBAPixel* pixel = img.getPixel(p.x, p.y);
        // if (pixel->distanceTo(seedcolor) > tolerance) {
        //     p.color = bordercolor;
        // } else {
        //     p.color = *pixel;
        // }
    } else { 
        // traverse all pixels, and check:
        // 1. if any of them has color very differnet from seedcolor; 
        // 2. if the distance between it and p <= borderwidth.
        // if both true, then color p with bordercolor and immediately return 
        // otherwise either keep the original color or the seedcolor
        for (unsigned int y = 0; y < img.height(); y++) { 
            for (unsigned int x = 0; x < img.width(); x++) {
                // get this pixel's color
                RGBAPixel* pixel = img.getPixel(x, y);
                if ((isWithinBorderWidth(p.x, p.y, x, y))) {
                    // if (x, y) is not already bordercolor, and has color radically 
                    // different from seedcolor, then color it with bordercolor
                    if (((*pixel).distanceTo(seedcolor) > tolerance)) {
                        p.color = bordercolor;
                        return p.color;
                    } 
                }
            }
        }
        // if reaching here, then it means we don't need to change the color, 
        // so check if the color of the passed-in PixelPoint p has color
        // similar to seedcolor and is not colored as border. 
        // If so, use it, otherwise change to seedcolor
        // this is only necessary because of how the tests in testFills are designed.
        p.color = decidePColor(p);
    }
    return p.color;
}


/**
 * Add your private BorderColorPicker function implementations below
 */

bool BorderColorPicker::isWithinBorderWidth(unsigned int px, unsigned int py, unsigned int x, unsigned int y) 
{
    unsigned int distSQ = ((px - x)*(px - x)) + ((py - y)*(py - y));
    if (distSQ <= borderwidth * borderwidth) {
        return true;
    } else {
        return false;
    }
}

RGBAPixel BorderColorPicker::decidePColor(PixelPoint& p) 
{
    RGBAPixel pix = p.color;
    if ((pix != bordercolor) && pix.distanceTo(seedcolor) <= tolerance) {
        return pix;
    } else {
        return seedcolor;
    }

}
