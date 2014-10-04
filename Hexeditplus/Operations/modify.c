#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define O_RDONLY 0
#define O_RDRW 2
#define O_CREAT 64

#define SEEK_SET 0

/*	modify file location value	*/
int main (int argc , char* argv[], char* envp[]) {
	FILE* file;
	int val, check;

	if (argc != 4){
		printf("Not enough arguments!\n");
		exit(EXIT_FAILURE);
	}

	// Opening the files
	if ((file = fopen(argv[1], "r+")) == NULL) {
		printf("failure in file1 opening");
		exit(EXIT_FAILURE);
	}

	// going to the locations
	if ((check = fseek(file, atoi(argv[2]), SEEK_SET)) != 0) {
		printf("failure in file1 seeking");
		exit(EXIT_FAILURE);
	}

	sscanf(argv[3], "%x", &val);
	fputc(val, file);
	fclose(file);
	return 0;
}
