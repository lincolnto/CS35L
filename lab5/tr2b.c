#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

int main(int argc, char** argv){
	/* Error Checking: */
	// Check for corrent number of arguments
	if (argc != 3){
		fprintf(stderr, "Error: Incorrect number of operands. Please input 2 operands");
		exit(1);
	}
	// Check if from and to are the same length
	char *from = argv[1];
	char *to = argv[2];
	size_t from_len = strlen(from);
	size_t to_len = strlen(to);
	if (from_len != to_len) { 
		fprintf(stderr, "Error: Operands from and to are not the same length!");
		exit(1);
	}

	// Check if from has duplicate bytes
	bool foundChars[256] = { false }; // Create an array for all chars. 1 = char is in from, 0 = char is not in from
	for (int i = 0; i < from_len; i++){
		int ch = from[i] - '0';
		if (foundChars[ch] == true){
			fprintf(stderr, "Error: Duplicate byte found in from");
			exit(1);
		}
		foundChars[ch] = true;
	}

	/* Begin Transliteration */

	while( !feof(stdin) ){
		char cur = getchar();
		bool byte_trans = false;
		for (size_t i = 0; i < from_len; i++){
			if (cur == from[i]) {// Byte needs to be transliterated
				byte_trans = true;
				putchar(to[i]);
				break;
			}
			else byte_trans = false; // Byte does not need to be transliterated
		}
		if (byte_trans == false){
			putchar(cur);
		}
	}

	return 0;
}