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

int page_table_page_counter 	= 0;
int physical_frame_counter		= 0;

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

void init_page_table_entries(char* physical_memory)
{
	printf("%s - Initializing Empty Page Table...\n", INIT_PRINT_TAG);
	for(int i = 0; i < PAGE_TABLE_SIZE; ++i)
	{
		/* Even -> Physical Frame Number */
		if (i % 2 == 0)
		{
			physical_memory[i] = 0x00;
		}
		/* Odd -> Control Bits */
		else
		{
			physical_memory[i] = 0x00;
		}
	}
}

/*================================== FILE I/O ==================================*/
void write_physical_memory_to_file(char* physical_memory, const char *file_path)
{
	printf("%s - Writing Physical Memory: %s\n", FILEIO_PRINT_TAG, file_path);

	/* Open file for writing [Creates file if doesn't exist, deletes & overwrites the file] */
    FILE *fp = fopen(file_path, "wb");

	if (fp != NULL)
	{
		fprintf(fp, TABLE_PHYSICAL_HEADER, "Address", "Frame", "Content");
		fprintf(fp, "%s|%s|%s\r\n", "--------", "-------", "---------");

		for(int i = 0; i < PHYSICAL_MEMORY_SIZE; ++i)
		{
			fprintf(fp, TABLE_PHYSICAL_MEMORY, i, physical_address_to_frame(i), physical_memory[i]);			
		}
	}

	/* Close stream */
	fclose(fp);
}

void write_page_table_to_file(char* physical_memory, const char *file_path)
{
	printf("%s - Writing Page Table: %s\n", FILEIO_PRINT_TAG, file_path);

	FILE *fp = fopen(file_path, "wb");

	if (fp != NULL)
	{
		fprintf(fp, TABLE_PAGE_HEADER, "Page", "Physical Frame", "Is Present?", "Can RW?", "Is Dirty?", "On Disk?");
		fprintf(fp, "%s|%s|%s|%s|%s|%s\r\n", "--------", "-----------------------", "---------------", "---------------", "---------------", "---------");
		
		/* Loop every 2 bytes */
		for(int i = 0; i < PAGE_TABLE_SIZE; i += 2)
		{
			unsigned char physical_frame_number = physical_memory[i];
			unsigned char control_bits = physical_memory[i + 1];

			int present_flag 	= ((control_bits & C_PRESENT) != 0) ? 1 : 0;
			int rw_flag 		= ((control_bits & C_READWRITE) != 0) ? 1 : 0;
			int dirty_flag 		= ((control_bits & C_DIRTY) != 0) ? 1 : 0;
			int disk_flag 		= ((control_bits & C_DISK) != 0) ? 1 : 0;

			fprintf(fp, TABLE_PAGE_TABLE, i, physical_frame_number, present_flag, rw_flag, dirty_flag, disk_flag);
		}
	}

	/* Close stream */
	fclose(fp);
}

// Source: http://www.codebind.com/cprogramming/get-current-directory-using-c-program/
// Author: CodeBind Administrator (Name unknown)
char* get_current_working_directory ()
{
	printf("%s - Retrieving Current Working Directory...\n", FILEIO_PRINT_TAG);
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

	if (end_frame >= FRAME_COUNT)
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
		// If [i] is the start of a frame
		if (i % PAGE_SIZE == 0)
		{
			unsigned char control_bits = 0x00;				/* Reset every frame */
			unsigned char current_frame = (unsigned char) (i / PAGE_SIZE);

			if	(physical_frame_counter < (payload_in_frames - 1))
				control_bits |= C_PRESENT | C_READWRITE;	/* Set flags to true */
			else
				control_bits |= C_READWRITE | C_DISK;		/* Set DISK flag to true */

			write_page_table_entry(physical_memory, current_frame, control_bits);

			physical_frame_counter++;
		}

		physical_memory[i] = (char) get_random_ascii_index();
	}

	printf("Starting Frame:\t\t#%i\n", (start_address / PAGE_SIZE));
	printf("Wrote Bytes:\t\t%'i (bytes)\n", payload_size);
	printf("Frames Occupied:\t%i (frames)\n", payload_in_frames);

	print_header_end('=', strlen(TABLE_PAYLOAD_HEADER));

	// Null terminator
	//physical_memory[payload_size] = '\0';
}

void write_page_table_entry(char* physical_memory, unsigned char frame_number, unsigned char control_bits)
{
	// Write 2 bytes for page table entry
	physical_memory[page_table_page_counter] = frame_number;
	physical_memory[page_table_page_counter + 1] = control_bits;

	page_table_page_counter += 2;
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

int physical_address_to_frame (int physical_address)
{
	return floor(physical_address / PAGE_SIZE);
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