#ifndef HASH_H
#define HASH_H

#include <stddef.h>
#include <stdint.h>

typedef uint64_t ui64;
typedef size_t size;

uint64_t hash(unsigned char *s);
size squish_hash(ui64 h, size ts);

#endif
