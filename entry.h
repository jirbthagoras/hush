#ifndef ENTRY_H
#define ENTRY_H
// A struct, notice that I add a self-pointer there because it will form a
// linked list (to prevent hash collision to happened)
typedef struct Entry {
  char *key;
  int value;
  struct Entry *next;
} Entry;

Entry *create_entry(char *key, int valua);
void free_entry(Entry *entry);
void link_entry(Entry *d, Entry *t);

#endif
