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

#endif