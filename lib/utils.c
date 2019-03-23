#ifdef linux
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
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

// Source: https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
// Author: Tutorials Point
int get_random_int(int min, int max)
{
	/* If equal payload size bounds, return PAYLOAD_LOWER_BOUNDS */
	if (PAYLOAD_LOWER_BOUNDS == PAYLOAD_UPPER_BOUNDS)
		return PAYLOAD_LOWER_BOUNDS;

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

void init_page_table_entries(char* page_table)
{
	printf("%s - Initializing Empty Page Table...\n", INIT_PRINT_TAG);
	for(int i = 0; i < PAGE_TABLE_SIZE; ++i)
	{
		/* Even -> Physical Frame Number */
		if (i % 2 == 0)
		{
			page_table[i] = 0x0;
		}
		/* Odd -> Control Bits */
		else
		{
			page_table[i] = 0x0;
		}
	}
}

/*================================== FILE I/O ==================================*/
void write_data_to_file(const char *filepath, const char *data)
{
	printf("file_name: %s | data_buffer: %s", filepath, data);

    FILE *fp = fopen(filepath, "ab");
    if (fp != NULL)
    {
        fputs(data, fp);
        fclose(fp);
    }
}

// Source: http://www.codebind.com/cprogramming/get-current-directory-using-c-program/
// Author: CodeBind Administrator (Name unknown)
char* get_current_working_directory ()
{
	char buff[FILENAME_MAX + 1];
	buff[FILENAME_MAX] = '\0';
	getcwd( buff, FILENAME_MAX );

	// Source: https://stackoverflow.com/questions/46190920/how-do-i-convert-a-char-array-to-a-string-in-c
	// Author: [Hitsugaya198] - https://stackoverflow.com/users/4636686/hitsugaya198
	char* string;
	string = malloc(sizeof(buff)+1);
	memset(&string[0], 0x00, sizeof(buff)+1);
	memcpy(&string[0], &buff[0], sizeof(buff));

	return string;
}

/*================================= OPERATIONAL ================================*/
void write_random_payload(char* physical_memory, int payload_size, int start_address)
{
	print_payload_header();

	/* Memory not defined or start_address is out of bounds */
	if (physical_memory == NULL || start_address >= PHYSICAL_MEMORY_SIZE)
	{
		printf("%s - Failed To Write To Physical Memory...\n", ERROR_PRINT_TAG);
		return;
	}

	printf("%s - Writing Random Payload to Physical Memory...\n", CORE_PRINT_TAG);

	int start_frame 			= floor(start_address / PAGE_SIZE);
	int payload_in_frames 		= floor(payload_size / PAGE_SIZE);
	int end_frame				= start_frame + payload_in_frames;
	int out_of_bounds_delta 	= end_frame - FRAME_COUNT;

	if ((start_frame + payload_in_frames) >= FRAME_COUNT)
	{
		int move_back_frames = out_of_bounds_delta + OOR_FRAME_OFFSET;

		printf("%s - Out of bounds...\n", SEGMENT_PRINT_TAG);
		printf("Start Frame:\t\t#%i\n", start_frame);
		printf("Payload Frames:\t\t%i (frames)\n", payload_in_frames);
		printf("End Frame\t\t#%i\n", end_frame);
		printf("Out Of Bounds Delta:\t%i (frames)\n", out_of_bounds_delta);
		printf("%s - Shifting Back Start Address by %i (frames)...\n", SEGMENT_PRINT_TAG, move_back_frames);
		start_address -= move_back_frames * PAGE_SIZE;
	}

	/* Write to physical memory */
	for(int i = start_address; i < (start_address + payload_size); ++i)
	{
		physical_memory[i] = (char) get_random_ascii_index();
	}

	printf("Starting Frame:\t\t#%i\n", (start_address / PAGE_SIZE));
	printf("Wrote Bytes:\t\t%'i (bytes)\n", payload_size);
	printf("Frames Occupied:\t%i (frames)\n", payload_in_frames);

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

void print_payload_header()
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