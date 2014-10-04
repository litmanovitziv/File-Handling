#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "linked_list.h"

/* 
 * If there is an entry in the list with tag_name - add 1 to the counter and return list.
 * Otherwise, add a new entry to the end of the list and return list.
 * If list is null - create a new entry and return a pointer to the entry.
 */
entry* register_entry(entry* list, char* tag_name) {
	entry *current = list, *prev = list;
	int found = 0;
	while (current != 0 && found == 0) {
		if (strcmp(tag_name, current->tag)==0) {
			(current->count)++;
			found++;
		/*	printf("student %s is appearing %d times (%d)\n", current->tag, current->count, found);
			list = 0;	*/
		}

		else {
			prev = current;
			current = current->next;
		}
	}

	if (found == 0) {	/* the string isn't found	*/
		current = malloc(sizeof(struct entry));
		current->next = 0;
		current->tag = malloc(strlen(tag_name));
		strcpy(current->tag, tag_name);
		current->count = 1;
		if (list==0) {
			list = current;
		/*	printf("student %s is added on %d time\n", current->tag, current->count);	*/
		}
		else {
			prev->next = current;
	/*		printf("previous student %s is added on %d time\n", prev->tag, prev->count);
			printf("student %s is added on %d time\n", (prev->next)->tag, (prev->next)->count);	*/
		}
	}

/*	printf("The top student %s is added on %d time\n", list->tag, list->count);	*/
	return list;
}

/*
 * For each entry in the list apply the function handler (that is given as a parameter).
 */
void foreach(entry* list, void (*handler)(entry* node)) {
	while (list != 0) {
		(*handler)(list);
		list = list->next;
	}
}

/* Free the memory allocated by the list */
void free_list(entry* list) {
	if (list->next != 0){
		free_list(list->next);
	}

	free(list->tag);
	free(list->next);
}

/*
 * Print one entry to the standard output (e.g. "Cohen - 2")
 */
void print_entry(entry* node) {
/*	printf("bigram %s is appearing %d times\n", link->bigram, link->count);	*/
	printf("%s is appearing %d times\n", node->tag, node->count);
}

/* Check one entry */
entry* check_tag(entry *list, char* tag_name) {
	entry* ans = NULL;
	while (list != 0) {
		if (strcmp(list->tag, tag_name) == 0) {
			ans = list;
			break;
		}
		list = list->next;
	}

	return ans;
}

/* Return the list length */
int list_length(entry* list) {
	int amount = 0;
	while (list != 0) {
		amount++;
		list = list->next;
	}
	return amount;
}
