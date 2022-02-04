#include <stdio.h>
#include "map.c"

#define consumer(args, block) ({                   \
    void temp_consumer(args){block} temp_consumer; \
})

int main()
{

    map_t *map = create_map(50);
    int integer = 50;
    char *string = "this is a string";

    put(map, "integer", &integer, sizeof(integer));
    put(map, "string", string, sizeof(char) * strlen(string));

    computeIfPresent(map, "integer", consumer(entry_t * eptr, {
                         printf("%d\n", *(int *)eptr->addr);
                     }));

    computeIfPresent(map, "string", consumer(entry_t * eptr, {
                         printf("%s\n", (char *)eptr->addr);
                     }));

    delete_map(map);
    return 0;
}