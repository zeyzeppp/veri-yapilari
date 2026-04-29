#include <stdio.h>
#include "dom_parser.h"
#include "hash_table.h"
#include "dom_operations.h"

int main() {
    // 1. ADIM: Hazırlık
    HashTable* table = create_hash_table();
    DOMNode* root = parse_html("sources/sample.html", table);

    if (root == NULL) {
        printf("Hata: index.html dosyasi yuklenemedi!\n");
        return 1;
    }

    printf("=== FAZ 2: DOM ANALIZ VE SORGULAMA SISTEMI ===\n");

    // 2. ADIM: Arama Testleri (Zaten yapmıştık)
    printf("\n[1] ID SORGUSU: #container-1");
    DOMNode* target = getElementById(table, "container-1");

    if (target) {
        printf(" -> Bulundu! Etiket: %s\n", target->tag);

        // 3. ADIM: Yeni Eklediğimiz Analiz Fonksiyonlarını Kullanma

        // Derinlik Testi
        int d = getElementDepth(target);
        printf("[2] DERINLIK ANALIZI: Bu eleman % d. seviyede yer aliyor.\n", d);

        // Kardeş (Sibling) Testi
        getSiblings(target);

        // Alt Ağaç (Subtree) Testi
        // Bu div'in içinde toplam kaç eleman var?
        printSubtreeStats(target);
    }

    // 4. ADIM: Genel Ağaç İstatistiği
    printf("\n[3] GENEL AGAC ANALIZI (TUM SAYFA)");
    printSubtreeStats(root);

    // 5. ADIM: Class Bazlı Arama (BFS Kanıtı)
    getElementsByClassName(root, "card");

    printf("\n=== Analiz Tamamlandi ===\n");

    return 0;
}