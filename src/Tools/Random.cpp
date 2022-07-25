#pragma once

#include <stdlib.h>

inline int random(int min, int max)
{
	return rand() % (max - min + 1) + min;
}