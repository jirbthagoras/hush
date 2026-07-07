#include "hash.h"

// NEED TO KNOW: char is basically an array of pointer that leads to a 1 byte
// memory. Since it is an array (the memory is subsequential) you can iterate
// through it
ui64 hash(unsigned char *s) {
  ui64 hash = 5381;
  int c;

  // Here, I iterate through the char. By dereferencing it (using asterisk) I
  // can get the character and cast it into int.
  while ((c = *s++)) {
    // Enter the djb2 hashing algorithm here
    hash = ((hash << 5) + hash) + c;
  }

  return hash;
}

size array_indices(ui64 h, size ts) { return h & ts; };
