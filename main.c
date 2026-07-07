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

// Creates the hash table yahahah
HashTable *create_table(size_t size) {
  // Allocate memory for the bucket inside the hash table later. The bucket size
  // multiplied by the TRUE size of the byte struct
  Bucket *bucket = malloc(sizeof(Bucket) * size);
  // Set all of them to NULL, cuz it is essential for scanning the available
  // bucket
  for (size_t i = 0; i < size; i++) {
    bucket[i].head = NULL;
  }

  // Allocate for hash table, this time only one hash table (cuz it is not an
  // array)
  HashTable *table = malloc(sizeof(HashTable));
  table->bucket = bucket;
  table->size = size;

  return table;
}

// Free up all of them, promise me i'll make arena later, malloc() and free()
// are pain in the ass.
void destroy_table(HashTable *table) {
  // iterate through the bucket and free up all of the linked list
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
