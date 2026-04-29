#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dom_parser.h"
#include "hash_table.h"

// ID ve Class ayıklama
void extract_attributes(char* body, DOMNode* node) {
    char* id = strstr(body, "id=\"");
    if(id) sscanf(id + 4, "%[^\"]", node->id);
    char* cls = strstr(body, "class=\"");
    if(cls) sscanf(cls + 7, "%[^\"]", node->className);
}

DOMNode* parse_html(const char* filename, HashTable* table) {
    FILE* f = fopen(filename, "r");
    if(!f) return NULL;

    Stack* s = create_stack(100);
    DOMNode *root = NULL, *current = NULL;
    char ch, buf[1024], txt[1024];
    int b_idx=0, t_idx=0, in_t=0;

    while((ch = fgetc(f)) != EOF) {
        if(ch == '<') {
            in_t = 1; b_idx = 0;
            if(t_idx > 0 && peek(s)) {
                txt[t_idx] = '\0';
                if(strspn(txt, " \t\n\r") != strlen(txt)) strncat(peek(s)->content, txt, 499);
                t_idx = 0;
            }
        } else if(ch == '>') {
            in_t = 0; buf[b_idx] = '\0';
            if(buf[0] == '/') pop(s);
            else {
                char tag[50]; sscanf(buf, "%s", tag);
                DOMNode* n = create_node(tag);
                extract_attributes(buf, n);
                if(n->id[0] != '\0') insert_to_hash(table, n->id, n);
                if(peek(s)) add_child(peek(s), n); else if(!root) root = n;

                // Tekil etiket değilse stack'e at
                if(strcmp(tag,"img")!=0 && strcmp(tag,"br")!=0 && tag[0]!='!') push(s, n);
            }
        } else if(in_t) buf[b_idx++] = ch;
        else txt[t_idx++] = ch;
    }
    fclose(f); return root;
}