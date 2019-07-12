# Memory Virtualization Simulation

> In this project students are required to create an application which simulates the structures and  processes used by both an Operating System and a Central Processing Unit to implement memory virtualization for a 16 bit virtual address space which employs a page size of 256 bytes. The simulated system must make use of a single-level linear page table which is stored in the system’s simulated physical memory.

### Current Build Status
[![Build status](https://ci.appveyor.com/api/projects/status/9fwk65mjh2lgbr8j?svg=true)](https://ci.appveyor.com/project/Alex-Jay/memory-virtualization-simulaton)

**Subject**: Operating Systems
**Degree**: BSc (Hons) Computing in Games Development

# Architecture
**Physical Memory**: 0 - 65,535 bytes
**Disk Memory**: 0 - 511 bytes ***[Not fully functional]***
**Page Table** : 0 - 511 bytes
**Page Table Entry**: Byte for Physical Frame Number & Byte for Control Bits, Overall 2 bytes.
**Control Bits**: 
- *C_PRESENT*
- *C_READWRITE*
- *C_DIRTY*
- *C_DISK*
- *C_ACCESSED*
- *C_CACHEDISABLED*
- *C_NONE_6*
- *C_NONE_7*

# Usage
In terminal:
```bash
<user>@<user>:~$ cd dir
<user>@<user>:~$ make clean
<user>@<user>:~$ make run
<user>@<user>:~$ *[Inputs from 0x0000 -> 0xFFFF]*
```

# Dependencies
- **Ubuntu 18.04+**
- **gcc**
- **CMake**

### Installation & Usage

- Clone the repository and checkout to ***master***
- Use **make** command to build the project

```bash
<user>@<user>:~$ cd memory_virtalization_simulation
<user>@<user>:~$ make
```

- Run the following command to launch the applciation after make
```bash
<user>@<user>:~$ make run
```

### Development

Want to contribute? Great!
**E-mail**: alexjaycontact@gmail.com if you would like to be added as a contributor.

### Todos
- Allocate block of memory sufficient to store bytes for the full address space.
- Create a Page Table for a single process.
- Randomly write between [2,048-bytes & 20,480-bytes] of data belonging to the 'process' previously created.
- Write file to ***"/data/physical_memory.txt"*** which displays the contents of your simulation of physical memory in linear & readable form. (Label which addresses are & are not used.
- Write file to ***"/data/page_table.txt"*** which displays the contents of your simulated page table in linear, readable form.
- Add 2 entries to the Page Table which points to pages which are not stored in your simulated physical memory (Swapping), store content for these pages in ***"/data"*** folder.
- Print, to console, a human-readable description of the strutture of a single page table entry you have selected.
- Display prompt which allows the user to enter any virtual memory address in your system, in HEXIDECIMAL form.

*If you have any further requests or proposals, don't be stumbled to contact us, we love socialising <3.*
