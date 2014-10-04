#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <sys/stat.h>

#include "../library/elf.h"
#include "../library/linked_list.h"

typedef struct lists {
	entry *Symlist;
	entry *UnSymlist;
} Symlists;

void readelf(void*, Symlists*, int*);

/* Check one entry whether exceed one */
void check_count(entry* node) {
	if (node->count > 1) {
		printf("\nduplicate check: FAILED (%s)\n", node->tag);
		exit(-1);
	}
}

void check_define(entry* Symlist1, entry* Symlist2) {
	int found;
	while (Symlist1 != 0) {
		found = 0;
		while (Symlist2 != 0) {
			if ( (strcmp(Symlist1->tag, "") == 0) ||
				(strcmp(Symlist1->tag, Symlist2->tag) == 0) )
					found = 1;
			Symlist2 = Symlist2->next;
		}

		if (found == 0) {
			printf("no missing symbol : FAILED (%s)\n", Symlist1->tag);
			exit(-1);
		}
		Symlist1 = Symlist1->next;
	}
}

/* Check at least one main entry */
void check_main(entry* list) {
	while (list != 0) {
		if (strcmp(list->tag, "main") == 0) {
			printf("main check: PASSED\n");
			return;
		}
		list = list->next;
	}

	printf("main check: FAILED\n");
	exit(-1);
}

int main(int argc, char* argv[], char* envp[]) {
	int fd;
	void *map_start; /* will point to the start of the memory maped file */
	struct stat fd_stat; /* this is needed to  the size of the file */

	int count_main = 0;
	Symlists* symbols = malloc(sizeof(Symlists));

	int file;
	for (file = 1; file<argc; file++) {
		printf("Checking the file : %s\n", argv[file]);

		if( (fd = open(argv[file], 2)) < 0 ) {
			perror("error in open");
			exit(-1);
		}
		
		if( fstat(fd, &fd_stat) != 0 ) {
			perror("stat failed");
			exit(-1);
		}
		
		if ( (map_start = mmap(0, fd_stat.st_size, PROT_READ | PROT_WRITE , MAP_SHARED, fd, 0)) == MAP_FAILED ) {
			perror("mmap failed");
			exit(-4);
		}

	/*	now, the file is mapped starting at map_start.		*/
		readelf(map_start, symbols, &count_main);

		/* now, we unmap the file */
		munmap(map_start, fd_stat.st_size);
	}

	printf("Final Results :\n");
	if (count_main != 1) {
		printf("main check: FAILED\n");
		exit(-1);
	}
	printf("main check: PASSED\n");

	foreach(symbols->Symlist, check_count);		/* Task 3b */
	printf("duplicate check: PASSED\n");

	check_define(symbols->UnSymlist, symbols->Symlist);	/* Task 3c */
	printf("no missing symbol : PASSED\n");

	return 0;
}

void readelf(void* map_start, Symlists* lists, int* count_main) {
	Elf32_Ehdr *header; /* this will point to the header structure */
	Elf32_Shdr *section_headers, *section; /* this will point to the section structure */
	Elf32_Sym *symbol_table, *symbol;
	char *shstrtab, *strtab, *sym_name;
	int index, sym_size;

	/* Lab 8 - Task 0 */
	printf("ELF Header:\n");
	header = (Elf32_Ehdr *) map_start;
	/* now we can do whatever we want with header ! */

	printf("Magic : ");
	char* s = "ELF";	/* the desired string */
	for (index=1; index<4; index++) {
		printf("%c ", (header->e_ident)[index]);
	/*	printf("EI_MAG%d : %c\n", index, (header->e_ident)[index]);	*/
		if (s[index-1] != (header->e_ident)[index]) {
			perror("elf failed");
			exit(-1);
		}
	}

	if (header->e_ident[index] != 1) {
		perror("\nclass failed");
		exit(-2);
	}
	else printf("\nClass: %d\n", header->e_ident[index]);

	printf("Type: %d\n", header->e_type);
	printf("Entry point address: 0x%x\n", header->e_entry);
	printf("Start of section headers: %d (bytes into file)\n", header->e_shoff);
	printf("Number of program headers : %d\n", header->e_phnum);
	printf("Number of section headers : %d\n", header->e_shnum);
	printf("Section header string table index : %d\n", header->e_shstrndx);

	/* Lab 8 - Tasks 1 */
	printf("\nSection Header Table:\n");
	printf("[inx]   name 	      size\n");
	section_headers = (Elf32_Shdr *) (map_start + header->e_shoff);

	shstrtab = map_start + section_headers[header->e_shstrndx].sh_offset; /* shstrtab points to Section Heades string table */

	for (index = 0 ; index < header->e_shnum ; index++) {
		section = &section_headers[index];
	/*	section = (Elf32_Shdr *) (map_shtable_start + index*header->e_shentsize);	*/
		printf("[%d] - ", index);
		printf("%-15s ", shstrtab + section->sh_name);
		printf("%x\n", section->sh_size);

		if (strcmp(shstrtab+section->sh_name, ".symtab") == 0) {
			sym_size = (section->sh_size)/(section->sh_entsize);
			symbol_table = (Elf32_Sym *) (map_start + section->sh_offset);
		}

		else if (strcmp(shstrtab+section->sh_name, ".strtab") == 0)
			strtab = map_start + section->sh_offset;
	}

	/* Lab 8 - Tasks 2 */
	printf("\nSymbol Table '.symtab' contains %d entries:\n", sym_size);
	for (index = 0 ; index < sym_size ; index++) {
		symbol = &symbol_table[index];
		printf("Symbol %3d: ", index);

		sym_name = strtab + symbol->st_name;
		printf("%-30s, ", sym_name);

		if ( strcmp(sym_name, "") != 0 ) {
			if (symbol->st_shndx == SHN_UNDEF) {
				lists->UnSymlist = register_entry(lists->UnSymlist, sym_name);
			}
			else lists->Symlist = register_entry(lists->Symlist, sym_name);
		}

		if ( strcmp(sym_name, "main") == 0 )
			(*count_main)++;

		if (symbol->st_shndx > 0 && symbol->st_shndx < header->e_shnum)
			printf("bound to %s\n", shstrtab + section_headers[symbol->st_shndx].sh_name);
		else printf("\n");
	}
	printf("\n");
}