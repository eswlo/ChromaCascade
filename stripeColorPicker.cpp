/**
 * @file stripeColorPicker.cpp
 * @description Implements the StripeColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "stripeColorPicker.h"

/**
 * Constructs a new StripeColorPicker.
 *
 * @param stripe_width The width of each alternating stripe, in pixels
 * @param stripe_color1 Color of the main stripe
 * @param stripe_color2 Color of the alternate stripe
 */
StripeColorPicker::StripeColorPicker(unsigned int stripe_width, RGBAPixel stripe_color1, RGBAPixel stripe_color2)
{
    stripewidth = stripe_width;
    color1 = stripe_color1;
    color2 = stripe_color2;
}

/**
 * Picks the color for pixel (x, y).
 *
 * The stripe pattern to be drawn consists of alternating stripes each of stripewidth pixels,
 * in a 45-degree forward slash orientation.
 * e.g.  / / / / / 
 *        / / / / /
 *       / / / / / 
 *        / / / / /
 *
 * For reference, coordinate (0, 0) will be the left-most pixel of a color1 stripe.
 */
RGBAPixel StripeColorPicker::operator()(PixelPoint p)
{
    unsigned int sum = p.x + p.y;
    unsigned int m = stripewidth * 2;

    if (sum % m < stripewidth) {
        p.color = color1; 
    } else {
        p.color = color2;
    }
    return p.color;
}

/**
 * Add your private StripeColorPicker function implementations below
 */
