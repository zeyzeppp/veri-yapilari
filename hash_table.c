#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

unsigned int hash_func(const char* id) {
    unsigned int hash = 5381;
    while (*id) hash = ((hash << 5) + hash) + *id++;
    return hash % 100;
}

HashTable* create_hash_table() {
    HashTable* t = (HashTable*)malloc(sizeof(HashTable));
    for(int i=0; i<100; i++) t->buckets[i] = NULL;
    return t;
}

void insert_to_hash(HashTable* table, const char* id, DOMNode* node) {
    unsigned int idx = hash_func(id);
    HashNode* n = (HashNode*)malloc(sizeof(HashNode));
    strcpy(n->id, id); n->node = node; n->next = table->buckets[idx];
    table->buckets[idx] = n;
}

DOMNode* lookup_hash(HashTable* table, const char* id) {
    unsigned int idx = hash_func(id);
    HashNode* curr = table->buckets[idx];
    while(curr) {
        if(strcmp(curr->id, id) == 0) return curr->node;
        curr = curr->next;
    }
    return NULL;
}