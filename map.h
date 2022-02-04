#ifndef MAP_H
#define MAP_H

#include <stdlib.h>

#define HASH(ID, CAPACITY) ({  \
    unsigned long i = 0;       \
    for (int j = 0; ID[j]; j++) \
        i += ID[j];             \
    i % CAPACITY;              \
})

typedef struct entry
{
    char *id;
    void *addr;
    size_t size;
    struct entry* next;
} entry_t;

typedef struct map
{
    size_t capacity;
    entry_t **entries;
} map_t;

map_t* create_map(size_t);
void delete_map(map_t *);
void delete_entry(entry_t*);
void put(map_t*, char*, void*, size_t);
void computeIfPresent(map_t*, char*, void (*function)(entry_t *));
entry_t* get(map_t *, char*);

#endif