# memory-allocator-c
A simplified implementation of malloc() and free() written in C to understand dynamic memory management and heap allocation in Unix-like systems.

```
Custom Memory Allocator in C

A simplified implementation of malloc() and free() written in C to understand dynamic memory management and heap allocation in Unix-like systems.

This project explores how memory allocation works internally using sbrk(), metadata management, free lists, block splitting, and block coalescing.

Overview:
This allocator manages heap memory manually by:
  Expanding the heap using sbrk()
  Maintaining a linked list of memory blocks
  Reusing freed blocks
  Splitting large blocks
  Merging adjacent free blocks to reduce fragmentation
  The goal of this project was to deeply understand how dynamic memory allocation works at the operating system level.

Features:
  Custom my_malloc(size_t size)
  Custom my_free(void *ptr)
  Heap expansion using sbrk()
  First-fit allocation strategy
  Free list management
  Block splitting
  Block coalescing (merging adjacent free blocks)
  Metadata stored before user memory

Memory Layout:
  Each allocated block contains:
    [ metadata | user memory ]

Metadata structure:
  typedef struct block {
      size_t size;
      int free;
      struct block *next;
  } block_t;
  The allocator returns a pointer to the memory region after metadata.

Allocation Strategy:
  Search free list for suitable block (first-fit).
  If found:
    Reuse block.
  Split block if large enough.
  If not found:
    Request new memory from OS using sbrk().

Block Splitting:
  When a free block is larger than required, it is split into:
    [allocated block][remaining free block]
  This improves memory utilization.
  Block Coalescing
  When adjacent blocks are free, they are merged to reduce fragmentation.
    [free][free] → [larger free block]

Compilation:
  gcc allocator.c -o allocator
  ./allocator

Key Concepts Used:
  Heap memory management
  sbrk() system call
  Pointer arithmetic
  Metadata management
  Linked lists
  Memory fragmentation
  First-fit allocation
  Block splitting
  Block coalescing

What I Learned:
  Through this project, I gained hands-on understanding of how memory allocation works internally in operating systems. Implementing my own allocator helped me           understand heap structure, fragmentation, pointer arithmetic, and the importance of efficient memory reuse.

Limitations:
  No thread safety
  No alignment optimizations
  Uses sbrk() instead of mmap() for large allocations
  Simplified first-fit strategy

Future Improvements:
  Add memory alignment
  Implement best-fit strategy
  Support large allocations via mmap()
  Add thread safety
  Add debugging and heap visualization tools

```
