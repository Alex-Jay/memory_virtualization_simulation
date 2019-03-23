#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "lib/utils.h"
#include "lib/constants.h"

#ifdef _WIN32
	#define PRINT_OS() (printf("%s\n", "WINDOWS"))
#elif defined _WIN64
	#define PRINT_OS() (printf("%s\n", "WINDOWS"))
#elif defined __linux__
	#include <unistd.h>
	#define PRINT_OS() (printf("%s\n", "LINUX"))
#endif

/*
	CA Title: Memory Virtualization Simulation
	Author: 	Aleksandrs Jevdokimovs
	Course: 	BSc. (Hons.) Computer Science in Games Development

	Synopsis:

	Create an application which simulates the structures and processes
	used by both an Operating System and a Central Processing Unit to
	implement memory virtualization for a 16-bit virtual address sp-
	ace which employs a page size of 256-bytes.

	Functionality Todo List:

	[+]	Allocate block of memory sufficient to store bytes for the full
			address space.

	[+]	Create a Page Table for a single process.

	[+]	Randomly write between [2,048-bytes & 20,480-bytes] of data be-
			longing to the 'process' previously created.

	[]	Write file to "/data/physical_memory.txt" which displays the
			contents of your simulation of physical memory in linear &
			readable form. (Label which addresses are & are not used.

	[]	Write file to "/data/page_table.txt" which displays the
			contents of your simulated page table in linear, readable
			form.

	[]	Add 2 entries to the Page Table which points to pages which
			are not stored in your simulated physical memory (Swapping),
			store content for these pages in "/data" folder.

	[]	Print, to console, a human-readable description of the stru-
			cture of a single page table entry you have selected.

	[]	Display prompt which allows the user to enter any virtual
			memory address in your system, in HEXIDECIMAL form.
*/

int main()
{
	setlocale(LC_NUMERIC, "");										/* Enable digit padding. i.e. 100000 => 100,000 */
	char* MEMORY_FILE_PATH = strcat(get_current_working_directory(), "/data/physical_memory.txt");
	char* PAGE_TABLE_FILE_PATH = strcat(get_current_working_directory(), "/data/page_table.txt");

	/*=============================== Initialization ===============================*/
	clear_console();												/* Clear console depending on operating system */
	init_random_seed();												/* Initialize random seed */
	char *physical_memory = malloc(PHYSICAL_MEMORY_SIZE);			/* 16-bit address space */
	char *disk_memory = malloc(PAGE_TABLE_SIZE);					/* Simulation of DISK memory */
	//char *page_table = malloc(PAGE_TABLE_SIZE);					/* 512 bytes. 2 bytes per entry. 256 entries */

	/*=============================== Random Selection =============================*/
	int random_payload_size = get_random_payload_size();			/* Random size of payload */
	int random_frame = get_random_physical_frame();					/* Retrieve a random frame [Excluding first 2 frames - Page Table] */
	int physical_address = frame_to_physical_address(random_frame);	/* Convert random frame to physical address */
	init_page_table_entries(physical_memory);							/* Initialize page table entries */

	/*================================= Debugging ==================================*/
	print_mem_config(random_payload_size, random_frame);			/* Print initialized values */

	/*=================================== Core =====================================*/
	write_random_payload(physical_memory, random_payload_size, physical_address);

	//write_data_to_file(MEMORY_FILE_PATH, "HELLO WORLD");

	//printf("PHYSICAL MEMORY PATH: %s\n", MEMORY_FILE_PATH);
	//printf("PAGE TABLE PATH: %s\n", PAGE_TABLE_FILE_PATH);

	// Source: https://stackoverflow.com/questions/3649026/how-to-display-hexadecimal-numbers-in-c
	// Author: [codaddict] - https://stackoverflow.com/users/227665/codaddict
	//printf("HEX: 0x%02x", 16);
	
	/*============================== Garbage Collect ===============================*/
	// Free memory from heap
	free(PAGE_TABLE_FILE_PATH);
	free(MEMORY_FILE_PATH);
	free(disk_memory);
	free(physical_memory);

	return 0;
}
