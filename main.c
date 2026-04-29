#include <stdio.h>
#include "dom_parser.h"
#include "hash_table.h"


int main() {
    HashTable* table = create_hash_table();
    DOMNode* root = parse_html("sources/sample.html", table);

    if (root != NULL) {
        printf("\n--- BELLEKTEKI DOM AGACI YAPISI ---\n");
        print_dom_tree(root, 0); // Ağacı 0. derinlikten başlayarak yazdır
        printf("----------------------------------\n");
        printf("DOM Agaci ve Hash Tablosu Basariyla Kuruldu!\n");
    }
    return 0;
}