// Sachin Shah
// March 14, 2020

#ifndef _PIXELS_H
#define _PIXELS_H

#include <stdint.h>

struct pixel
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	struct pixel *next;
};

typedef struct pixel Pixel;

uint8_t shift_2(uint8_t num);

Pixel *add_pixel(Pixel *last, uint8_t red, uint8_t green, uint8_t blue);
void free_pixels(Pixel *root);

#endif