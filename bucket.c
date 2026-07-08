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
  Entry *new_entry = create_entry(key, value);

  if (bucket[hash]->head == NULL)
    bucket[hash]->head = new_entry;
  else {
    Entry *current = bucket[hash]->head;
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
  while (current != NULL) {
    if (strcmp(key, current->key))
      return (void *)&current->value;
    current = current->next;
  }

  return NULL;
}

void remove(Bucket *bucket[], unsigned long hash, char *key) {
  if (bucket[hash] == NULL)
    return;

  Entry *current = bucket[hash]->head;
  Entry *prev;

  // Loop through the entries
  while (current != NULL) {
    // If key matches
    if (strcmp(key, current->key)) {
      // If this entry is a head
      if (current == bucket[hash]->head) {
        bucket[hash]->head = current->next;
      }
      prev->next = current->next;
      free(current);
      return;
    }
    prev = current;
    current = current->next;
  }
}
