#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "bytes.h"


//
//
//
//
void bytes_init(bytes_t * const bytes)
{
	bytes->data = bytes->dflt;

	bytes->usage = 0;
	bytes->dim = DEFAULT_SIZE;
}


//
//
//
//
void bytes_free(bytes_t * const bytes)
{
	if (bytes->data != bytes->dflt)
	{
		free(bytes->data);
	}

	bytes->data = NULL;
}


//
//
//
//
void bytes_fprintf(FILE * out, const bytes_t * const bytes)
{
	fprintf(out, "          ");

	for (size_t b = 0; b < BYTES_PER_LINE; b++)
	{
		fprintf(out, "%02zx ", b);
	}
	fprintf(out, "\n");

	fprintf(out, "         ");
	fprintf(out, " -----------------------------------------------");
	fprintf(out, "\n");

 	for (size_t x = 0; x < bytes->usage; x += 16)
	{
		size_t min = (bytes->usage  >= x + BYTES_PER_LINE) 
				? x + BYTES_PER_LINE : bytes->usage; 

		fprintf(out, "%08zx  ", x);
	
		for (size_t y = x; y < min; y++)
		{ 
			fprintf(out, "%02"PRIx8" ", bytes->data[y]);
		}
		fprintf(out, "\n");
	}

	fprintf(out, "         ");
	fprintf(out, " -----------------------------------------------");
	fprintf(out, "\n");
	fprintf(out, "\n");
	
}


//
//
//
//
bool bytes_empty(const bytes_t * const bytes)
{
	return bytes->usage == 0;
}


//
//
//
//
uint8_t * bytes_data(const bytes_t * const bytes)
{
	return bytes->data;
}


//
//
//
//
size_t bytes_usage(const bytes_t * const bytes)
{
	return bytes->usage;
}


//
//
//
//
bool bytes_set(bytes_t * const bytes, size_t index, uint8_t val)
{
	if (index < bytes->usage) {
		bytes->data[index] = val;
		return true;
	} else {
		return false;
	}
}


// Gets a 1 byte, 2 byte, 4 byte, or 8 byte value from *bytes, and
// interprets it as either a big or little endian value.
//
// Enumerations are provided for both the width (width_t) and byte
// order (endian_t). These enumerations can be used as more than just
// a constant to compare against. Since they are integer values they 
// might be used as part of the computation.
//
// Pre:
//	bytes - Points to valid bytes_t variable and is not NULL
//
// Post:
//	Tries to read a width sized value and interprets it as if it had
//	order, byte ordering. The result is stored in output variable, result. 
//
// Returns:
//	If there are enough bytes starting at index to get a width size
//	value the function returns true, false otherwise.
//
// Examples:
//	If bytes->data contains the bytes: {0xDE, 0xAD, 0xBE, 0xEF} 
//
//	If we interpret it as a 4 byte value, then in big endian order it
//	is 0xDEADBEEF, the highest order byte is in the lowest index, 0.
//
//	In little endian order it would be interpreted as 0xEFBEADDE, 
//	highest order byte is in the largest index, 3.
//	
//	
bool bytes_get(const bytes_t * const bytes, size_t index, 
		width_t width, endian_t order, uint64_t * const result)
{
	if (index + width < bytes->usage) {
		switch (order) {
			case BIG:
				for (size_t i = index; i < index + width; i++) {
					*result = bytes->data[i] | (*result << 8);
				}
				break;
			default:
				for (size_t i = index + width - 1; i >= index; i++) {
					*result = bytes->data[i] | (*result >> 8);
				}
		}
		return true;
	} else {
		return false;
	}
}


