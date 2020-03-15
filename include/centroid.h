// Sachin Shah
// March 14, 2020

#ifndef _CENTROID_H
#define _CENTROID_H

#include <stdint.h>

struct centroid
{
	uint32_t red;
	uint32_t green;
	uint32_t blue;
};

typedef struct centroid Centroid;

void centroid_add(Centroid *c1, Centroid *c2);
void centroid_divide(Centroid *centroid, uint32_t num);
void centroid_times(Centroid *centroid, uint32_t num);

void set_centroid(Centroid *centroid, uint32_t value);

#endif