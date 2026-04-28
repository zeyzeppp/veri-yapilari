#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 1. ADIM: VERI YAPILARI (FAZ 1 GEREKSINIMLERI)
// DOM Düğümü: N-ary Tree yapısı [cite: 90, 91]
typedef struct DOMNode {
    char tag_name[50];          // Etiket adı [cite: 93]
    char id[50];                // id özelliği [cite: 94, 102]
    char class_name[50];        // class özelliği [cite: 94]
    char content[256];          // Etiket içindeki metin
    struct DOMNode* parent;     // Ebeveyn referansı [cite: 95]
    struct DOMNode** children;  // Dinamik çocuk listesi [cite: 96]
    int child_count;
} DOMNode;

// Ayrıştırma için Yığıt (Stack) yapısı [cite: 98, 101]
typedef struct Stack {
    DOMNode** items;
    int top;
    int capacity;
} Stack;

// 2. ADIM: YARDIMCI FONKSIYONLAR
// Yeni düğüm oluşturma (Malloc ile hafıza yönetimi)
DOMNode* create_node(const char* tag) {
    DOMNode* node = (DOMNode*)malloc(sizeof(DOMNode));
    strcpy(node->tag_name, tag);
    strcpy(node->id, "");
    strcpy(node->class_name, "");
    strcpy(node->content, "");
    node->parent = NULL;
    node->children = NULL;
    node->child_count = 0;
    return node;
}

// Çocuğu ebeveyne bağlama (Dinamik dizi büyütme) [cite: 96]
void add_child(DOMNode* parent, DOMNode* child) {
    parent->child_count++;
    parent->children = (DOMNode**)realloc(parent->children, sizeof(DOMNode*) * parent->child_count);
    parent->children[parent->child_count - 1] = child;
    child->parent = parent;
}

// Stack işlemleri [cite: 99, 100]
Stack* create_stack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->items = (DOMNode**)malloc(sizeof(DOMNode*) * capacity);
    return stack;
}

void push(Stack* stack, DOMNode* item) {
    stack->items[++stack->top] = item;
}

DOMNode* pop(Stack* stack) {
    if (stack->top == -1) return NULL;
    return stack->items[stack->top--];
}

DOMNode* peek(Stack* stack) {
    if (stack->top == -1) return NULL;
    return stack->items[stack->top];
}

// 3. ADIM: OZELLIK AYIKLAMA (ID & CLASS) [cite: 102, 122]
void extract_attributes(char* tag_content, DOMNode* node) {
    char* id_ptr = strstr(tag_content, "id=\"");
    if (id_ptr) {
        sscanf(id_ptr + 4, "%[^\"]", node->id);
    }

    char* class_ptr = strstr(tag_content, "class=\"");
    if (class_ptr) {
        sscanf(class_ptr + 7, "%[^\"]", node->class_name);
    }
}

// 4. ADIM: ANA PARSER MANTIGI [cite: 81, 120, 122]
void parse_html(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("HATA: Dosya acilamadi! Lutfen 'sources/sample.html' yolunu kontrol edin.\n");
        return;
    }

    Stack* stack = create_stack(100);
    char line[512];
    DOMNode* root = NULL;

    printf("HTML Ayristirma Islemi Basliyor...\n----------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        char* ptr = strstr(line, "<");
        while (ptr) {
            if (*(ptr + 1) == '/') { // Kapanis etiketi: </div> [cite: 100]
                pop(stack);
            }
            else if (isalpha(*(ptr + 1))) { // Acilis etiketi: <div ...> [cite: 99]
                char full_tag[128];
                sscanf(ptr + 1, "%[^>]", full_tag); // '>' gorene kadar tum etiketi al

                char tag_name[50];
                sscanf(full_tag, "%s", tag_name); // Sadece ilk kelimeyi (etiket adi) al

                DOMNode* newNode = create_node(tag_name);
                extract_attributes(full_tag, newNode); // id ve class'ı ayıkla

                if (peek(stack) != NULL) {
                    add_child(peek(stack), newNode); // Hiyerarsiyi kur
                } else if (root == NULL) {
                    root = newNode; // Kok dugumu belirle
                }

                push(stack, newNode);
                printf("[Dugum Eklendi] Tag: %s | ID: %s | Class: %s\n",
                       newNode->tag_name, newNode->id, newNode->class_name);
            }
            ptr = strstr(ptr + 1, "<"); // Ayni satirdaki diger etiketlere bak
        }
    }

    fclose(file);
    printf("----------------------------------\nDOM Agaci Basariyla Kuruldu.\n");
}

int main() {
    // Calistirmadan once 'sources' klasoru altinda 'sample.html' oldugundan emin ol
    parse_html("sources/sample.html");
    return 0;
}