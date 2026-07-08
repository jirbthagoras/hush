#include "entry.h"
#include <stdlib.h>
#include <string.h>

Entry *create_entry(char *key, int value) {
  Entry *new_entry = malloc(sizeof(Entry));
  new_entry->key = strdup(key);
  new_entry->value = value;
  new_entry->next = NULL;
  return new_entry;
};
