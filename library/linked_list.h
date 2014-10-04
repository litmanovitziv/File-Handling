#ifndef LINKED_LIST_H

typedef struct entry entry;

struct entry {
	entry *next;
	char *tag;
/*	int status = 0;	/* 0 - undefined, 1 - defined */
	int count;
};

/*
 * add a new entry to the end of the list and return list
 */
entry* register_entry(entry* list, char * tag_name);

/*
 * For each entry in the list apply the function handler
 */
void foreach(entry* list, void (*handler)(entry * node));

/*
 * Print one entry to the standard output (e.g. "Cohen - 2")
 */
void print_entry(entry * node);

/* Check one entry */
entry* check_tag(entry * list, char* tag_name);

/* Return the list length */
int list_length(entry* list);

/* Free the memory allocated by the list */
void free_list(entry* list);

#endif