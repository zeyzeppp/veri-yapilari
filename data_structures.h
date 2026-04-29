#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// Düğüm yapısı
typedef struct DOMNode {
    char tag[50];
    char id[50];
    char className[50];
    char content[256];
    struct DOMNode** children;
    int child_count;
    struct DOMNode* parent;
    int is_expanded;
} DOMNode;

// Kuyruk yapısı (Kırmızı hataların sebebi buradaki eksiklik olabilir)
typedef struct {
    DOMNode** items;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Yığıt yapısı
typedef struct {
    DOMNode** items;
    int top;
    int capacity;
} Stack;

// Fonksiyon İmzaları
DOMNode* create_node(const char* tag, const char* id, const char* className, const char* content);
Queue* create_queue(int capacity);
int is_queue_empty(Queue* q);
void enqueue(Queue* q, DOMNode* item);
DOMNode* dequeue(Queue* q);
Stack* create_stack(int capacity);
void push(Stack* s, DOMNode* item);
DOMNode* pop(Stack* s);
DOMNode* peek(Stack* s);

#endif