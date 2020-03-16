// Sachin Shah
// March 12, 2020

#include "image.h"
#include "meanshift.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	Image *img = NULL;
	char *source, *save;
	uint8_t bandwidth;
	uint32_t gens = 50;

	if (argc < 4) error("Too few command line arguments. Need [source filename] [output filename] [bandwidth]. Optional [Max gens]");

	img = open_image(argv[1]);
	bandwidth = atoi(argv[3]);

	if (argc == 5) gens = atoi(argv[4]);

	segment(img, bandwidth, gens);
	save_image(img, argv[2]);

	img = free_image(img);

	return 0;
}