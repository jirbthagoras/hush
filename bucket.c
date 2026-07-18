#include "bucket.h"
#include <stdlib.h>
#include <string.h>

Entry *create_entry(unsigned char *key, int value) {
  Entry *new_entry = malloc(sizeof(Entry));
  new_entry->key = strdup((char *)key);
  new_entry->value = value;
  new_entry->next = NULL;
  return new_entry;
};

void insert(Bucket *bucket, unsigned long hash, unsigned char *key, int value) {
  Entry *new_entry = create_entry(key, value);

  if (bucket[hash].head == NULL)
    bucket[hash].head = new_entry;
  else {
    Entry *current = bucket[hash].head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_entry;
  }
}

int get(Bucket *bucket, unsigned long hash, unsigned char *key) {
  if (bucket[hash].head == NULL)
    return -1;

  Entry *current = bucket[hash].head;
  while (current != NULL) {
    if (!strcmp((char *)key, current->key))
      return current->value;
    current = current->next;
  }

  return -1;
}

void remove_entry(Bucket *bucket, unsigned long hash, char *key) {
  if (bucket[hash].head == NULL)
    return;

  Entry *current = bucket[hash].head;
  Entry *prev = bucket[hash].head;

  // Loop through the entries
  while (current != NULL) {
    // If key matches
    if (!strcmp(key, current->key)) {
      // If this entry is a head
      if (current == bucket[hash].head) {
        bucket[hash].head = current->next;
      }
      prev->next = current->next;
      free(current);
      return;
    }
    prev = current;
    current = current->next;
  }
}
