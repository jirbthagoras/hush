#include "bucket.h"
#include <stdlib.h>
#include <string.h>

Entry *create_entry(char *key, int value) {
  Entry *new_entry = malloc(sizeof(Entry));
  new_entry->key = strdup(key);
  new_entry->value = value;
  new_entry->next = NULL;
  return new_entry;
};

void insert(Bucket *bucket[], unsigned long hash, char *key, int value) {
  Entry *head_entry = bucket[hash]->head;
  Entry *new_entry = create_entry(key, value);

  if (head_entry == NULL)
    bucket[hash]->head = new_entry;
  else {
    Entry *current = head_entry;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_entry;
  }
}

void *get(Bucket *bucket[], unsigned long hash, char *key) {
  if (bucket[hash] == NULL)
    return NULL;

  Entry *current = bucket[hash]->head;
  while (current->next != NULL) {
    if (strcmp(key, current->key))
      return (void *)&current->value;
    current = current->next;
  }
  return NULL;
}
