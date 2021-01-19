#include "encryption.h"
#include "generation.h"

#include <iostream>

using namespace std;

// performing the encryption operation
void encryption(struct generation *g, uint8_t *buffer, size_t length)
{
        uint32_t position_in_stream;
        size_t number_of_calls = length >> 2;
        size_t l_neighbour = length & 3;
        uint8_t *temporary = (uint8_t *)&position_in_stream;

        for(size_t index = 0; index < number_of_calls; ++index) 
		{
			position_in_stream = generation32(g);
			buffer[(index<<2)] ^= temporary[0];
			buffer[(index<<2)+1] ^= temporary[1];
			buffer[(index<<2)+2] ^= temporary[2];
			buffer[(index<<2)+3] ^= temporary[3];
        }
		
        if(l_neighbour != 0) 
		{
			position_in_stream = generation32(g);
			for(size_t index = 0; index < l_neighbour; ++index)
				buffer[(number_of_calls<<2)+index] ^= temporary[index];
        }
		
		std::cout<<"The position with the stream is -> "<<position_in_stream<<endl;
}