#include <stdio.h>
#include <stdlib.h>
#include "lib/utils.h"
#include "lib/constants.h"

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

typedef unsigned short ushort_t;

int main()
{
	// 16-bit address space
	char *physical_memory = malloc(PHYSICAL_MEMORY_SIZE);

	// Page Table Entry Count = 2^16 / 256 = 256 entries
	// Page Table Size = 256 * 2 bytes = 512 bytes total
	// Byte 0 - 511 = Page Table
	// Every 2 bytes are a page table entires
	ushort_t *page_table = malloc(PAGE_TABLE_SIZE);


	printf("Random Number: %i\n", get_random_number());
	printf("Available Frame Count: %i\n", get_available_physical_frames(PHYSICAL_MEMORY_SIZE, PAGE_TABLE_SIZE, 256) );

	return 0;
}
