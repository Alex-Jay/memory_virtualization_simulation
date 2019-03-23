#ifndef CONSTANTSH
#define CONSTANTSH

// Source: https://www.youtube.com/watch?v=q5GcA0m8q_Q&t=878s
// Author: [javidx9] - https://www.youtube.com/channel/UC-yuWVUplUJZvieEligKBkA
#define C_PRESENT 			(1 << 0)
#define C_READWRITE 		(1 << 1)
#define C_DIRTY				(1 << 2)	
#define C_DISK   			(1 << 3)
//#define C_ACCESSED		(1 << 4)
//#define C_CACHEDISABLED	(1 << 5)
//#define C_NONE_6 			(1 << 6)
//#define C_NONE_7			(1 << 7)

static int PHYSICAL_MEMORY_SIZE     = 65536;
static int DISK_MEMORY_SIZE         = 512;     // CA requires 2 items added to disk [Restrict memory to 2 frames]
static int PAGE_TABLE_SIZE          = 512;
static int PAGE_SIZE                = 256;
static int FRAME_COUNT              = 256;
static int PAYLOAD_LOWER_BOUNDS     = 2048;
static int PAYLOAD_UPPER_BOUNDS     = 20480;
static int ASCII_MIN_RANGE          = 33;
static int ASCII_MAX_RANGE          = 127;
static int OOR_FRAME_OFFSET         = 20;

static char INIT_PRINT_TAG[]        = "[System.Init]";
static char CORE_PRINT_TAG[]        = "[System.Core]";
static char FILEIO_PRINT_TAG[]      = "[System.FileIO]";
static char ERROR_PRINT_TAG[]       = "[System.Error]";
static char SEGMENT_PRINT_TAG[]     = "[System.Segmentation]";

/* Printf formatting */
static char TABLE_BODY_FORMAT[]     = "Phyiscal Memory:\t%'d (bytes)\nTable Size:\t\t%d (bytes)\nPayload Size:\t\t%'d (bytes)\nFrame Count:\t\t%d frames\nRandom Frame:\t\t#%d\n";
static char TABLE_MEMORY_HEADER[]   = "============== [Init. Memory Configuration] ================\n";
static char TABLE_PAYLOAD_HEADER[]  = "======================= [Payload] ==========================\n";
static char TABLE_PHYSICAL_HEADER[] = "%-3s\t| %-3s\t| %-3s\r\n";
static char TABLE_PAGE_HEADER[]   = "%-3s\t| %-3s\t| %-3s\t| %-3s\t| %-3s\t| %-3s\r\n";

// Source: https://stackoverflow.com/questions/3649026/how-to-display-hexadecimal-numbers-in-c
// Author: [codaddict] - https://stackoverflow.com/users/227665/codaddict
static char TABLE_PHYSICAL_MEMORY[] = "0x%-3x\t\t| %-3i\t\t| %-3c\r\n";

static char TABLE_PAGE_TABLE[]      = "0x%-3x\t| 0x%-3x\t\t\t| %-3i\t\t| %-3i\t\t| %-3i\t\t| %-3i\r\n";

/*
    Appendix:
    [Memory configuration]
    PHYSICAL_MEMORY_SIZE    => Total address space size
    PAGE_TABLE_SIZE         => Total size of the page table
    PAGE_SIZE               => Single page size
    FRAME_COUNT             => Total # of frames in address space
    PAYLOAD_LOWER_BOUNDS    => Minimum size of random memory payload
    PAYLOAD_UPPER_BOUNDS    => Maximumt size of random memory payload
    ASCII_MIN_RANGE         => Lowest ASCII value
    ASCII_MAX_RANGE         => Highest ASCII value
    OOR_FRAME_OFFSET        => Additional Out Of Range offset [This allows extra empty frames if trying to write out of range]

    [Control Bits]          [Sets the flag to true]
    C_PRESENT               => Page is in physical memory [Not swapped]
    C_READWRITE 		    => Page can be written into
    C_USER 				    => Page accessible in user-space	
    C_DIRTY 			    => Page is written to
    C_ACCESSED			    => Page is being accessed
    C_CACHEDISABLED		    => Disable caching
    C_NONE_6 			    => Empty bit
    C_NONE_7			    => Empty bit
*/
#endif