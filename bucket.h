#ifndef BUCKET_H
#define BUCKET_H

#include "hash.h"
typedef struct Entry {
  char *key;
  int value;
  struct Entry *next;
} Entry;

typedef struct Bucket {
  Entry *head;
} Bucket;

typedef struct {
  Bucket *bucket;
  size size;
} HashTable;

void insert(Bucket *bucket, unsigned long hash, unsigned char *key, int value);
int get(Bucket *bucket, unsigned long hash, unsigned char *key);

Entry *create_entry(unsigned char *key, int value);
void remove_entry(Bucket *bucket, unsigned long hash, char *key);

#endif
