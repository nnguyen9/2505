#include <stdio.h>
#include <stdint.h>

#include "instr_decode.h"


int main()
{
	// Hard code a random program into mem. It doesn't do much, but it
	// should have all of the instructions.
	uint8_t mem[] = {
		INT, 0,
		NOOP, 
		NOOP, 
		NOOP,
		LOADR, 0x01, 0x00, 
		LOADI, 0x02, 32,
		ADD, 0x01, 0x01, 0x02, 
		LOADI, 0x02, 1,
		SUB, 0x01, 0x01, 0x02,
		STORE, 0x01, 0x00,
		NOT, 0x01, 0x01,
		AND, 0x01, 0x01, 0x03,
		OR, 0x01, 0x01, 0x03,
		SHIFT, 0x01, 0x01, 0x03,
		ROT, 0x01, 0x01, 0x03,
		NOOP, 
		NOOP, 
		NOOP,
		RET
		};

	// Call your implementation printing the report to the terminal.
	instr_decode(stdout, 69, mem);

	return 0;	
}
