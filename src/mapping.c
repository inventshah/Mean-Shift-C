// Sachin Shah
// March 13, 2020

#include "mapping.h"
#include "utils.h"
#include "image.h"

#include "stdint.h"
#include "stdlib.h"

Map create_map(void)
{
	uint8_t i, j;

	uint32_t ***temp = (uint32_t ***) calloc(MAP_SIZE, sizeof(uint32_t **));
	check_null(temp, "creating map failed");
	for (i = 0; i < MAP_SIZE; i++)
	{
		temp[i] = (uint32_t **) calloc(MAP_SIZE, sizeof(uint32_t *));
		check_null(temp[i], "creating map failed");
		for (j = 0; j < MAP_SIZE; j++)
		{
			temp[i][j] = (uint32_t *) calloc(MAP_SIZE, sizeof(uint32_t));
			check_null(temp[i][j], "creating map failed");
		}
	}

	return temp;
}

uint8_t get_index(uint32_t num)
{
	return gamma_correct(num) >> 2;
}