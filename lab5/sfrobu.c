#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>

// Helper Function - Unfrobnicates a single char c
char unfrob(const char c) {
	// Apply the memfrob algorithm to a single char to unfrob it
	return c ^ 42;
}

int frobcmp_fopt(const void* a, const void* b){
	int i = 0;
	char *a1 = *(char **)a;
	char *b1 = *(char **)b;
	char ua, ub;
	while (a1[i] != ' ' && b1[i] != ' ')
	{
		ua = unfrob(a1[i]);
		ub = unfrob(b1[i]);
		ua = toupper( (unsigned char)ua );
		ub = toupper( (unsigned char)ub );
		if (ua == ub) { // Current char is equal, keep checking array
			i++;
			continue;
		}
		else if (ua > ub)
			return 1;
		else if (ua < ub)
			return -1;
	}
	// If we reach this point, one array is a prefix of the other
	// or the arrays are equal
	if (a1[i] == ' ' && b1[i] != ' ')
		return -1;
	else if (a1[i] != ' ' && b1[i] == ' ')
		return 1;
	else
		return 0;
}

int frobcmp(const void* a, const void* b) {
	int i = 0;
	char *a1 = *(char **)a;
	char *b1 = *(char **)b;
	char ua, ub;
	while (a1[i] != ' ' && b1[i] != ' ')
	{
		ua = unfrob(a1[i]);
		ub = unfrob(b1[i]);
		if (ua == ub) { // Current char is equal, keep checking array
			i++;
			continue;
		}
		else if (ua > ub)
			return 1;
		else if (ua < ub)
			return -1;
	}
	// If we reach this point, one array is a prefix of the other
	// or the arrays are equal
	if (a1[i] == ' ' && b1[i] != ' ')
		return -1;
	else if (a1[i] != ' ' && b1[i] == ' ')
		return 1;
	else
		return 0;
}
	
int main(int argc, char *argv[]) {
	struct stat fStats;
	if(fstat(0, &fStats) < 0){
		fprintf(stderr, "Error: fstats");
	}
	
	// Allocate memory
	int numCols = 100;
	char *inp;

	if(S_ISREG(fStats.st_mode)){ // Input is a regular file, allocate data to store entire file
		inp = (char *)malloc(fStats.st_size * sizeof(char));
		numCols = (int)fStats.st_size;
	}
	else{
		inp = (char *)malloc(sizeof(char) * numCols); // Initially allocate arbitrary amount of data
	}
	if (inp == NULL){ // Error Checking: problems allocating memory
		fprintf(stderr, "Error: Could not allocate memory");
		exit(1);
	}
	char cur[1]; // Store the current char read in from stdin
	ssize_t curState = read(0, cur, 1);
	if(curState < 0){
		fprintf(stderr, "Error: IO error while trying to read into cur buffer");
		exit(1);
	}
	int inp_i = 0;

	while (curState != 0){
		if (inp_i == numCols) { // Reached capacity for inp, need to reallocate memory
			numCols = numCols * 2; 
			inp = realloc(inp, sizeof(char) * numCols); // Double the size of numCols, then realloc
			if (inp == NULL){
				fprintf(stderr, "Error: Could not re-allocate memory");
				exit(1);
			}
		}
		if (cur != 0) {
			inp[inp_i] = cur[0];
			inp_i++;
		}
		curState = read(0, cur, 1);
	}
	
	// Stdin ends with partial record, no trailing space. Need to append a space.
	if (inp[inp_i - 1] != ' ') {
		if (inp_i == numCols) { // Check if we have enough space
			numCols++;
			inp = realloc(inp, sizeof(char) * numCols);
		}
		inp[inp_i - 1] == ' ';
		inp_i++;
	}
	
	//Debugging: Print all of inp_i. Inp is all taken in correctly, check output
	// printf("========================\n==  INP ARRAY START:  ==\n========================\n");
	// for (int i = 0; i < inp_i; i++) {
	//  	printf("%c", inp[i]);
	// }
	// printf("!!!END!!!");
	// printf("\n========================\n==   INP ARRAY END:   ==\n========================\n");

	const int inp_size = inp_i;

	// Create an array of all the words
	char **words = (char **)malloc(0);
	int words_size = 0;
	char *curword = (char *)malloc(0);
	int curword_size = 0;
	int j = 0;
	// printf("\n==Words N Shit==\n");
	while (j < inp_size) {
		// Store each char in inp into curword, up to the next space
		curword = realloc(curword, sizeof(char) * (++curword_size) );
		// If we hit a space, add curword to words
		char curChr = inp[j];
		// printf("%c", curChr);
		if (curChr == ' ') {
			// Store the word
			// printf("Storing: %c\n", curword[curword_size - 2]);
			curword[curword_size - 1] = ' ';
			words = realloc(words, sizeof(char *) * (++words_size) );
			words[words_size - 1] = curword;
			// Clear curword
			curword = (char *)malloc(0);
			curword_size = 0;
		}
		else {
			curword[curword_size - 1] = curChr;
		}
		j++;
	}
	// Get the last word
	curword[curword_size - 1] = ' ';
	words = realloc(words, sizeof(char *) * (++words_size) );
	words[words_size - 1] = curword;

//	printf("Words Size: %d", words_size);
//	printf(".END.\n==Words N Shit==\n");

//	printf("\nDEBUG:\n");
//	for (int k = 0; k < words_size; k++) {
//		for (int m = 0; words[k][m] != ' '; m++) {
//			printf("%c", words[k][m]);
//		}
//		printf(" ");
//	}
//	printf("\nDEBUG:\n");
	// Check for -f argument
	bool f_opt = false;
	if (argc > 1 && strcmp(argv[1], "-f") == 0) // Need to use toupper
		f_opt = true;

	// Sort the words array
	if (f_opt) qsort(words, words_size, sizeof(char*), frobcmp_fopt);
	else qsort(words, words_size, sizeof(char*), frobcmp);

	// Print to stdout
	for (int k = 0; k < words_size; k++) {
		for (int m = 0; words[k][m] != ' '; m++) {
			putchar(words[k][m]);
		}
		putchar(' ');
	}
	free(inp);
	free(words);
}