#include "encryption.h"
#include "generation.h"

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <inttypes.h>
#include <iostream>

using namespace std;

const size_t MESSAGE_LENGTH = 2000000000;

uint64_t generateStringOfBytes() 
{
        int folder = 0; 
        ssize_t resourceFile = 0;
        uint64_t buffer = 0;		
        
		if((folder = open("D:/Apps C++/Chapter 14 - Chaos-based Cryptography/ChaosSecureRandomNumberGenerator/dev/urandom", O_RDONLY)) == -1)
			exit(-1);
        
		if((resourceFile = read(folder, &buffer, sizeof buffer)) < 0)
			exit(-1);
        
		buffer &= ((1ULL << 53) - 1);
        close(folder);
        return buffer;
}

int main(void) 
{		
        struct generation gen;		
        uint64_t key[3] = {generateStringOfBytes()+rand()%3000, generateStringOfBytes()+rand()%5000, generateStringOfBytes()+rand()%8000};		        
		cout<<"Key 1 -> "<<key[0]<<endl;
		cout<<"Key 2 -> "<<key[1]<<endl;
		cout<<"Key 3 -> "<<key[2]<<endl;
		
        // generate 1GiB of 1s
        uint8_t *message = (uint8_t*)malloc(MESSAGE_LENGTH);
        memset(message, 1, MESSAGE_LENGTH);

        // perform encryption
        generation_initialization(&gen, key);
        clock_t s = clock();
        encryption(&gen, message, MESSAGE_LENGTH);
        clock_t e = clock();
        double spent = (double)(e - s) / CLOCKS_PER_SEC;
        printf("1GiB in %lfs\n", spent);

        free(message);				
}