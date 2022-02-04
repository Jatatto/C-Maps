#include <string.h>
#include "map.h"

void delete_map(map_t *map)
{
    for (size_t i = 0; i < map->capacity; i++)
    {
        if (map->entries[i] != NULL)
        {
            delete_entry(map->entries[i]);
        }
    }
    free(map->entries);
    free(map);
}

void delete_entry(entry_t *entry)
{
    if (entry->next != NULL)
    {
        delete_entry(entry->next);
    }
    free(entry->addr);
    free(entry->id);
    free(entry);
}

static entry_t *create_entry(char *id, void *addr, size_t size)
{
    entry_t *entry = malloc(sizeof(struct entry));
    char *copy = malloc((strlen(id) + 1) * sizeof(id));
    strcpy(copy, id);
    entry->id = copy;
    entry->next = NULL;
    entry->addr = malloc(size);
    memcpy(entry->addr, addr, size);
    return entry;
}

map_t *create_map(size_t def_cap)
{
    map_t *map = (map_t *)calloc(1, sizeof(struct map));
    map->capacity = def_cap;
    map->entries = (entry_t **)calloc(def_cap, sizeof(struct entry));
    return map;
}

void put(map_t *map, char *id, void *addr, size_t size)
{
    unsigned long hash = HASH(id, map->capacity);
    entry_t *ptr = map->entries[hash];
    if (ptr == NULL)
    {
        map->entries[hash] = create_entry(id, addr, size);
    }
    else
    {
        while (ptr->next != NULL && strcmp(id, ptr->id) != 0)
        {
            ptr = ptr->next;
        }
        if (strcmp(ptr->id, id) == 0)
        {
            memcpy(ptr->addr, addr, size);
        }
        else
        {
            ptr->next = create_entry(id, addr, size);
        }
    }
}

entry_t *get(map_t *map, char *id)
{
    entry_t *ptr = map->entries[HASH(id, map->capacity)];
    while (ptr != NULL && strcmp(ptr->id, id) != 0)
    {
        ptr = ptr->next;
    }
    return ptr;
}

void computeIfPresent(map_t *map, char*id, void (*function)(entry_t*eptr)){
    entry_t *ptr = get(map, id);
    if(ptr != NULL){
        function(ptr);
    }
}