// Developer: Zeynep Alperen
// Module: HTML Parser - Stack Based Tokenizer


#ifndef DOM_PARSER_H
#define DOM_PARSER_H

#include "data_structures.h"
#include "hash_table.h" // Hash tablosu desteği için şart

// --- Fonksiyon Prototipleri ---

/**
 * HTML dosyasını karakter karakter okur, Stack kullanarak DOM ağacını kurar
 * ve aynı anda ID'leri Hash Tablosuna kaydeder.
 */
DOMNode* parse_html(const char* filename, HashTable* table);

/**
 * Etiket gövdesinden (Örn: <div id="test">) id ve class özniteliklerini
 * cımbızla çeker ve ilgili düğüme (node) yazar.
 */
void extract_attributes(char* tag_body, DOMNode* node);

#endif