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
	/* 16-bit address space */
	char *physical_memory = malloc(PHYSICAL_MEMORY_SIZE);

	/* 
		Page Table Entry Count = 2^16 / 256 = 256 entries
		Page Table Size = 256 * 2 bytes = 512 bytes total
		Byte 0 - 511 = Page Table
		Every 2 bytes are a page table entires 
	*/
	ushort_t *page_table = malloc(PAGE_TABLE_SIZE);

	int random_payload_size = get_random_payload_size();
	int random_frame = get_random_physical_frame();
	int random_physical_index = frame_to_physical_address(random_frame);

	printf("[Memory Configuration]\n");
	printf (TABLE_HEADER_FORMAT, "Physical Memory", "Table Size", "Payload Size", "Frame Count", "Random Frame Index");
	printf (TABLE_BODY_FORMAT, PHYSICAL_MEMORY_SIZE, PAGE_TABLE_SIZE, random_payload_size, get_available_physical_frame_count(), random_frame);
	printf("\n\n");
	printf("[Payload]\n");
	
	write_random_payload(physical_memory, random_payload_size, random_frame);

	for(int i = random_physical_index; i < random_payload_size; ++i)
	{
		printf("[%i] %c\n", i, (char) physical_memory[i]);
	}
	

	/*
	printf("Total Physical Memory: %i bytes\n", PHYSICAL_MEMORY_SIZE);
	printf("Page Table Size: %i bytes\n", PAGE_TABLE_SIZE);
	printf("Random Payload Size: %i bytes\n", get_random_payload_size());
	printf("Available Frame Count: %i frames\n", get_available_physical_frames() );

	physical_memory[5] = (char) 74;

	printf("Data @ physical_memory[5]: %c\n", (physical_memory[5]));

	page_table[0] = (ushort_t) 0x0029;

	printf("Address @ page_table[0]: %hu\n", (page_table[0]));

	printf("Random Frame Index [2-256]: %i\n", get_available_random_physical_frame());
	*/

	free(page_table);
	free(physical_memory);

	return 0;
}
