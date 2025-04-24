#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct HashMap HashMap;

HashMap * create();
void insert(HashMap * map, const char * key, void (*value)(int));
void (*get(HashMap * map, const char * key))(int);
void destroy(HashMap * map);
#endif
