#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "data_structures.h"

typedef struct HashNode {
    char id[50];
    DOMNode* node;
    struct HashNode* next;
} HashNode;

typedef struct HashTable {
    HashNode* buckets[100];
} HashTable;

HashTable* create_hash_table();
void insert_to_hash(HashTable* table, const char* id, DOMNode* node);
DOMNode* lookup_hash(HashTable* table, const char* id);
#endif