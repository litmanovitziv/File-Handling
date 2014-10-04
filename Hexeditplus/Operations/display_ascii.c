#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*	display_ascii filename location length		*/
int main (int argc , char* argv[], char* envp[]) {
	FILE* file;
	char buffer;
	int check, length;

	if (argc != 4){
		perror("Not enough arguments!\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL) {
		printf("failure in file opening");
		exit(EXIT_FAILURE);
  	}

	check = fseek(file, atoi(argv[2]), SEEK_SET);
	if (check!=0) {
		printf("failure in file seeking");
		exit(EXIT_FAILURE);
  	}

  	length = atoi(argv[3]);
	while (length > 0) {
		int result = fread(&buffer,1, 1, file);
		if (result!=1){
			printf("failure in file reading");
			exit(EXIT_FAILURE);
		}
		if (buffer)
			printf("%c", buffer);
		else printf(".");

		length--;
	}
	printf("\n");

	fclose(file);
	return 0;
}
