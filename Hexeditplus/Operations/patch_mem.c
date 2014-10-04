#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*	patch_mem targetfile tgt_location mem_location length	*/
int main (int argc , char* argv[], char* envp[]) {
	FILE* file;
	char* source_pos;

	if (argc != 5){
		printf("Not enough arguments! Bye\n");
		exit(EXIT_FAILURE);
	}

	/* Opening the files */
	if ((file = fopen(argv[1], "r+")) == NULL) {
		printf("failure in file1 opening");
		exit(EXIT_FAILURE);
	}

	/* going to the locations */
	if (fseek(file, atoi(argv[2]), SEEK_SET) != 0) {
		printf("failure in file seeking");
		exit(EXIT_FAILURE);
	}

	sscanf(argv[3], "%p", &source_pos);
	fwrite(source_pos, 1, atoi(argv[4]), file);
	printf("\n");

	fclose(file);
	return 0;
}