#ifndef BUCKET_H
#define BUCKET_H

typedef struct Entry {
  char *key;
  int value;
  struct Entry *next;
} Entry;

typedef struct Bucket {
  Entry *head;
} Bucket;

void insert(Bucket *bucket[], unsigned long hash, char *key, int value);
void *get(Bucket *bucket[], unsigned long hash, char *key);

Entry *create_entry(char *key, int value);

#endif
