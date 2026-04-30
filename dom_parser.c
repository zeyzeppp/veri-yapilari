#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dom_parser.h"
#include "dom_operations.h"

// Yardımcı fonksiyon: Parametre uyuşmazlığını çözmek için
void add_child_internal(DOMNode* parent, DOMNode* child) {
    if (!parent || !child) return;
    parent->children = realloc(parent->children, sizeof(DOMNode*) * (parent->child_count + 1));
    parent->children[parent->child_count++] = child;
    child->parent = parent;
}

DOMNode* parse_html(const char* filename, HashTable* table) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    char line[256];
    DOMNode* root = NULL;
    Stack* s = create_stack(100);

    while (fgets(line, sizeof(line), file)) {
        char tag[50], id[50] = "", className[50] = "", content[100] = "";

        // Basit bir parser mantığı: <tag id=".." class="..">content
        if (line[0] == '<' && line[1] != '/') {
            // Not: Gerçek bir projede burası daha detaylı regex/string split ile parse edilir.
            // Şimdilik hata almamak için boş parametrelerle create_node çağırıyoruz.
            sscanf(line, "<%[^ >] id=\"%[^\"]\" class=\"%[^\"]\">%[^\n]", tag, id, className, content);

            DOMNode* n = create_node(tag, id, className, content);

            if (peek(s)) {
                add_child_internal(peek(s), n);
            } else if (!root) {
                root = n;
            }

            push(s, n);

            // ID varsa hash tabloya ekle
            if (strlen(n->id) > 0) {
                insert_to_hash(table, n->id, n);
            }
        }
        else if (line[0] == '<' && line[1] == '/') {
            pop(s);
        }
    }

    fclose(file);
    return root;
}