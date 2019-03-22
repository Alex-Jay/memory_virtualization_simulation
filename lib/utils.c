#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "constants.h"
#include "utils.h"

/*=============================== INITIALIZATION ===============================*/
void init_random_seed()
{
	printf("%s - Initializing Random Generator Seed...\n", INIT_PRINT_TAG);
	srand(time(NULL));
	time_t t;
	srand((unsigned) time(&t));
}

// Random Number Generator
// Authod: Tutorials Point
// Source: https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
int get_random_int(int min, int max)
{
	if (PAYLOAD_UPPER_BOUNDS == PAYLOAD_LOWER_BOUNDS)
		return 0;

	/* Generate a random integer */
	int random_int = rand() % (max + 1 - min) + min;

	return random_int;
}

int get_random_payload_size()
{
	printf("%s - Generating Random Payload size...\n", INIT_PRINT_TAG);
	if (PAYLOAD_UPPER_BOUNDS == PAYLOAD_LOWER_BOUNDS)
		return 0;
	else
		return get_random_int(PAYLOAD_LOWER_BOUNDS, PAYLOAD_UPPER_BOUNDS);
}

int get_random_ascii_index()
{
	return get_random_int(ASCII_MIN_RANGE, ASCII_MAX_RANGE);
}

void init_page_table_entries(ushort_t* page_table)
{

}

/*================================= OPERATIONAL ================================*/
void write_random_payload(char* physical_memory, int payload_size, int physical_address)
{
	print_payload();
	printf("%s - Writing Random Payload to Physical Memory...\n", CORE_PRINT_TAG);

	if (physical_memory == NULL)
		return;

	for(int i = physical_address; i < (physical_address + payload_size); ++i)
	{
		physical_memory[i] = (char) get_random_ascii_index();
	}

	int frame_count = floor(payload_size / PAGE_SIZE);

	printf("Starting Frame:\t\t#%i\n", (physical_address/PAGE_SIZE));
	printf("Wrote Bytes:\t\t%'i (bytes)\n", payload_size);
	printf("Frames Occupied:\t%i (frames)\n", frame_count);

	print_header_end('=', strlen(TABLE_PAYLOAD_HEADER));

	// Null terminator
	//physical_memory[payload_size] = '\0';
}

int get_random_physical_frame ()
{
	printf("%s - Retrieving Random Physical Frame...\n", INIT_PRINT_TAG);
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
	printf("%s - Converting Frame to Physical Address...\n", INIT_PRINT_TAG);
	// Example: 0 * 256 = 0
	// Example: 1 * 256 = 256
	// Example: 2 * 256 = 512
	return frame_number * PAGE_SIZE;
}

/*================================== DEBUGGING =================================*/
void print_mem_config(int payload_size, int frame)
{
	printf ("\n%s", TABLE_MEMORY_HEADER);
	printf (TABLE_BODY_FORMAT, PHYSICAL_MEMORY_SIZE, PAGE_TABLE_SIZE, payload_size, get_available_physical_frame_count(), frame);
	print_header_end ('=', strlen(TABLE_MEMORY_HEADER));
}

void print_payload()
{
	printf("%s", TABLE_PAYLOAD_HEADER);
}

void print_header_end (char char_to_print, int count)
{
	int current = 0;
	while(current < count - 1)
	{
		printf("%c", char_to_print);
		++current;
	}
	printf("\n\n");
}

// Source: https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
// Author: [nbro] - https://stackoverflow.com/users/3924118/nbro
void clear_console ()
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}