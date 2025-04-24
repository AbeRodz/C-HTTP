#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 16

typedef struct {
    char key[256];
    void (*value)(int);
} KeyValue;

struct HashMap {
    KeyValue * data;
    size_t size;
    size_t capacity;
};

// Hash function for the hashmap
static unsigned int hash(const char * str, size_t capacity) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + *str;
        str++;
    }
    return hash % capacity;
}

// Create a new hashmap
HashMap * create() {
    HashMap * map = (HashMap *)malloc(sizeof(HashMap));
    if (!map) {
        return NULL;
    }
    map->size = 0;
    map->capacity = INITIAL_SIZE;
    map->data = (KeyValue *)calloc(map->capacity, sizeof(KeyValue));
    if (!map->data) {
        free(map);
        return NULL;
    }
    return map;
}

// Resize the hashmap when it reaches capacity
static void resize_hashmap(HashMap * map) {
    size_t new_capacity = map->capacity * 2;
    KeyValue * new_data = (KeyValue *)calloc(new_capacity, sizeof(KeyValue));
    if (!new_data) {
        return; // Resize failed, continue with the current size
    }

    for (size_t i = 0; i < map->capacity; i++) {
        if (map->data[i].key[0] != '\0') {
            unsigned int index = hash(map->data[i].key, new_capacity);
            while (new_data[index].key[0] != '\0') {
                index = (index + 1) % new_capacity;
            }
            strcpy(new_data[index].key, map->data[i].key);
            new_data[index].value = map->data[i].value;
        }
    }

    free(map->data);
    map->data = new_data;
    map->capacity = new_capacity;
}

void insert(HashMap * map, const char * key, void (*value)(int)) {
    if (map->size >= map->capacity / 2) {
        resize_hashmap(map);
    }
    unsigned int index = hash(key, map->capacity);
    while (map->data[index].key[0] != '\0') {
        index = (index + 1) % map->capacity;
    }
    strcpy(map->data[index].key, key);
    map->data[index].value = value;
    map->size++;
}
// Retrieve a value from the hashmap
void (*get(HashMap * map, const char * key))(int) {
    unsigned int index = hash(key, map->capacity);
    while (map->data[index].key[0] != '\0') {
        if (strcmp(map->data[index].key, key) == 0) {
            return map->data[index].value;
        }
        index = (index + 1) % map->capacity;
    }
    return NULL;
}

// destroys map and free memory
void destroy(HashMap * map) {
    free(map->data);
    free(map);
}
