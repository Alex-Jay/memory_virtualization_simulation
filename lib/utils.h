#ifndef UTILSH
#define UTILSH

typedef unsigned short ushort_t;

// Initialization
void init_random_seed();
int get_random_int(int min, int max);
int get_random_payload_size();
int get_random_ascii_index();
void init_page_table_entries(ushort_t* page_table);

// Operational
void write_random_payload(char* physical_memory, int payload_size, int physical_address);
int get_random_physical_frame();
int get_available_physical_frame_count();
int frame_to_physical_address(int frame_number);

// Debugging
void print_mem_config(int payload_size, int frame);
void print_payload();
void print_header_end (char char_to_print, int count);
void clear_console();

#endif