// Inserts len bytes stored in the memory pointed to by buf into *bytes
// at starting at the specified index.
//
// Pre:
//	bytes - Points to valid bytes_t variable and is not NULL.
//	buf - Points to a chunk of memory len bytes long.
//
// Post:
//	The bytes in buf are inserted into *bytes starting at index. If
//	necessary, bytes->data may switch to dynamically allocated
//	memory or may be resized as bytes->data grows. 
//
// Returns:
//	If a required dynamic allocation fails, or index > bytes->usage
//	the function will return false, true otherwise.
//
// Other thoughts:
// 	You are going to insert "before" index. So if you insert at index = 0 
//	you are inserting before the first byte. Further, if you were insert 
//	at index = bytes->usage, it like appending one or bytes at the end.
//
//	Reallocate (or just allocate) when bytes->usage + len > bytes->dim.
//	To avoiding reallocating every time you insert, double the  needed
//	size, i.e. bytes->dim = 2 * (bytes->usage + len)
//
//
bool bytes_insert(bytes_t * bytes, size_t index, uint8_t * buf, size_t len)
{
	if (index > bytes->usage) {
		return false;
	}
	if (bytes->usage + len > bytes->dim) {
		
		uint8_t * temp;
		if (bytes->dim == DEFAULT_SIZE) {
			temp = malloc(2 * (bytes->usage + len));
			for (int i = 0; i < bytes->usage; i++) {
				temp[i] = bytes->data[i];
			}
		} else {
			temp = (uint8_t *)realloc(bytes->data, (2 *((bytes->usage) + len))); 
		}

		if (temp == NULL) {
			return false;
		}
		bytes->data = temp;
		bytes->dim = 2 * (bytes->usage + len);
	}
	for (int i = 0; i < ((bytes->usage) - index); i++) 	{ 		
		*((bytes->data) + bytes->usage + len -i - 1) = *((bytes->data) + bytes->usage - i - 1); 	
	} 	
	for (int i = 0; i < len; i++) { 		
		*((bytes->data) + index + i) = *(buf+i); 	
	} 
	bytes->usage += len;
	return true;

}

// Erases len bytes from *bytes starting at the specified index.
//
// Pre:
//	bytes - Points to valid bytes_t variable and is not NULL
//
// Post:
//	If index < bytes->usage, then up to len bytes have been erased from
//	*bytes starting at index. When index + len > bytes->usage less than
//	len bytes will be erased.
//
// Returns:
//	If index >= bytes->usage, then no erasure occurs and the function
//	returns false, true otherwise.
//
bool bytes_erase(bytes_t * const bytes, size_t index, size_t len)
{
	if (index >= bytes->usage) {
		return false;
	}
	if (index + len <= bytes->usage) {
		for (int i = 0; i < len; i++) {
			for (int i = index; i < bytes->usage; i++) {
				*(bytes->data + i) = *(bytes->data + i + 1);
			}
			bytes->usage--;
		}
	} else {
		for (int i = 0; i < bytes->usage; i++) {
			for (int i = index; i < bytes->usage; i++) {
				*(bytes->data + i) = *(bytes->data + i + 1);
			}
			bytes->usage--;
		}
	}
	return true;
}


// A different way to iterate through a bytes_t type.
//
// This function makes use of the range_t type, which allows us to specify
// range of bytes that we want to examine or modify. The range is inclusive
// at the start, and exclusive at the end. So if a range starts 0 and stops
// at 10, we would examine bytes from 0 up to but not including 10.
//
// For example:
// 	This will iterate through every byte when used with bytes_range():
// 		range_t r1 = {.start = 0, .end = bytes->usage, .step = 1};
//
// 	This will iterate through every other byte when used with 
//	bytes_range():
// 		range_t r2 = {0, bytes->usage, 2};
//
// 	This starts at index 10 and goes down to but not including index 4, 
//	4 bytes at a time:
// 		range_t r3 = {10, 4,  -4};
//
// 	You will modify the range object once every time the function runs. 
//	It's up to you to make sure you don't go out of bounds, but this 
//	should be evaluated lazily.
// 
// Returns:
//	A pointer to the next element, or NULL if there isn't a next element.
//
uint8_t * bytes_range(const bytes_t * const bytes, range_t *range)
{
	if ((range->step > 0 && range->start >= range->stop) || (range->step < 0 
		&& range->start <= range->stop)) {
		return NULL;
	}
	uint8_t * next;
	next = bytes->data + range->start;
	range->start += range->step;
	return next;
}


// Makes a deep copy of *src and stores it in *dest. Similar to *dest = *src.
//
// Pre:
//	src - Points to valid bytes_t variable and is not NULL.
//	dest - Points to valid bytes_t variable and is not NULL.
//
// Post:
//	If successful then *dest contains a copy of *src. Both *src and *dest
//	should be completely separate entities. Changing one should not 
//	affect the other.
//
// Returns:
//	If copying *src into *dest succeeds the function will return true.
//	If dynamic allocation is required, but fails this function will
//	return false.
//
bool bytes_copy(bytes_t * const dest, const bytes_t * const src)
{
	bytes_init(dest);
	for (int i = 0; i < src->usage; i++) {
		bytes_insert(dest, i, src->data + i, 1);
	}
	return true;
}

//On my honor:
//
//-I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants 
// assigned to this course.
//
//-I have not used C language code obtained from another student, 
// or any other unauthorized source, either modified or unmodified.  
//
//-If any C language code or documentation used in my program 
// was obtained from an allowed source, such as a text book or course
// notes, that has been clearly noted with a proper citation in
// the comments of my program.
//
// Nam Nguyen