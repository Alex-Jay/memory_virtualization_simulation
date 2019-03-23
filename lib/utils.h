#ifndef UTILSH
#define UTILSH

typedef unsigned short  ushort_t;
typedef unsigned char   uchar_t;
typedef unsigned int    uint_t;

// Initialization
void init_random_seed ();
int get_random_int (int min, int max);
int get_random_payload_size ();
int get_random_ascii_index ();
void init_page_table_entries (char* physical_memory);
void init_disk_entries (char* disk_memory);

// File I/O
void write_physical_memory_to_file (char* physical_memory, const char *file_path);
void write_page_table_to_file (char* physical_memory, const char *file_path);
void write_disk_memory_to_file (char* disk_memory, const char *file_path);
char* get_current_working_directory ();

// Operational
void write_random_payload (char* physical_memory, char* disk_memory, int payload_size, int start_address);
void write_page_table_entry (char* physical_memory, uchar_t frame_number, uchar_t control_bits);
void write_disk_entry (char* physical_memory, char* disk_memory);
int get_available_random_pte (char* physical_memory);
int get_random_physical_frame ();
int get_available_physical_frame_count();
int frame_to_physical_address (int frame_number);
int physical_address_to_frame (int physical_address);
int page_to_physical_frame (char* physical_memory, ushort_t input_address, int virtual_page_number, int offset);
int get_available_pte_slot_for_disk (char* physical_memory);

// Debugging
void print_mem_config (int payload_size, int frame);
void print_payload_header ();
void print_translation_data (
    char*       physical_memory,
    ushort_t    input_address,
    ushort_t    virtual_page_number,
    uchar_t     virtual_address,
    uchar_t     control_bits,
    uchar_t     phy_frame_number,
    ushort_t    l_shifted_page_number,
    ushort_t    page_offset,
    ushort_t    masked_page_number
);
void print_page_table_entry (char* physical_memory, int page_number);
void print_physical_frame_contents (char* physical_memory, ushort_t input_address);
void print_header_end (char char_to_print, int count);
void clear_console ();

#endif