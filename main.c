#include "bucket.h"
#include "hash.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLESIZE 100

HashTable *create_table(size_t size);
void destroy_table(HashTable *table);

int main() {
  printf("=========================================\n");
  printf("      RUNNING HASH TABLE TEST SUITE      \n");
  printf("=========================================\n\n");

  HashTable *t = create_table(TABLESIZE);
  assert(t != NULL);

  // ----------------------------------------------------------------
  // TEST 1: Basic Insertion and Retrieval
  // ----------------------------------------------------------------
  printf("[TEST 1] Testing basic insert and get...\n");

  unsigned char *key1 = (unsigned char *)"target";
  size_t hash1 = squish_hash(hash(key1), TABLESIZE);

  insert(t->bucket, hash1, key1, 99);
  int res1 = get(t->bucket, hash1, key1);

  assert(res1 == 99);
  printf("  -> Found inserted key! Value: %d (Expected: 99) -> PASS\n", res1);

  // Test looking for something that isn't there (should return -1)
  int missing_res = get(t->bucket, hash1, (unsigned char *)"not_here");
  assert(missing_res == -1);
  printf("  -> Non-existent key safely returned -1 -> PASS\n\n");

  // ----------------------------------------------------------------
  // TEST 2: Collision Chaining (Linked List Layering)
  // ----------------------------------------------------------------
  printf("[TEST 2] Testing collisions & Linked List layering...\n");

  // We will force three different keys into the exact same bucket slot manually
  size_t forced_slot = 42;
  unsigned char *kA = (unsigned char *)"apple";
  unsigned char *kB = (unsigned char *)"banana";
  unsigned char *kC = (unsigned char *)"cherry";

  insert(t->bucket, forced_slot, kA, 10);
  insert(t->bucket, forced_slot, kB, 20);
  insert(t->bucket, forced_slot, kC, 30);

  // Manually inspect the layers of pointers to see if they chained correctly
  Entry *head_node = t->bucket[forced_slot].head;
  assert(head_node != NULL);
  assert(strcmp(head_node->key, "apple") == 0 && head_node->value == 10);

  assert(head_node->next != NULL);
  assert(strcmp(head_node->next->key, "banana") == 0 &&
         head_node->next->value == 20);

  assert(head_node->next->next != NULL);
  assert(strcmp(head_node->next->next->key, "cherry") == 0 &&
         head_node->next->next->value == 30);
  printf(
      "  -> Linked list pointer layering matches expected structure -> PASS\n");

  // Verify that 'get' successfully walks down the chain to find the values
  assert(get(t->bucket, forced_slot, kA) == 10);
  assert(get(t->bucket, forced_slot, kB) == 20);
  assert(get(t->bucket, forced_slot, kC) == 30);
  printf("  -> get() successfully traverses deep collision layers -> PASS\n\n");

  // ----------------------------------------------------------------
  // TEST 3: Structural Deletions
  // ----------------------------------------------------------------
  printf("[TEST 3] Testing node removal mechanics...\n");

  // Case A: Remove from the middle of the chain (banana)
  remove_entry(t->bucket, forced_slot, "banana");
  assert(get(t->bucket, forced_slot, kB) == -1); // banana is gone
  assert(get(t->bucket, forced_slot, kA) == 10); // apple is still there
  assert(get(t->bucket, forced_slot, kC) == 30); // cherry is still there
  // Verify the chain closed the gap (apple->next should now point to cherry)
  assert(strcmp(t->bucket[forced_slot].head->next->key, "cherry") == 0);
  printf("  -> Middle node deletion & link reconstruction -> PASS\n");

  // Case B: Remove the head node of the chain (apple)
  remove_entry(t->bucket, forced_slot, "apple");
  assert(get(t->bucket, forced_slot, kA) == -1); // apple is gone
  // Verify that cherry stepped up to become the new head of the bucket
  assert(strcmp(t->bucket[forced_slot].head->key, "cherry") == 0);
  printf("  -> Head node deletion & replacement -> PASS\n\n");

  // Clean up remaining memory
  destroy_table(t);

  printf("=========================================\n");
  printf("      ALL TESTS PASSED SUCCESSFULLY      \n");
  printf("=========================================\n");
  return 0;
}

HashTable *create_table(size_t s) {
  Bucket *bucket = malloc(sizeof(Bucket) * s);
  for (size_t i = 0; i < s; i++) {
    bucket[i].head = NULL;
  }

  HashTable *table = malloc(sizeof(HashTable));
  table->bucket = bucket;
  table->size = s;

  return table;
}

void destroy_table(HashTable *table) {
  for (size_t i = 0; i < table->size; i++) {
    Entry *current = table->bucket[i].head;

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
