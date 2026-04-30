#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dom_operations.h"

// --- ID ILE ARAMA (Hash Table - O(1)) ---
DOMNode* getElementById(HashTable* table, const char* id) {
    return lookup_hash(table, id);
}

// --- CLASS ILE ARAMA (BFS - Kuyruk Kullanımı) ---
// startNode parametresi sayesinde hem tüm ağaçta hem de alt ağaçta arama yapabilir!
void getElementsByClassName(DOMNode* startNode, const char* className) {
    if (startNode == NULL) return;

    Queue* q = create_queue(200);
    enqueue(q, startNode);

    printf("\n>>> '.%s' Class'i Icin Arama (Baslangic: %s#%s) <<<\n",
           className, startNode->tag, startNode->id);

    int found = 0;
    while (!is_queue_empty(q)) {
        DOMNode* current = dequeue(q);

        if (strcmp(current->className, className) == 0) {
            printf("- [%s] ID: %s, Derinlik: %d\n",
                   current->tag, current->id, getElementDepth(current));
            found = 1;
        }

        for (int i = 0; i < current->child_count; i++) {
            enqueue(q, current->children[i]);
        }
    }
    if (!found) printf("Sonuc bulunamadi.\n");

    // BELLEK YONETIMI: Kuyruk isini bitirdiğinde temizlenmeli
    free(q->items);
    free(q);
}

// --- TAG ILE ARAMA (DFS - Recursive) ---
void getElementsByTagName(DOMNode* root, const char* tagName) {
    if (root == NULL) return;

    if (strcmp(root->tag, tagName) == 0) {
        printf("- [%s] ID: %s, Class: %s\n",
               root->tag, root->id, root->className);
    }

    for (int i = 0; i < root->child_count; i++) {
        getElementsByTagName(root->children[i], tagName);
    }
}

// --- DERINLIK HESAPLAMA ---
int getElementDepth(DOMNode* node) {
    int depth = 0;
    DOMNode* curr = node;
    while (curr != NULL && curr->parent != NULL) {
        depth++;
        curr = curr->parent;
    }
    return depth;
}

// --- KARDES DUGUMLERI BULMA ---
void getSiblings(DOMNode* node) {
    if (node == NULL || node->parent == NULL) {
        printf("Dugumun kardesi yok.\n");
        return;
    }

    DOMNode* p = node->parent;
    printf("\n'%s#%s' Dugumunun Kardesleri:\n", node->tag, node->id);

    int count = 0;
    for (int i = 0; i < p->child_count; i++) {
        if (p->children[i] != node) {
            printf("  -> [%s] ID: %s\n", p->children[i]->tag, p->children[i]->id);
            count++;
        }
    }
    if (count == 0) printf("  (Kardes bulunamadi)\n");
}

// --- ALT AGAC ANALIZI (Recursive Count) ---
int countNodesInSubtree(DOMNode* node) {
    if (node == NULL) return 0;
    int total = 1;
    for (int i = 0; i < node->child_count; i++) {
        total += countNodesInSubtree(node->children[i]);
    }
    return total;
}

// --- ISTATISTIK YAZDIRMA ---
void printSubtreeStats(DOMNode* node) {
    if (node == NULL) {
        printf("Analiz edilecek dugum bulunamadi.\n");
        return;
    }
    printf("\n======= ALT AGAC ANALIZI: %s#%s =======\n", node->tag, node->id);
    printf("Toplam Dugum Sayisi  : %d\n", countNodesInSubtree(node));
    printf("Bulundugu Derinlik   : %d\n", getElementDepth(node));
    printf("Dogrudan Cocuk Sayisi: %d\n", node->child_count);
    printf("================================================\n");
}

// --- BELLEK TEMIZLEME (FAZ 2 FINAL DOKUNUSU) ---
void free_dom_tree(DOMNode* node) {
    if (node == NULL) return;
    for (int i = 0; i < node->child_count; i++) {
        free_dom_tree(node->children[i]);
    }
    free(node->children);
    free(node);
}

void renderDashboard(DOMNode* root, DOMNode* highlighted, const char* message) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    printf("==========================================================================\n");
    printf("   DOM IDE - FAZ 3 | MESAJ: %s\n", message);
    printf("==========================================================================\n");
    printf("%-35s | %-35s\n", "[ HTML KAYNAK KODU ]", "[ CANLI DOM AGACI ]");
    printf("------------------------------------+-------------------------------------\n");

    // Not: Buraya ileride HTML metnini satır satır basacak bir mantık ekleyeceğiz.
    // Şimdilik sadece ağaç yapısını sağda gösterelim.
    print_collapsible_tree(root, 0, highlighted);

    printf("------------------------------------+-------------------------------------\n");
    printf(" KOMUTLAR: toggle <id> | find <id> | append <parent_id> <tag> | delete <id> | save | exit\n");
    printf("--------------------------------------------------------------------------\n");
    printf(">> ");
}

