// Sachin Shah
// March 13, 2020

#include "mapping.h"
#include "utils.h"

#include "stdint.h"
#include "stdlib.h"

Map create_map(void)
{
	uint8_t i, j;

	uint32_t ***temp = (uint32_t ***) calloc(64, sizeof(uint32_t **));
	check_null(temp, "creating map failed");
	for (i = 0; i < 64; i++)
	{
		temp[i] = (uint32_t **) calloc(64, sizeof(uint32_t *));
		check_null(temp[i], "creating map failed");
		for (j = 0; j < 64; j++)
		{
			temp[i][j] = (uint32_t *) calloc(64, sizeof(uint32_t));
			check_null(temp[i][j], "creating map failed");
		}
	}

	return temp;
}

void zero_map(Map map)
{
	uint8_t i, j, k;

	for (i = 0; i < 64; i++)
	{
		for (j = 0; j < 64; j++)
		{
			for (k = 0; k < 64; k++)
			{
				map[i][j][k] = 0;
			}
		}
	}
}