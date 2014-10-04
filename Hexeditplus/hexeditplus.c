#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../library/LineParser.h"

typedef struct fun_arg_char {
	char *name;
	void (*fun)(char*);
} Function;

void display(char*);
void display_ascii(char*);
void modify(char*);
void Copy_from_file(char*);
void Copy_from_mem(char*);
void quit(char*);

void execute(cmdLine* pCmdLine){
	char *command = pCmdLine->arguments[0];

	int ans = execvp(command, pCmdLine->arguments);
	if (ans==-1){
		perror("command isn't valid \n");
		exit(0);
	}
}

int main (int argc, char** argv){
	int pid;
	Function menu[] = { { "Display", display }, { "Display(ascii)", display_ascii }, {"Modify", modify} , 
				{ "Copy from file" ,Copy_from_file} , { "Copy from memory" , Copy_from_mem }, {"Quit" , NULL} };

	while(1) {
		printf("Menu :\n");
		int index = 0;
		int length = (sizeof(menu))/(sizeof(Function));	/* The allocated size of menu devided into the allocated size of Function */
		while (index<length){
			printf("%d - %s\n", index, menu[index].name);
			index++;
		}

		int choice = -1;
		while(choice<0 || choice>length) {
			printf("\nWhich function would you like ? ");
			scanf("%d", &choice);
		}

		if (choice == 5)
			break;

		getchar();
		pid = fork();
		if (pid==0)	/* The child */
			menu[choice].fun(argv[1]);
		else if (pid > 0) {	/* The parent */
			waitpid(pid, 0, 0);
			printf("\n");
		}
	}

	return 0;
}

/*	display filename location length	*/
void display(char* file) {
	char* line = malloc(256);
	char input[10];

	strcpy(line, "./Operations/display");
	strcat(line, " ");
	strcat(line, file);
	strcat(line, " ");

	printf("Which position would you like to present from ? ");
	gets(input);
	strcat(line, input);
	strcat(line, " ");

	printf("How many would you like to present ? ");
	gets(input);
	strcat(line, input);

	execute(parseCmdLines(line));
}

/*	display_ascii filename location length	*/
void display_ascii(char* file) {
	char* line = malloc(256);
	char input[10];

	strcpy(line, "./Operations/display_ascii");
	strcat(line, " ");
	strcat(line, file);
	strcat(line, " ");

	printf("Which position would you like to present from ? ");
	gets(input);
	strcat(line, input);
	strcat(line, " ");

	printf("How many would you like to present ? ");
	gets(input);
	strcat(line, input);

	execute(parseCmdLines(line));
}

/*	modify file location value	*/
void modify(char* file) {
	char* line = malloc(256);
	char input[10];

	strcpy(line, "./Operations/modify");
	strcat(line, " ");
	strcat(line, file);
	strcat(line, " ");

	printf("Which position would you like to write into ? ");
	gets(input);
	strcat(line, input);
	strcat(line, " ");

	printf("Which volue would you like to write ? ");
	gets(input);
	strcat(line, input);

	execute(parseCmdLines(line));
}

/*	patch_file sourcefile src_location targetfile tgt_location length	*/
void Copy_from_file(char* file) {
	char* line = malloc(256);
	char input[10];

	strcpy(line, "./Operations/patch_file");
	strcat(line, " ");

	printf("Which file would you like to write from ? ");
	gets(input);
	strcat(line, input);
	strcat(line, " ");

	printf("Where (in source file) would you like to copy from ? ");
	gets(input);
	strcat(line, input);
	strcat(line, " ");

	printf("The target file is %s\n", file);
	strcat(line, file);
	strcat(line, " ");

	printf("Where (in turget file) would you like to write ? ");
	gets(input);
	strcat(line, input);
	strcat(line, " ");

	printf("How many bytes would you like to copy ? ");
	gets(input);
	strcat(line, input);

	execute(parseCmdLines(line));
}

/*	patch_mem targetfile tgt_location mem_location length	*/
void Copy_from_mem(char* file) {
	char* line = malloc(256);
	char input[10];

	strcpy(line, "./Operations/patch_mem");
	strcat(line, " ");

	printf("The target file is %s\n", file);
	strcat(line, file);
	strcat(line, " ");

	printf("Where would you like to write ? ");
	gets(input);
	strcat(line, input);
	strcat(line, " ");

	printf("Where would you like to copy from ? ");
	gets(input);
	strcat(line, input);
	strcat(line, " ");

	printf("How many bytes would you like to copy ? ");
	gets(input);
	strcat(line, input);

	printf("%s\n", line);
	execute(parseCmdLines(line));
}
