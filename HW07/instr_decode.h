#ifndef INSTR_DECODE_H
#define INSTR_DECODE_H

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

enum instrs {NOOP, INT, RET, ADD, SUB, AND, OR, NOT,
		SHIFT, ROT, LOADR, LOADI, STORE};

typedef enum instrs instrs;

// Decodes binary instructions stored in the region of memory pointed to by 
// mem, and writes a report to the provided file stream, out. Formatting 
// details are provided in the specification for the assignment. 
//
// Pre:
//	out - Points to an open file stream.
//	start_addr - The location (offset) of the first instruction in the 
//	             memory region pointed to by mem.
// 	mem - Points to a memory region that contains instructions.	
// Post:
//	The instructions in the memory pointed to by mem have been
//	decoded/parsed and a report written as specified. 
//
// Restrictions:
//	You may not use array brackets for this assignments. Any array
//	accesses must use pointer arithmetic and the dereference operator.
//
void instr_decode(FILE * out, uint16_t start_addr, const uint8_t * const mem);

#endif

