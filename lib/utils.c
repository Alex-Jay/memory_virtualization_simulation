#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "utils.h"

// Random Number Generator
// Authod: Tutorials Point
// Source: https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
int get_random_number()
{
	time_t t;

	/* Initialize random generator & Retrieve a random integer */
	srand((unsigned) time(&t));
	int random_int = rand() % (PAYLOAD_UPPER_BOUND + 1 - PAYLOAD_LOWER_BOUND) + PAYLOAD_LOWER_BOUND;

	return random_int;
}

int get_available_physical_frames (int physical_memory, int page_table_size, int page_size)
{
	if(page_table_size < 0)
		return 0;

	// Get available free memory and determine frame count
	return (PHYSICAL_MEMORY_SIZE - page_table_size) / page_size;
}