// Sachin Shah
// March 14, 2020

#include "pixels.h"
#include "utils.h"

#include <stdint.h>
#include <stdlib.h>


uint8_t shift_2(uint8_t num)
{
	return num >> 2;
}

Pixel *add_pixel(Pixel *last, uint8_t red, uint8_t green, uint8_t blue)
{
	Pixel *ptr = (Pixel *) malloc(sizeof(Pixel));
	check_null(ptr, "malloc failed to find space for a Pixel");

	ptr->red = (red);
	ptr->green = (green);
	ptr->blue = (blue);
	ptr->next = NULL;

	if (last != NULL) last->next = ptr;
	return ptr;
}

void free_pixels(Pixel *root)
{
	if (root != NULL)
	{
		free_pixels(root->next);
		free(root);
	}
}