#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"


// --- DOM Düğümü Oluşturma ---
DOMNode* create_node(const char* tag, const char* id, const char* className, const char* content) {
    DOMNode* newNode = (DOMNode*)malloc(sizeof(DOMNode));
    if (!newNode) return NULL;

    strncpy(newNode->tag, tag, sizeof(newNode->tag) - 1);
    strncpy(newNode->id, id, sizeof(newNode->id) - 1);
    strncpy(newNode->className, className, sizeof(newNode->className) - 1);
    strncpy(newNode->content, content, sizeof(newNode->content) - 1);

    newNode->children = NULL;
    newNode->child_count = 0;
    newNode->parent = NULL;

    // --- FAZ 3 GÜNCELLEMESİ ---
    // Ağaç ilk yüklendiğinde dallar açık görünsün diye 1 yapıyoruz
    newNode->is_expanded = 1;

    return newNode;
}

// --- Kuyruk (Queue) İşlemleri (BFS İçin) ---
Queue* create_queue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->capacity = capacity;
    q->front = q->size = 0;
    q->rear = capacity - 1;
    q->items = (DOMNode**)malloc(q->capacity * sizeof(DOMNode*));
    return q;
}

int is_queue_empty(Queue* q) {
    return (q->size == 0);
}

void enqueue(Queue* q, DOMNode* item) {
    if (q->size == q->capacity) return;
    q->rear = (q->rear + 1) % q->capacity;
    q->items[q->rear] = item;
    q->size = q->size + 1;
}

DOMNode* dequeue(Queue* q) {
    if (is_queue_empty(q)) return NULL;
    DOMNode* item = q->items[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size = q->size - 1;
    return item;
}

// --- Yığıt (Stack) İşlemleri (Parsing İçin) ---
Stack* create_stack(int capacity) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->capacity = capacity;
    s->top = -1;
    s->items = (DOMNode**)malloc(s->capacity * sizeof(DOMNode*));
    return s;
}

void push(Stack* s, DOMNode* item) {
    if (s->top == s->capacity - 1) return;
    s->items[++s->top] = item;
}

DOMNode* pop(Stack* s) {
    if (s->top == -1) return NULL;
    return s->items[s->top--];
}

DOMNode* peek(Stack* s) {
    if (s->top == -1) return NULL;
    return s->items[s->top];
}