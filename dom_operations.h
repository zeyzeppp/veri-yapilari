#ifndef DOM_OPERATIONS_H
#define DOM_OPERATIONS_H

#include "data_structures.h"
#include "hash_table.h"

// --- 1. Arama Fonksiyonları ---
// ID ile Hızlı Arama (Hash Table - O(1))
DOMNode* getElementById(HashTable* table, const char* id);

// Class İsmi ile Arama (BFS - Kuyruk Kullanımı - O(n))
void getElementsByClassName(DOMNode* root, const char* className);

// Etiket İsmi ile Arama (DFS - Recursive - O(n))
void getElementsByTagName(DOMNode* root, const char* tagName);

// --- 2. Analiz ve Navigasyon Fonksiyonları ---
// Bir düğümün ağaçtaki derinlik seviyesini döner (Root = 0)
int getElementDepth(DOMNode* node);

// Bir düğümün kardeşlerini (aynı parent'a sahip diğer çocuklar) yazdırır
void getSiblings(DOMNode* node);

// Belirli bir düğümden başlayan alt ağaçtaki (subtree) toplam düğüm sayısını hesaplar
int countNodesInSubtree(DOMNode* node);

// Alt ağaç hakkında istatistiksel özet yazdırır
void printSubtreeStats(DOMNode* node);

// --- Faz 3: Manipülasyon Fonksiyonları ---
// 1. Yeni düğüm oluşturup bir ebeveyne bağlama
void appendChild(DOMNode* parent, DOMNode* child, HashTable* table);

// 2. ID kullanarak düğüm silme (ve belleği temizleme)
void removeElementById(DOMNode* root, HashTable* table, const char* id);

// 3. Bellekteki ağacı HTML dosyası olarak diske yazma
void saveTreeToHTML(DOMNode* root, const char* filename);

// 4. İçerik güncelleme
void updateElementContent(DOMNode* node, const char* newContent);
void renderDashboard(DOMNode* root, DOMNode* highlighted, const char* message);
void print_collapsible_tree(DOMNode* node, int depth, DOMNode* highlighted);

// Eğer fonksiyonun ismi dom_operations.c içinde 'print_collapsible_tree' ise:
void print_collapsible_tree(DOMNode* node, int depth, DOMNode* highlighted);
void renderDashboard(DOMNode* root, DOMNode* highlighted, const char* message);

void appendChildNode(HashTable* table, const char* parentId, const char* tag, const char* newId);
void removeElementById(DOMNode* root, HashTable* table, const char* id);

void save_html_to_file(DOMNode* root, const char* filename);

#endif