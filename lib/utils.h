#ifndef UTILSH
#define UTILSH

typedef unsigned short ushort_t;

// Initialization
void init_random_seed();
int get_random_int(int min, int max);
int get_random_payload_size();
int get_random_ascii_index();
void init_page_table_entries(char* physical_memory);

// File I/O
void write_physical_memory_to_file(char* physical_memory, const char *file_path);
void write_page_table_to_file(char* physical_memory, const char *file_path);
char* get_current_working_directory ();

// Operational
void write_random_payload(char* physical_memory, int payload_size, int start_address);
void write_page_table_entry(char* physical_memory, unsigned char frame_number, unsigned char control_bits);
int get_random_physical_frame();
int get_available_physical_frame_count();
int frame_to_physical_address(int frame_number);
int physical_address_to_frame (int physical_address);

// Debugging
void print_mem_config(int payload_size, int frame);
void print_payload_header();
void print_header_end (char char_to_print, int count);
void clear_console();

#endif