// Sachin Shah
// March 14, 2020

#include "centroid.h"

#include <stdint.h>
#include <stdio.h>

void centroid_add(Centroid *c1, Centroid *c2)
{
	c1->red += c2->red;
	c1->green += c2->green;
	c1->blue += c2->blue;
}

void centroid_divide(Centroid *c1, uint32_t num)
{
	if (num == 0) return;
	c1->red /= num;
	c1->green /= num;
	c1->blue /= num;
}

void centroid_times(Centroid *c1, uint32_t num)
{
	c1->red *= num;
	c1->green *= num;
	c1->blue *= num;
}

void set_centroid(Centroid *c1, uint32_t value)
{
	c1->red = value >> 18;
	c1->green = (value >> 12) & 63;
	c1->blue = (value >> 6) & 63;
}
