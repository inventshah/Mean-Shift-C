// Sachin Shah
// March 12, 2020

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "image.h"
#include "utils.h"
#include "meanshift.h"

int main(int argc, char **argv)
{
	Image *img = open_image("source.png");

	segment(img, 16, 25);
	save_image(img, "shifted_source16.png");

	img = free_image(img);

	return 0;
}