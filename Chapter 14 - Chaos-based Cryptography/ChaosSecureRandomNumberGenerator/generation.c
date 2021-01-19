#include "generation.h"

static void initialization(struct generation *gen, double initValueX, double initValueY, double initValueZ)
{
	gen->x.d = initValueX;
	gen->y.d = initValueY;
	gen->z.d = initValueZ;
}

static void perform_iteration(struct generation *gen)
{
	gen->x.d = gen->x.d + APPROXIMATION * (-gen->y.d - gen->z.d);
	gen->y.d = gen->y.d + APPROXIMATION * (gen->x.d + A_Coordinate * gen->y.d); 
	gen->z.d = gen->z.d + APPROXIMATION * (B_Coordinate + gen->z.d * (gen->x.d - C_Coordinate));
}

void generation_initialization(struct generation *gen, uint64_t keyValue[3])
{
	initialization(gen,
			(double)keyValue[0] / 9007199254740992, 
			(double)keyValue[1] / 8674747684896687, 
			(double)keyValue[2] / 6758675765879568);

	for(uint8_t index = 0; index < REMOVE_NOISE - 1; ++index)
			perform_iteration(gen);
}

uint32_t generation32(struct generation *gen)
{
	uint32_t message[6];
	message[0] = (uint32_t)(gen->x.rb.mantisa >> 32);
	message[1] = (uint32_t)(gen->x.rb.mantisa);
	message[2] = (uint32_t)(gen->y.rb.mantisa >> 32);
	message[3] = (uint32_t)(gen->y.rb.mantisa);
	message[4] = (uint32_t)(gen->z.rb.mantisa >> 32);
	message[5] = (uint32_t)(gen->z.rb.mantisa);
	perform_iteration(gen);

	message[0] += message[1];
	message[2] += message[3];
	message[4] += message[5];
	
	for(uint8_t index = 0; index < 4; ++index) 
	{
			ROSSLER(message[0],7); ROSSLER(message[3],13);
			message[5] ^= (message[4] + message[3]);
			message[1] ^= (message[2] + message[0]);
			message[2] = message[2] ^ message[0] ^ message[5];
			message[4] = message[4] ^ message[3] ^ message[1];
	}
	
	message[2] += message[4];
	return message[2];
}