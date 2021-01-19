#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "generation.h"
#include <stddef.h>

void encryption(struct generation *g, uint8_t *buffer, size_t length);

#endif