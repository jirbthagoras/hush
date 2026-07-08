#include "bucket.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct {
  Bucket *bucket;
  size_t size;
} HashTable;

HashTable *create_table(size_t size);
void destroy_table(HashTable *table);

int main() {}

HashTable *create_table(size_t size) {
  Bucket *bucket = malloc(sizeof(Bucket) * size);
  for (size_t i = 0; i < size; i++) {
    bucket[i].head = NULL;
  }

  HashTable *table = malloc(sizeof(HashTable));
  table->bucket = bucket;
  table->size = size;

  return table;
}

void destroy_table(HashTable *table) {
  for (size_t i = 0; i < table->size; i++) {
    Entry *current = table->bucket[i].head;

    // Traverse
    while (current != NULL) {
      Entry *temp = current;
      current = current->next;

      free(temp->key);
      free(temp);
    }
  }

  free(table->bucket);
  free(table);
}
