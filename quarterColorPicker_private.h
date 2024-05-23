/**
 * @file quarterColorPicker_private.h
 * @description student declarations of private functions
 *              for QuarterColorPicker, CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED.
 *
 *              Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

 // begin your declarations below
void scale(PNG* scaledImg, unsigned int scale_width, unsigned int scale_height, PNG& referenceimg);
void tile(PNG* tiledImg, unsigned int original_width, unsigned int original_height, PNG* scaledImg);