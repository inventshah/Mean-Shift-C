// Sachin Shah
// March 12, 2020

#include "utils.h"
#include "image.h"
#include "mapping.h"
#include "pixels.h"
#include "centroid.h"

#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t clip(int8_t num)
{
	if (num < 0) return 0;
	if (num > 63) return 63;
	return num;
}

uint32_t combine(uint8_t red, uint8_t green, uint8_t blue, uint8_t climb)
{
	return (red << 24) | (green << 16) | (blue << 8) | climb;
}

void segment(Image *img, uint8_t bandwidth, uint32_t max_gens)
{
	Map color_map;
	Map counts;

	uint32_t x, y, gens = 0, count = 0;
	uint8_t red, green, blue, ru, rl, gu, gl, bu, bl;
	uint8_t cont = 1;

	png_bytep rgb = NULL;

	Pixel *first_pixel = NULL;
	Pixel *current_pixel = NULL;

	Centroid current_centroid = {0, 0, 0};
	Centroid average_centroid = {0, 0, 0};

	color_map = create_map();
	counts = create_map();
	// zero_map(color_map);
	// zero_map(counts);

	printf("Starting to init pixels\n");
	for (x = 0; x < img->width; x++)
	{
		for (y = 0; y < img->height; y++)
		{
			rgb = get_rgb(img, x, y);
			red = shift_2(rgb[0]);
			green = shift_2(rgb[1]);
			blue = shift_2(rgb[2]);

			if (counts[red][green][blue] == 0)
			{
				color_map[red][green][blue] = combine(red, green, blue, 0);
				current_pixel = add_pixel(current_pixel, red, green, blue);
				if (first_pixel == NULL) first_pixel = current_pixel;
			}
			counts[red][green][blue]++;
		}
	}

	// for (red = 0; red < 64; red++)
	// {
	// 	for (green = 0; green < 64; green++)
	// 	{
	// 		for (blue = 0; blue < 64; blue++)
	// 		{
	// 			if (counts[red][green][blue])
	// 			{
	// 				printf("rgb(%u, %u, %u) = %u\n", red, green, blue, counts[red][green][blue]);
	// 			}
	// 		}
	// 	}
	// }

	// current_pixel = first_pixel;
	// while (current_pixel != NULL)
	// {
	// 	printf("rgb(%u, %u, %u) = %u\n", current_pixel->red, current_pixel->green, current_pixel->blue, counts[current_pixel->red][current_pixel->green][current_pixel->blue]);
	// 	current_pixel = current_pixel->next;
	// }

	while (cont == 1 && gens < max_gens)
	{
		printf("gen=%d\n", gens);

		cont = 0;
		current_pixel = first_pixel;

		while (current_pixel != NULL)
		{
			if ((color_map[current_pixel->red][current_pixel->green][current_pixel->blue] & 1) == 0)
			{
				set_centroid(&average_centroid, 0);
				set_centroid(&current_centroid, color_map[current_pixel->red][current_pixel->green][current_pixel->blue]);
				count = 0;

				rl = clip(current_centroid.red - bandwidth);
				ru = clip(current_centroid.red + bandwidth);

				gl = clip(current_centroid.green - bandwidth);
				gu = clip(current_centroid.green + bandwidth);

				bl = clip(current_centroid.blue - bandwidth);
				bu = clip(current_centroid.blue + bandwidth);

				// printf("bounds(%d, %d, %d, %d, %d, %d)\n", rl, ru, gl, gu, bl, bu);
				for (red = rl; red <= ru; red++)
				{
					for (green = gl; green <= gu; green++)
					{
						for (blue = bl; blue <= bu; blue++)
						{
							if (counts[red][green][blue] != 0)
							{
								set_centroid(&current_centroid, color_map[red][green][blue]);
								centroid_times(&current_centroid, counts[red][green][blue]);
								centroid_add(&average_centroid, &current_centroid);
								count += counts[red][green][blue];
							}
						}
					}
				}

				set_centroid(&current_centroid, color_map[current_pixel->red][current_pixel->green][current_pixel->blue]);
				if (count == 0) printf("rgb(%u, %u, %u) = %u\ncolormap(%u, %u, %u) = %u\n", current_pixel->red, current_pixel->green, current_pixel->blue, counts[current_pixel->red][current_pixel->green][current_pixel->blue], current_centroid.red, current_centroid.green, current_centroid.blue, count);

				centroid_divide(&average_centroid, count);
				
				if (average_centroid.red != current_centroid.red || average_centroid.green != current_centroid.green || average_centroid.blue != current_centroid.blue)
				{
					cont = 1;
					color_map[current_pixel->red][current_pixel->green][current_pixel->blue] = combine(average_centroid.red, average_centroid.green, average_centroid.blue, 0);
					// printf("rgb(%u, %u, %u) = %u\ncolormap(%u, %u, %u) = %u\n", current_pixel->red, current_pixel->green, current_pixel->blue, counts[current_pixel->red][current_pixel->green][current_pixel->blue], current_centroid.red, current_centroid.green, current_centroid.blue, count);
					// printf("avg rgb(%u, %u, %u)\n\n", average_centroid.red, average_centroid.green, average_centroid.blue);
					//fflush(stdout);
				}
				else
				{
					color_map[current_pixel->red][current_pixel->green][current_pixel->blue] |= 1;
				}
			}

			current_pixel = current_pixel->next;
		}

		gens++;
	}

	for (x = 0; x < img->width; x++)
	{
		for (y = 0; y < img->height; y++)
		{
			rgb = get_rgb(img, x, y);
			red = shift_2(rgb[0]);
			green = shift_2(rgb[1]);
			blue = shift_2(rgb[2]);

			count = color_map[red][green][blue];

			red = count >> 24;
			green = (count >> 16) & 63;
			blue = (count >> 8) & 63;

			red <<= 2;
			green <<= 2;
			blue <<= 2;
			//printf("rgb(%d, %d, %d)\n", red, green, blue);

			set_rgb(img, x, y, red, green, blue);
		}
	}

	free_pixels(first_pixel);
}