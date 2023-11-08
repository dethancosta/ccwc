#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

int count_bytes(FILE *file);
int count_lines(FILE *file);
int count_chars(FILE *file);
int count_words(FILE *file);

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Please provide a file name.\n");
		return EXIT_FAILURE;
	}
	int word_count = 0;
	int line_count = 0;
	int char_count = 0;
	char *filename = argv[argc-1]; // Assumes that filename is last argument given
	FILE *f = fopen(filename, "r"); 
	if (f == NULL) {
		printf("Error opening file\n");
		return EXIT_FAILURE;
	}
	setlocale(LC_CTYPE, "");

	int in_word = 0;
	wint_t c;
	while ((c = fgetwc(f)) != WEOF) {
		if (c == '\n') line_count++;
		char_count++;
		if (!iswspace(c)) {
			if (!in_word) {
				word_count++;
				in_word = 1;
			}
		} else {
			in_word = 0;
		}
	}

	if (argc == 3 && strcmp(argv[1], "-l") == 0) {
		printf("%d %s\n", line_count, filename);
	} else if (argc == 3 && strcmp(argv[1], "-m") == 0) {
		printf("%d %s\n", char_count, filename);
	} else if (argc == 3 && strcmp(argv[1], "-w") == 0) {
		printf("%d %s\n", word_count, filename);
	} else if (argc == 2) {
		printf("%d %d %d %s\n", line_count, word_count, char_count, filename);
	}
	fclose(f);
	return EXIT_SUCCESS;
}

