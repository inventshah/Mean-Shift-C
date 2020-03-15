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

uint8_t clip(uint8_t num)
{
	if (num < 0) return 0;
	if (num > 63) return 63;
	return num;
}

uint32_t combine(uint8_t red, uint8_t green, uint8_t blue, uint8_t climb)
{
	return (red << 18) | (green << 12) | (blue << 6) | climb;
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

	// zero_map(color_map);
	// zero_map(counts);
	color_map = create_map();
	counts = create_map();

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
				color_map[red][green][blue] = combine(red, green, blue, 2);
				current_pixel = add_pixel(current_pixel, red, green, blue);
				if (first_pixel == NULL) first_pixel = current_pixel;
			}
			counts[red][green][blue]++;
		}
	}

	while (cont && gens < max_gens)
	{
		printf("gen=%d\n", gens);

		cont = 0;
		current_pixel = first_pixel;

		while (current_pixel != NULL)
		{
			if (color_map[current_pixel->red][current_pixel->green][current_pixel->blue] & 1)
			{
				set_centroid(&average_centroid, 0);
				count = 0;
				rl = clip(current_pixel->red - bandwidth);
				ru = clip(current_pixel->red + bandwidth);

				gl = clip(current_pixel->green - bandwidth);
				gu = clip(current_pixel->green + bandwidth);

				bl = clip(current_pixel->blue - bandwidth);
				bu = clip(current_pixel->blue + bandwidth);

				for (red = rl; red < ru; red++)
				{
					for (green = gl; green < gu; green++)
					{
						for (blue = bl; blue < bu; blue++)
						{
							if (color_map[red][green][blue] & 2)
							{
								set_centroid(&current_centroid, color_map[red][green][blue]);
								centroid_times(&current_centroid, counts[red][green][blue]);
								centroid_add(&average_centroid, &current_centroid);
								count += counts[red][green][blue];
							}
						}
					}
				}

				centroid_divide(&average_centroid, count);

				if (average_centroid.red != current_pixel->red || average_centroid.green != current_pixel->green || average_centroid.blue != current_pixel->blue)
				{
					cont = 1;
					color_map[current_pixel->red][current_pixel->green][current_pixel->blue] = combine(average_centroid.red, average_centroid.green, average_centroid.blue, 2);
				}
				else
				{
					color_map[current_pixel->red][current_pixel->green][current_pixel->blue] |= 1;
				}
			}

			gens++;
			current_pixel = current_pixel->next;
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

				red = count >> 18;
				green = (count >> 12) & 64;
				blue = (count >> 6) & 64;

				red <<= 2;
				green <<= 2;
				blue <<= 2;

				set_rgb(img, x, y, red, green, blue);
			}
		}
	}

	free_pixels(first_pixel);
}