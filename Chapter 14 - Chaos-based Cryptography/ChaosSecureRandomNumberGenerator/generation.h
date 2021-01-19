#ifndef GENERATION_H 
#define GENERATION_H

#include <inttypes.h>
#include <math.h>

// the Rossler (ROL) attractor definition for plane (x,n)
#define ROSSLER(x,n) ((x = ((x << n) | (x >> (32 - n)))))

// the attractor variables (coordinates) - for this example Rossler is chosen
#define A_Coordinate 0.5273
#define B_Coordinate 3
#define C_Coordinate 6

// constant for integral approximation as a step size
#define APPROXIMATION 0.01

// constant used for removing the initial noise
#define REMOVE_NOISE 64 

void generation_initialization(struct generation *g, uint64_t k[3]);
uint32_t generation32(struct generation *g);

// the normalization form of a real number
union realbits 
{
	double d;
	struct 
	{
			uint64_t mantisa: 52;
			uint64_t exponent: 11;
			uint64_t sign: 1;
	} rb;
};

struct generation 
{
	union realbits x, y, z; 
};

#endif