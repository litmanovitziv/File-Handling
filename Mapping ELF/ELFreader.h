/* ELFreader.h */
#ifndef _ELF_READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <sys/stat.h>

#include "../library/elf.h"
#include "../library/linked_list.h"

typedef struct mapping {
	Elf32_Ehdr *header;
	Elf32_Shdr *section_headers;
	Elf32_Sym *symbol_table;
	char *shstrtab, *strtab;	/* shstrtab points to Section Heades string table */
	int sym_size;
} file_mapping;

typedef struct lists {
	entry *Symlist;
	entry *UnSymlist;
} Symlists;

typedef struct data file_data;
struct data {
	char* file_name;
	file_mapping *file;
	Symlists *symbols;
	void* main;
	file_data *next;
};

void init_file(file_data *file);
file_data* readelf(char* names);
void read_header(file_mapping* file, void* start);
void read_sections(file_mapping* file, void* start);
void read_symbols(file_mapping* file, Symlists* lists, void* start);

#endif
