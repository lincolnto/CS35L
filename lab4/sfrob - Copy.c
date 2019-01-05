#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// Helper Function - Unfrobnicates a single char c
char unfrob(const char c) {
	// Apply the memfrob algorithm to a single char to unfrob it
	return c ^ 42;
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
	
int main(void) {
	int numCols = 100;
	char *inp;
	inp = (char *)malloc(sizeof(char) * numCols); // Create an array to store inputs
	if (inp == NULL){
		fprintf(stderr, "Error: Could not allocate memory");
		exit(1);
	}
	char cur = ' '; // Store the current char read in from stdin
	int inp_i = 0;
	int numWords = 0;
	while (!feof(stdin)){
		cur = getchar();
		if (inp_i == numCols) { // Reached capacity for inp
			numCols = numCols * 2; 
			inp = realloc(inp, sizeof(char) * numCols); // Double the size of numCols, then realloc
			if (inp == NULL){
				fprintf(stderr, "Error: Could not re-allocate memory");
				exit(1);
			}
		}
		if (cur != EOF) {
			inp[inp_i] = cur;
			inp_i++;
		}
		if (cur == ' ') numWords++; // Keep track of number of words for later
	}
	
	// Stdin ends with partial record, no trailing space. Need to append a space.
	if (inp[inp_i - 1] != ' ') {
		if (inp_i == numCols) { // Check if we have enough space
			numCols++;
			inp = realloc(inp, sizeof(char) * numCols);
		}
		inp[inp_i - 1] == ' ';
		inp_i++;
		numWords++;
	}
	
	// Debugging: Print all of inp_i. Inp is all taken in correctly, check output
	// printf("========================\n==  INP ARRAY START:  ==\n========================\n");
	// for (int i = 0; i < inp_i; i++) {
	// 	printf("%c", inp[i]);
	// }
	// printf("!!!END!!!");
	// printf("\n========================\n==   INP ARRAY END:   ==\n========================\n");

	// Create an array of all the words
	char **words;
	words = (char **)malloc(sizeof(char *) * numWords);
	if (words == NULL) {
		fprintf(stderr, "Error: Could not allocate memory");
		exit(1);
	}
	int words_i = 0;
	int j = 0;
	words[words_i] = inp;
	while (j < inp_i) { // Go through inp, storing the first address encountered after a space into words
		j++;
		if (inp[j] == ' ') {
			// printf("Word %d:\n", words_i);
			// for (int q = 0; words[words_i][q]!= ' '; q++) {	printf("%c", words[words_i][q]); }
			// printf("\n");
			words_i++;
			if (j < inp_i) { // We have not reached the end of inp yet, so there are more words
				words[words_i] = &inp[j + 1];
			}
		}
	}

	// printf("\n==== WORDS ARR ====\n");
	// for (int z = 0; z < numWords; z++) {
	//	for (int v = 0; words[z][v] != ' '; v++) {
	// 		printf("%c", words[z][v] );
	//	}
	//	printf('\n');
	// }
	// printf("\n==== WORDS ARR ====\n");

	// Sort the words array
	qsort(words, numWords, sizeof(char*), frobcmp);

	// Print to stdout
	for (int k = 0; k < numWords; k++) {
		for (int m = 0; words[k][m] != ' '; m++) {
			putchar(words[k][m]);
		}
		putchar(' ');
	}
	free(inp);
	free(words);
}