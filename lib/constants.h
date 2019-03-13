#ifndef CONSTANTSH
#define CONSTANTSH

// 2^16 = 65536 bytes
static int PHYSICAL_MEMORY_SIZE = 65536;

// 512 bytes for page table
// 256 bytes per page * 2 bytes
static int PAGE_TABLE_SIZE = 512;

static int PAYLOAD_LOWER_BOUND = 2048;

// TODO: Change the value back before upload
static int PAYLOAD_UPPER_BOUND = 4096;
//const int PAYLOAD_UPPER_BOUND = 20480;

#endif