#pragma once
#include "types.h"

#define offsetof(type,member)  (size_t)&(((type*)0)->member)

#define list_first_entry_or_null(ptr, type, member) ({ \
	struct list_head *head__ = (ptr); \
	struct list_head *next__ = head__->next; \
	head__ == next__ ? NULL : ((type *)(next__ - offsetof(type, member))); \
})

void list_del(struct list_head *entry) {
	entry->prev->next = entry->next;
	entry->next->prev = entry->prev;

	//? poison
}
void list_add(struct list_head* head, struct list_head* entry) {
	struct list_head* next = head->next;
	next->prev = entry;
	head->next = entry;
	entry->prev = head;
	entry->next = next;
}
