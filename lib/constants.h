#ifndef CONSTANTSH
#define CONSTANTSH

#define C_PRESENT 			(1 << 0)
#define C_READWRITE 		(1 << 1)
#define C_USER 				(1 << 2)	
#define C_DIRTY 			(1 << 3)
#define C_ACCESSED			(1 << 4)
#define C_CACHEDISABLED		(1 << 5)
#define C_NONE_6 			(1 << 6)
#define C_NONE_7			(1 << 7)

static int PHYSICAL_MEMORY_SIZE     = 65536;
static int PAGE_TABLE_SIZE          = 512;
static int PAGE_SIZE                = 256;
static int FRAME_COUNT              = 256;
static int PAYLOAD_LOWER_BOUNDS     = 2048;
static int PAYLOAD_UPPER_BOUNDS     = 4096; // TODO: Change the value back before upload
//static const int PAYLOAD_UPPER_BOUNDS     = 20480;
static int ASCII_MIN_RANGE          = 33;
static int ASCII_MAX_RANGE          = 127;

static char TABLE_HEADER_FORMAT[]   = "%15s%15s%15s%15s%20s\n";
static char TABLE_BODY_FORMAT[]     = "%15d%15d%15d%15d%20d\n";

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