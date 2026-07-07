#include "entry.h"
#include <stdlib.h>

Entry *create_entry(char *key, int value) {
  Entry *new_entry = malloc(sizeof(Entry));
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = NULL;
  return new_entry;
};

void link_entry(Entry *d, Entry *t) { d->next = t; }

void free_entry(Entry *entry) { free(entry); };
