// Sachin Shah
// March 12, 2020

#ifndef _MAPPING_H
#define _MAPPING_H

#include <stdint.h>

typedef uint32_t*** Map;

Map create_map(void);

void zero_map(Map map);

#endif