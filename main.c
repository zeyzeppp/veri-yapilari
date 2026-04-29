#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dom_parser.h"
#include "hash_table.h"
#include "dom_operations.h"

int main() {
    HashTable* table = create_hash_table();
    DOMNode* root = parse_html("sources/sample.html", table);

    if (root == NULL) {
        printf("Hata: html dosyasi yuklenemedi!\n");
        return 1;
    }

    DOMNode* highlighted = NULL;
    char command[50];
    char targetId[50];
    char msg[100] = "Sistem Hazir. Komut bekliyor...";

    while (1) {
        // Ekranı her seferinde tazeleyen Dashboard
        renderDashboard(root, highlighted, msg);

        // Komut girişi
        printf(">> ");
        if (scanf("%s", command) != 1) break;

        if (strcmp(command, "exit") == 0) {
            printf("Programdan cikiliyor...\n");
            break;
        }

        // 1. ARAMA KOMUTU: find <id>
        if (strcmp(command, "find") == 0) {
            scanf("%s", targetId);
            highlighted = getElementById(table, targetId);
            if (highlighted) {
                sprintf(msg, "Basarili: '%s' bulundu ve isaretlendi.", targetId);
            } else {
                sprintf(msg, "Hata: '%s' ID'li eleman bulunamadi!", targetId);
            }
        }
        // 2. AC/KAPAT KOMUTU: toggle <id>
        else if (strcmp(command, "toggle") == 0) {
            scanf("%s", targetId);
            DOMNode* node = getElementById(table, targetId);
            if (node) {
                node->is_expanded = !node->is_expanded; // Durumu tersine cevir
                sprintf(msg, "Islem: '%s' hiyerarsisi %s.", targetId, node->is_expanded ? "acildi" : "kapatildi");
            } else {
                sprintf(msg, "Hata: Toggle icin ID bulunamadi!");
            }
        }
        // 3. YENI ELEMAN: append <parent_id> <tag> (Gelistirilecek)
        else if (strcmp(command, "append") == 0) {
            sprintf(msg, "Append ozelligi bir sonraki adimda aktif olacak.");
        }
        else {
            sprintf(msg, "Bilinmeyen komut! (find, toggle, exit)");
        }
    }

    return 0;
}