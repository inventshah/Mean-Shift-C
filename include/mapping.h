// Sachin Shah
// March 12, 2020

#ifndef _MAPPING_H
#define _MAPPING_H

#include <stdint.h>

#define MAP_SIZE 64

typedef uint32_t*** Map;

Map create_map(void);
uint8_t get_index(uint8_t num);

#endif