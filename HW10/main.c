#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

#include "string_type.h"
#include "txtfile.h"


int main(int argc, char ** argv)
{
	size_t num_lines;
	string_t *lines = NULL;

	if (argc != 2)
	{
		printf("Must supply a filename on the command line.\n");
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");

	if (fp == NULL)
	{
		printf("Coudn't open file %s.\n", argv[1]);
		return 2;
	}

	// Try to read the file line by line.
	if (!txtfile_readlines(fp, &lines, &num_lines))
	{
		printf("Error reading lines from text file %s\n", argv[1]);
		return 3;
	}
	printf("done with readl ine");
	fclose(fp);
	printf("Find duplicate words in file %s:\n", argv[1]);

	// This is our previous word, starts out as the empty string.
	string_t prev;
	string_init(&prev);

	for (size_t l = 0; l < num_lines; l++)
	{
		size_t num_words; 
		string_t *words = NULL;
		size_t ln = l + 1;

		// Try to split up the line into words.
		if(!string_split(&words, &lines[l], " \t", &num_words))
		{
			printf("Error spliting line %zu", ln);
			break;
		}

		// Examine each word in the line.
		for (size_t w = 0; w < num_words; w++)
		{
			// Test with the previous word, if it's equal to
			// the current word, we've found a duplicate.
			if (strcmp(string_c_str(&prev), 
				string_c_str(&words[w])) == 0)
			{
				printf("\tDuplicate word %s on line %zu\n",
					string_c_str(&words[w]), ln);
			}

			// Current word becomes the previous word.
			if (!string_copy(&prev, &words[w]))
			{
				printf("Error copying word on line %zu\n", ln);
			 	break;
			}
		}

		// We're done with the result of the split, so deallocate.
		string_free_split(words, num_words);

	}

	printf("Print all of the lines, they should be unchanged:\n");
	for (size_t l = 0; l < num_lines; l++)
	{
		printf("\t%s\n", string_c_str(&lines[l]));
	}
	
	string_t joined;
	string_init(&joined);

	// Join the lines in the file with the separator CS2505	
	if(string_join(&joined, lines, num_lines, "CS2505"))
	{
		printf("Join the file lines with 'CS2505': \n");
		printf("'%s'\n", string_c_str(&joined));
	}

	
	printf("Try to erase 1000 from joined string: \n");
	string_erase(&joined, 10, 1000);

	printf("Erase the rest of the character from the end one by one: \n");
	while (!string_empty(&joined))
	{
		string_erase(&joined, string_len(&joined) - 1, 1);
		printf("'%s'\n", string_c_str(&joined));
	}

	// Some clean up, deallocate lines, joined, and prev.
	string_free_split(lines, num_lines);
	string_free(&joined);
	string_free(&prev);
	string_t test;
	string_init(&test);

	// printf("Insert characters\n");
	// char a = 'A';
	// char b = 'B';
	// char c = 'C';
	// char d = 'D';
	// char e = 'E';
	// char f = 'F';
	// char g = 'G';
	// char h = 'H';
	// char i = 'I';
	// char j = 'J';
	// char k = 'K';
	// char l = 'L';
	// char m = 'M';
	// char n = 'N';
	// char o = 'O';
	// char p = 'P';
	// char q = 'Q';
	// char r = 'R';
	// char s = 'S';
	// char t = 'T';
	// char u = 'U';
	// char v = 'V';
	// char w = 'W';
	// char x = 'X';
	// char y = 'Y';
	// char z = 'Z';
	// string_insert(&test, 0, &s, 1);
	// string_insert(&test, 0, &n, 1);
	// string_insert(&test, 0, &l, 1);
	// string_insert(&test, 0, &n, 1);
	// string_insert(&test, 0, &k, 1);
	// string_insert(&test, 0, &g, 1);
	// string_insert(&test, 0, &j, 1);
	// string_insert(&test, 0, &r, 1);
	// string_insert(&test, 0, &k, 1);
	// string_insert(&test, 0, &a, 1);
	// char * string = "QCQUY\tCaJWDLYOe\tW\tPXZiRB\tSBGoAVDQZW\tuPORAN\tNDBSRR";
	// string_insert(&test, 0, string, strlen(string));
	// printf("The contents are:\n\"%s\"\n", string_c_str(&test));

	// char * delim = "\t";

	// size_t num_words; 
	// string_t *words = NULL;
	// 	size_t ln = l + 1;

	// 	// Try to split up the line into words.
	//
	// printf("\nPoint2: Memory allocated: %d bytes\n",malloc_usable_size(words));
	// if(!string_split(&words, &test, delim, &num_words))
	// {
	// 	printf("Error spliting line\n");
	// 	return 1;
	// }	
	
	// printf("\nPoint2: Memory allocated: %d bytes\n",malloc_usable_size(words));

	// printf("number of splits:\n%d\n", num_words);
	// printf("string:\n%s\n", string_c_str(&test));
	// FILE *fp = fopen(argv[1], "r");
	// printf("before readline\n");
	// txtfile_readlines(fp, &words, &num_words);
	// printf("after readline\nwords: %d", num_words);
	// for (size_t w = 0; w < num_words; w++)
	// {
	// 	printf("Token %d is:\n\"%s\"\n", w, string_c_str(&words[w]));
	// }
	// fclose(fp);
	// fp = fopen(argv[1], "r");
	// string_t filestuf;
	// if (fp == NULL)
 // 	{
 // 		printf("Coudn't open file %s.\n", argv[1]);
	// 	return 2;
	// }
	// txtfile_read(fp, &filestuf);
	// printf("File:\n%s\n", string_c_str(&filestuf));

	return 0;
}
