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
        // 1. ARAMA KOMUTU
        else if (strcmp(command, "find") == 0) {
            scanf("%s", targetId);
            highlighted = getElementById(table, targetId);
            if (highlighted) {
                sprintf(msg, "Basarili: '%s' bulundu ve isaretlendi.", targetId);
            } else {
                sprintf(msg, "Hata: '%s' ID'li eleman bulunamadi!", targetId);
            }
        }
        // 2. AC/KAPAT KOMUTU
        else if (strcmp(command, "toggle") == 0) {
            scanf("%s", targetId);
            DOMNode* node = getElementById(table, targetId);
            if (node) {
                node->is_expanded = !node->is_expanded;
                sprintf(msg, "Islem: '%s' hiyerarsisi %s.", targetId, node->is_expanded ? "acildi" : "kapatildi");
            } else {
                sprintf(msg, "Hata: Toggle icin ID bulunamadi!");
            }
        }
        // 3. YENI ELEMAN EKLE (Faz 3 - Append)
        else if (strcmp(command, "append") == 0) {
            char newTag[50], newId[50];
            scanf("%s %s %s", targetId, newTag, newId);

            if (getElementById(table, targetId)) {
                appendChildNode(table, targetId, newTag, newId);
                sprintf(msg, "Islem: '%s' icine '%s#%s' eklendi.", targetId, newTag, newId);
            } else {
                sprintf(msg, "Hata: Eklenecek ebeveyn (%s) bulunamadi!", targetId);
            }
        }
        // 4. ELEMAN SIL (Faz 3 - Delete)
        else if (strcmp(command, "delete") == 0) {
            scanf("%s", targetId);
            if (getElementById(table, targetId)) {
                removeElementById(root, table, targetId);
                sprintf(msg, "Islem: '%s' ve tum alt dallari silindi.", targetId);
                highlighted = NULL; // Silindiği için seçili olanı sıfırla
            } else {
                sprintf(msg, "Hata: Silinecek ID (%s) bulunamadi!", targetId);
            }
        }

        // 5. KAYDET: save
        else if (strcmp(command, "save") == 0) {
            save_html_to_file(root, "guncel_index.html");
            sprintf(msg, "Islem Basarili: Agac 'guncel_index.html' olarak kaydedildi!");
        }

        else {
            sprintf(msg, "Bilinmeyen komut! (find, toggle, append, delete, exit)");
        }
    }

    return 0;
}