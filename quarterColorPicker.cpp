/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"

QuarterColorPicker::QuarterColorPicker(PNG& inputimg, unsigned char b_amount)
{
    referenceimg = inputimg;
    brightamount = b_amount;
}

/**
 * Picks the color for pixel (x, y).
 *
 * Using the private reference image, scale each dimension by half
 * and tile the smaller image in a 2 x 2 grid over the original dimensions
 * of the image, and return the pixel at the appropriate coordinate from
 * the tiled image, brightened on each R/G/B channel by the required amount.
 * 
 * The value of each pixel in the scaled image will be a bilinear interpolation
 * of a 2x2 pixel region from the original image, with each of the R/G/B/A channels
 * processed individually. Interpolate over the x-axis before the y-axis.
 * Truncate any fractional values on the R/G/B channels. Brighten each color channel
 * as the final step.
 * 
 * @pre referenceimg width and height are both even
 */
RGBAPixel QuarterColorPicker::operator()(PixelPoint p)
{
    unsigned int original_width = referenceimg.width();
    unsigned int original_height = referenceimg.height();
    unsigned int scale_width = original_width / 2;
    unsigned int scale_height = original_height / 2;
    PNG* scaledImg = new PNG(scale_width, scale_height);
    // PNG* tiledImg = new PNG(original_width, original_height);
    scale(scaledImg, scale_width, scale_height, referenceimg);
    // tile(tiledImg, original_width, original_height, scaledImg);
    // RGBAPixel* newPixel = tiledImg->getPixel(p.x, p.y);
    RGBAPixel* newPixel;
    if (p.x < scale_width && p.y < scale_height) {
      newPixel = scaledImg->getPixel(p.x, p.y);
    } else if (p.x >= scale_width && p.y < scale_height) {
      newPixel = scaledImg->getPixel(p.x - scale_width, p.y);
    } else if (p.x < scale_width && p.y >= scale_height) {
      newPixel = scaledImg->getPixel(p.x, p.y - scale_height);
    } else {
      newPixel = scaledImg->getPixel(p.x - scale_width, p.y - scale_height);
    }
    p.color = *newPixel;
    newPixel = NULL;
    delete scaledImg;
    // delete tiledImg;
    return p.color;
}

/**
 * Add your private QuarterColorPicker function implementations below
 */
void QuarterColorPicker::scale(PNG* scaledImg, unsigned int scale_width, unsigned int scale_height, PNG& referenceimg) 
{
    for (unsigned ys = 0; ys < scale_height; ys++) {
      for (unsigned xs = 0; xs < scale_width; xs++) {
        RGBAPixel* p1 = referenceimg.getPixel(xs*2, ys*2);
        RGBAPixel* p2 = referenceimg.getPixel(xs*2 + 1, ys*2);
        RGBAPixel* p3 = referenceimg.getPixel(xs*2, ys*2 + 1);
        RGBAPixel* p4 = referenceimg.getPixel(xs*2 + 1, ys*2 + 1);

        RGBAPixel* up = new RGBAPixel();
        up->r = static_cast<int>((p1->r + p2->r) / 2);
        up->g = static_cast<int>((p1->g + p2->g) / 2);
        up->b = static_cast<int>((p1->b + p2->b) / 2);
        up->a = (p1->a + p2->a) / 2;

        RGBAPixel* down = new RGBAPixel();
        down->r = static_cast<int>((p3->r + p4->r) / 2);
        down->g = static_cast<int>((p3->g + p4->g) / 2);
        down->b = static_cast<int>((p3->b + p4->b) / 2);
        down->a = (p3->a + p4->a) / 2;

        RGBAPixel* newPixel = new RGBAPixel();
        newPixel->r = static_cast<int>((up->r + down->r) / 2);
        newPixel->g = static_cast<int>((up->g + down->g) / 2);
        newPixel->b = static_cast<int>((up->b + down->b) / 2);
        newPixel->a = (up->a + down->a) / 2;

        //in case new val goes over 255
        if (newPixel->r + brightamount <= 255) {
            newPixel->r = newPixel->r + brightamount;
        } else {
            newPixel->r = 255;
        }

        if (newPixel->g + brightamount <= 255) {
            newPixel->g = newPixel->g + brightamount;
        } else {
            newPixel->g = 255;
        }
    
        if (newPixel->b + brightamount <= 255) {
            newPixel->b = newPixel->b + brightamount;
        } else {
            newPixel->b = 255;
        }

        // newPixel->a = newPixel->a + brightamount;

        RGBAPixel* oldPixel = scaledImg->getPixel(xs, ys);
        *oldPixel = *newPixel;

        delete up;
        delete down;
        delete newPixel;
      }
    }
}

void QuarterColorPicker::tile(PNG* tiledImg, unsigned int original_width, unsigned int original_height, PNG* scaledImg) 
{
    //tile upper left
    for (unsigned yt = 0; yt < original_height / 2; yt++) {
      for (unsigned xt = 0; xt < original_width / 2; xt++) {
        RGBAPixel* oldPixel = tiledImg->getPixel(xt, yt);
        RGBAPixel* newPixel = scaledImg->getPixel(xt, yt);
        *oldPixel = *newPixel;
      }
    }

    //tile upper right
    for (unsigned yt = 0; yt < original_height / 2; yt++) {
      for (unsigned xt = (original_width / 2); xt < original_width; xt++) {
        RGBAPixel* oldPixel = tiledImg->getPixel(xt, yt);
        RGBAPixel* newPixel = scaledImg->getPixel(xt - (original_width / 2), yt);
        *oldPixel = *newPixel;
      }
    }

    //tile lower left
    for (unsigned yt = original_height / 2; yt < original_height; yt++) {
      for (unsigned xt = 0; xt < original_width / 2; xt++) {
        RGBAPixel* oldPixel = tiledImg->getPixel(xt, yt);
        RGBAPixel* newPixel = scaledImg->getPixel(xt, yt - (original_height / 2));
        *oldPixel = *newPixel;
      }
    }

    //tile lower right
    for (unsigned yt = original_height / 2; yt < original_height; yt++) {
      for (unsigned xt = original_width / 2; xt < original_width; xt++) {
        RGBAPixel* oldPixel = tiledImg->getPixel(xt, yt);
        RGBAPixel* newPixel = scaledImg->getPixel(xt - (original_width / 2), yt - (original_height / 2));
        *oldPixel = *newPixel;
      }
    }
}
