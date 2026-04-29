#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"

DOMNode* create_node(const char* tag) {
    DOMNode* node = (DOMNode*)malloc(sizeof(DOMNode));
    strcpy(node->tag, tag);
    node->id[0] = '\0';
    node->className[0] = '\0';
    node->content[0] = '\0';
    node->parent = NULL;
    node->child_count = 0;
    node->child_capacity = 2;
    node->children = (DOMNode**)malloc(sizeof(DOMNode*) * node->child_capacity);
    return node;
}

void add_child(DOMNode* parent, DOMNode* child) {
    if (parent->child_count == parent->child_capacity) {
        parent->child_capacity *= 2;
        parent->children = (DOMNode**)realloc(parent->children, sizeof(DOMNode*) * parent->child_capacity);
    }
    parent->children[parent->child_count++] = child;
    child->parent = parent; // Parent bağını burada kuruyoruz
}

// Stack Fonksiyonları
Stack* create_stack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->items = (DOMNode**)malloc(sizeof(DOMNode*) * capacity);
    return stack;
}
void push(Stack* stack, DOMNode* node) { if (stack->top < stack->capacity - 1) stack->items[++stack->top] = node; }
DOMNode* pop(Stack* stack) { return (stack->top >= 0) ? stack->items[stack->top--] : NULL; }
DOMNode* peek(Stack* stack) { return (stack->top >= 0) ? stack->items[stack->top] : NULL; }

// Queue Fonksiyonları (BFS İçin)
Queue* create_queue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->capacity = capacity;
    q->front = 0; q->rear = -1; q->count = 0;
    q->items = (DOMNode**)malloc(sizeof(DOMNode*) * capacity);
    return q;
}
void enqueue(Queue* q, DOMNode* item) {
    if (q->count == q->capacity) return;
    q->rear = (q->rear + 1) % q->capacity;
    q->items[q->rear] = item;
    q->count++;
}
DOMNode* dequeue(Queue* q) {
    if (q->count == 0) return NULL;
    DOMNode* item = q->items[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->count--;
    return item;
}
int is_queue_empty(Queue* q) { return q->count == 0; }

void print_dom_tree(DOMNode* node, int depth) {
    if (node == NULL) return;

    // Derinliğe göre girinti (indentation) oluştur
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    // Düğüm bilgilerini yazdır
    printf("[%s]", node->tag);
    if (node->id[0] != '\0') printf(" #%s", node->id);
    if (node->className[0] != '\0') printf(" .%s", node->className);
    if (node->content[0] != '\0') printf(" (Icerik: %s)", node->content);
    printf("\n");

    // Çocuklarını özyinelemeli olarak yazdır
    for (int i = 0; i < node->child_count; i++) {
        print_dom_tree(node->children[i], depth + 1);
    }
}