#ifndef BUCKET_H
#define BUCKET_H

#include "entry.h"

// This is the bucket of hashed keys. This is where the hash result from djb2
// hasher will belong. The hash reuslt also needs to be squished so that the
// hash number is not too large and ranged between 100 - BUCKET_SIZE
typedef struct Bucket {
  Entry *head;
} bucket;

#endif
