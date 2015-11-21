#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "instr_decode.h"

void instr_decode(FILE * out, uint16_t start_addr, const uint8_t * const mem)
{
	// Initialize variables
	uint8_t i = start_addr;
	uint16_t addr = start_addr;
	uint8_t value = *(mem + i);
	uint8_t bytes;

	// Loop  through input mem
	while (value != RET) {
		// Outputs the offset
		fprintf(out, "%04X:\t", addr);

		// Uses a switch to determine the instruction
		switch (value) {
			case NOOP: 
				fprintf(out, "noop");
				bytes = 1;
				break;
			case INT:
				value = *(mem + ++i);
				fprintf(out, "int 0x%02x", value);
				bytes = 2;
				break;
			case RET:
				fprintf(out, "ret");
				bytes = 1;
				break;
			case ADD:
				value = *(mem + ++i);
				fprintf(out, "add 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				bytes = 4;
				break;
			case SUB:
				value = *(mem + ++i);
				fprintf(out, "sub 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				bytes = 4;
				break;
			case AND: 
				value = *(mem + ++i);
				fprintf(out, "and 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				bytes = 4;
				break;
			case OR:
				value = *(mem + ++i);
				fprintf(out, "or 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				bytes = 4;
				break;
			case NOT:
				value = *(mem + ++i);
				fprintf(out, "not 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				bytes = 3;
				break;
			case SHIFT:
				value = *(mem + ++i);
				fprintf(out, "shift 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				bytes = 4;
				break;
			case ROT:
				value = *(mem + ++i);
				fprintf(out, "rot 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				bytes = 4;
				break;
			case LOADR:
				value = *(mem + ++i);
				fprintf(out, "loadr 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				bytes = 3;
				break;
			case LOADI:
				value = *(mem + ++i);
				fprintf(out, "loadi 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				bytes = 3;
				break;
			case STORE:
				value = *(mem + ++i);
				fprintf(out, "store 0x%02x", value);
				value = *(mem + ++i);
				fprintf(out, ", 0x%02x", value);
				bytes = 3;
				break;
		}
		fprintf(out, "\n");
		// Increments the index of mem
		i++;
		// Gets new value pointer
		value = *(mem + i);
		// Move the offset
		addr = addr + bytes;
	}
	// Outputs ret as last
	fprintf(out, "%04X:\tret\n", addr);
}

// On my honor:
//
// - I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants
// assigned to this course.
//
// - I have not used C language code obtained from another student,
// or any other unauthorized source, either modified or unmodified.
//
// - If any C language code or documentation used in my program
// was obtained from an allowed source, such as a text book or course
// notes, that has been clearly noted with a proper citation in
// the comments of my program.
//
// <Nam Nguyen>