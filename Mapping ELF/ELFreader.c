#include "ELFreader.h"

int main(int argc, char* argv[]) {
	file_data *files = NULL, *current_file;

	argv++;
	while (*argv) {
		current_file = readelf(*argv);
		if (files != NULL)
			current_file->next = files->next;
		files = current_file;
		printf("\n");
		argv++;
	}

	return 0;
}

void init_file(file_data *file) {
	file->file = malloc(sizeof(file_mapping));
	memset(file->file, 0, sizeof(file_mapping));
	file->symbols = malloc(sizeof(Symlists));
	memset(file->symbols, 0, sizeof(Symlists));
	file->main = 0;
	file->next = 0;
}

/* readelf <flags> <file name> <linked list pointer>	TODO : advanced	*/
file_data* readelf(char* name) {
	file_data *file;
	int fd;
	void *map_start; /* will point to the start of the memory maped file */
	struct stat fd_stat; /* this is needed to  the size of the file */

	file = malloc(sizeof(file_data));
	init_file(file);

	printf("File : %s\n", name);
	file->file_name = malloc(sizeof(*name));
	strcpy(file->file_name, name);

	if( (fd = open(name, 2)) < 0 ) {
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

/*	now, the file is mapped starting at map_start	*/
	read_header(file->file, map_start);
	read_sections(file->file, map_start);
	read_symbols(file->file, file->symbols, map_start);

	/* now, we unmap the file */
	munmap(map_start, fd_stat.st_size);
	memset(file->file, 0, sizeof(file_mapping));

	return file;
}

/* Lab 8 - Task 0 */
void read_header(file_mapping* file, void* start) {
	file->header = (Elf32_Ehdr *) start;
	Elf32_Ehdr *header = (Elf32_Ehdr *) start;
	int index;
	char *type = "ELF";

	printf("ELF Header:\n");
	/* now we can do whatever we want with header ! */

	printf("  Magic: ");
	for (index=1; index<4; index++) {
	/*	printf("%c ", (header->e_ident)[index]);
		printf("EI_MAG%d : %c\n", index, (header->e_ident)[index]);	*/
		if (type[index-1] != (header->e_ident)[index]) {
			perror("magic failed");
			exit(-1);
		}
	}
	printf("%31s", type);

	if (header->e_ident[index] != 1) {
		perror("\nclass failed");
		exit(-2);
	}
	else printf("\n  Class: %29d\n", header->e_ident[index]);
	printf("  Type: %30d\n", header->e_type);

	printf("  Entry point address: %21x (hexadecimal)\n", header->e_entry);

	printf("  Start of section headers: %13d (bytes into file)\n", header->e_shoff);
	file->section_headers = (Elf32_Shdr *) (start + header->e_shoff);

	printf("  Number of program headers: %9d\n", header->e_phnum);
	printf("  Number of section headers: %10d\n", header->e_shnum);

	printf("  Section header string table index: %d\n", header->e_shstrndx);
	file->shstrtab = start + (file->section_headers)[header->e_shstrndx].sh_offset;
	printf("\n");
}

/* Lab 8 - Tasks 1 */
void read_sections(file_mapping* file, void* start) {
	Elf32_Shdr *section;
	int index;

	printf("Section Header Table:\n");
	printf("[Nr]   name 	      size\n");

	for (index = 0 ; index < file->header->e_shnum ; index++) {
		section = &(file->section_headers)[index];
	/*	section = (Elf32_Shdr *) (map_shtable_start + index*header->e_shentsize);	*/
		printf("[%d] ", index);
		printf("%-15s ", file->shstrtab + section->sh_name);
		printf("%x\n", section->sh_size);

		if (strcmp(file->shstrtab + section->sh_name, ".symtab") == 0) {
			file->sym_size = (section->sh_size)/(section->sh_entsize);
			file->symbol_table = (Elf32_Sym *) (start + section->sh_offset);
		}

		else if (strcmp(file->shstrtab + section->sh_name, ".strtab") == 0)
			file->strtab = start + section->sh_offset;
	}
}

/* Lab 8 - Tasks 2 */
void read_symbols(file_mapping* file, Symlists* lists, void* start) {
	Elf32_Sym *symbol;
	char *sym_name;
	int index;

	printf("\nSymbol Table '.symtab' contains %d entries:\n", file->sym_size);
	for (index = 0 ; index < file->sym_size ; index++) {
		symbol = &(file->symbol_table)[index];
		printf("Symbol %3d: ", index);

		sym_name = file->strtab + symbol->st_name;
		printf("%-30s, ", sym_name);

		if ( strcmp(sym_name, "") != 0 ) {
			if (symbol->st_shndx == SHN_UNDEF) {
				lists->UnSymlist = register_entry(lists->UnSymlist, sym_name);
			}
			else lists->Symlist = register_entry(lists->Symlist, sym_name);
		}

		if (symbol->st_shndx > 0 && symbol->st_shndx < file->header->e_shnum)
			printf("bound to %s\n", file->shstrtab + (file->section_headers)[symbol->st_shndx].sh_name);
		else printf("\n");
	}
}


