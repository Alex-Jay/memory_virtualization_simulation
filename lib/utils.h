#ifndef UTILSH
#define UTILSH

void init_random();
int get_random_int(int min, int max);
int get_random_payload_size();
int get_random_ascii_index();
void write_random_payload(char* physical_memory, int payload_size, int frame_number);
int get_random_physical_frame();
int get_available_physical_frame_count();
int frame_to_physical_address(int frame_number);

#endif