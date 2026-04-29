#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// --- N-ARY TREE DÜĞÜM YAPISI ---
typedef struct DOMNode {
    char tag[50];
    char id[50];
    char className[100];
    char content[500];
    struct DOMNode* parent;          // Ebeveyn referansı (İstenen özellik)
    struct DOMNode** children;       // Dinamik çocuk listesi
    int child_count;
    int child_capacity;
} DOMNode;

// --- STACK (YIĞIT) YAPISI ---
typedef struct Stack {
    DOMNode** items;
    int top;
    int capacity;
} Stack;

// --- QUEUE (KUYRUK) YAPISI ---
typedef struct Queue {
    DOMNode** items;
    int front;
    int rear;
    int capacity;
    int count;
} Queue;

// --- Fonksiyon Prototipleri ---
DOMNode* create_node(const char* tag);
void add_child(DOMNode* parent, DOMNode* child);
Stack* create_stack(int capacity);
void push(Stack* stack, DOMNode* node);
DOMNode* pop(Stack* stack);
DOMNode* peek(Stack* stack);
Queue* create_queue(int capacity);
void enqueue(Queue* queue, DOMNode* item);
DOMNode* dequeue(Queue* queue);
int is_queue_empty(Queue* queue);

void print_dom_tree(DOMNode* node, int depth);

#endif