#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "utils.h"

// Random Number Generator
// Authod: Tutorials Point
// Source: https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
int get_random_int(int min, int max)
{
	time_t t;

	if (PAYLOAD_UPPER_BOUNDS == PAYLOAD_LOWER_BOUNDS)
		return 0;

	/* Initialize random generator & Retrieve a random integer */
	srand((unsigned) time(&t));
	int random_int = rand() % (max + 1 - min) + min;

	return random_int;
}

int get_random_payload_size()
{
	if (PAYLOAD_UPPER_BOUNDS == PAYLOAD_LOWER_BOUNDS)
		return 0;
	else
		return get_random_int(PAYLOAD_LOWER_BOUNDS, PAYLOAD_UPPER_BOUNDS);
}

char get_random_char()
{
	return (char) get_random_int(ASCII_MIN_RANGE, ASCII_MAX_RANGE);
}

void write_random_payload(char* physical_memory, int payload_size, int start_frame)
{
	int physical_bytes = frame_to_physical_address(start_frame);

	if (physical_memory == NULL)
		return;

	for(int i = physical_bytes; i < payload_size - 1; ++i)
	{
		physical_memory[i] = get_random_char();
	}

	// Null terminator
	physical_memory[payload_size] = '\0';
}

int get_random_physical_frame ()
{
	// Example: 256 frames - 254 frames = 2 frames [Frame 0-1: Page Table]
	int min = FRAME_COUNT - get_available_physical_frame_count();
	int max = FRAME_COUNT;

	return get_random_int(min, max);
}

int get_available_physical_frame_count ()
{
	if (PAGE_TABLE_SIZE < 0)
		return 0;

	/* Get available free memory (including page table size difference) and determine frame count */
	return (PHYSICAL_MEMORY_SIZE - PAGE_TABLE_SIZE) / PAGE_SIZE;
}

int frame_to_physical_address (int frame_number)
{
	// Example: 0 * 256 = 0
	// Example: 1 * 256 = 256
	// Example: 2 * 256 = 512
	return frame_number * PAGE_SIZE;
}