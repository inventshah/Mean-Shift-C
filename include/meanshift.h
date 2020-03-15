// Sachin Shah
// March 12, 2020

#ifndef _MEANSHIFT_H
#define _MEANSHIFT_H

#include "image.h"

#include <stdint.h>

uint8_t clip(uint8_t num);

uint32_t combine(uint8_t red, uint8_t green, uint8_t blue, uint8_t climb);

void segment(Image *img, uint8_t bandwidth, uint32_t max_gens);

#endif