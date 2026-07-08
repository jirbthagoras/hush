#include "hash.h"

ui64 hash(unsigned char *s) {
  ui64 hash = 5381;
  int c;

  while ((c = *s++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash;
}

size squish_hash(ui64 h, size ts) { return h % ts; };
