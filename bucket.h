#ifndef BUCKET_H
#define BUCKET_H

#include "entry.h"

// This is the bucket of hashed keys. This is where the hash result from djb2
// hasher will belong. The hash reuslt also needs to be squished so that the
// hash number is not too large and ranged between 100 - BUCKET_SIZE
typedef struct Bucket {
  Entry *head;
} Bucket;

// Insert the key-val into bucket, first check the index, then check the Entry
// pointed from the Bucket.
void insert(Bucket *bucket[], unsigned long hash, char *key, int value);

#endif
