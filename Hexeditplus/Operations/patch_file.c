#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*	patch_file sourcefile src_location targetfile tgt_location length	*/
int main (int argc , char* argv[], char* envp[]) {
	FILE *file_1, *file_2;
	char buffer;
	int check_1, check_2, length;

	if (argc != 6) {
		printf("Not enough arguments! Bye\n");
		exit(EXIT_FAILURE);
	}

	// Opening the files
	file_1 = fopen(argv[1], "r");
	if (file_1==NULL) {
		printf("failure in file1 opening");
		exit(EXIT_FAILURE);
	}

	file_2 = fopen(argv[3], "r+");
	if (file_2==NULL) {
		printf("failure in file2 opening");
		exit(EXIT_FAILURE);
	}

	/* going to the locations */
	check_1 = fseek(file_1, atoi(argv[2]), SEEK_SET);
	if (check_1!=0) {
		printf("failure in file1 seeking");
		exit(EXIT_FAILURE);
	}
	
	check_2 = fseek(file_2, atoi(argv[4]), SEEK_SET);
	if (check_2!=0) {
		printf("failure in file2 seeking");
		exit(EXIT_FAILURE);
	}

  	length = atoi(argv[5]);
	while (length > 0) {
		int result = fread(&buffer,1, 1, file_1);
		if (result!=1){
			printf("failure in file reading");
			exit(EXIT_FAILURE);
		}
		fwrite(&buffer,1 , 1, file_2);

		length--;
	}

	fclose(file_1);
	fclose(file_2);
	return 0;
}