// --- COLLAPSIBLE TREE PRINT (Faz 3 Görselleştirme) ---
void print_collapsible_tree(DOMNode* node, int depth, DOMNode* highlighted) {
    if (node == NULL) return;

    // Girintileme
    for (int i = 0; i < depth; i++) printf("  ");

    // Vurgulama (Eğer aranan düğümse yeşil yap)
    if (node == highlighted) printf("\033[1;32m");

    // Açılır-kapanır ikonları ve etiket bilgisi
    char* icon = (node->child_count > 0) ? (node->is_expanded ? "[-] " : "[+] ") : "    ";
    printf("%s%s", icon, node->tag);

    if (strlen(node->id) > 0) printf("#%s", node->id);
    if (node == highlighted) printf(" [SELECTED]\033[0m");
    printf("\n");

    // Eğer düğüm açıksa (is_expanded == 1) çocuklarını yazdır
    if (node->is_expanded) {
        for (int i = 0; i < node->child_count; i++) {
            print_collapsible_tree(node->children[i], depth + 1, highlighted);
        }
    }
}

// --- YENI DUGUM EKLEME (Faz 3 - Append) ---
void appendChildNode(HashTable* table, const char* parentId, const char* tag, const char* newId) {
    DOMNode* parent = getElementById(table, parentId);
    if (!parent) return;

    // Yeni düğümü oluştur
    DOMNode* newNode = create_node(tag, newId, "", "Yeni Icerik");
    newNode->parent = parent;

    // Ebeveynin çocuk dizisini genişlet ve ekle
    parent->children = realloc(parent->children, sizeof(DOMNode*) * (parent->child_count + 1));
    parent->children[parent->child_count++] = newNode;

    // Hash tabloya kaydet
    insert_to_hash(table, newId, newNode);
}

// Yardımcı Fonksiyon: Düğümü, çocuklarını ve Hash kayıtlarını temizler
void free_node_and_remove_from_hash(DOMNode* node, HashTable* table) {
    if (!node) return;
    for (int i = 0; i < node->child_count; i++) {
        free_node_and_remove_from_hash(node->children[i], table);
    }
    if (strlen(node->id) > 0) {
        delete_from_hash(table, node->id);
    }
    free(node->children);
    free(node);
}

// --- DUGUM SILME (Faz 3 - Delete) ---
void removeElementById(DOMNode* root, HashTable* table, const char* id) {
    DOMNode* target = getElementById(table, id);
    if (!target) return;
    if (target == root) return; // Güvenlik: Kök (html) silinemez!

    DOMNode* parent = target->parent;

    // 1. Ebeveynin listesinden çıkar (Diziyi kaydır)
    int index = -1;
    for (int i = 0; i < parent->child_count; i++) {
        if (parent->children[i] == target) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        for (int i = index; i < parent->child_count - 1; i++) {
            parent->children[i] = parent->children[i + 1];
        }
        parent->child_count--;
    }

    // 2. Belleği ve Hash kayıtlarını temizle
    free_node_and_remove_from_hash(target, table);
}

// --- HTML OLARAK KAYDETME (Faz 3 - Save) ---
void save_node_to_file(DOMNode* node, FILE* file, int depth) {
    if (!node) return;

    // Girintileme (Okunabilirlik için boşluklar)
    for (int i = 0; i < depth; i++) fprintf(file, "    ");

    // Etiketi aç ve özellikleri yazdır
    fprintf(file, "<%s", node->tag);
    if (strlen(node->id) > 0) fprintf(file, " id=\"%s\"", node->id);
    if (strlen(node->className) > 0) fprintf(file, " class=\"%s\"", node->className);
    fprintf(file, ">\n");

    // İçerik varsa yazdır
    if (strlen(node->content) > 0) {
        for (int i = 0; i < depth + 1; i++) fprintf(file, "    ");
        fprintf(file, "%s\n", node->content);
    }

    // Çocuk düğümleri özyineli (recursive) olarak yazdır
    for (int i = 0; i < node->child_count; i++) {
        save_node_to_file(node->children[i], file, depth + 1);
    }

    // Etiketi kapat
    for (int i = 0; i < depth; i++) fprintf(file, "    ");
    fprintf(file, "</%s>\n", node->tag);
}

void save_html_to_file(DOMNode* root, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;

    fprintf(file, "<!DOCTYPE html>\n");
    save_node_to_file(root, file, 0);
    fclose(file);
}