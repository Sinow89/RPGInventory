#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "raylib.h"
#include "raymath.h"

#define TOTAL_ITEMS 10
#define MAX_NAME 256

typedef struct item_t{
    char name[MAX_NAME];
    int gold;
    int rarity;
    float kilo;
    int received_order;
} item_t;

typedef enum {
    SORT_BY_ORDER,
    SORT_BY_GOLD,
    SORT_BY_RARITY,
    SORT_BY_WEIGHT
} SortCriteria;

typedef int (*CompareFunc)(item_t, item_t, bool);

int compareReceivedOrder(item_t a, item_t b, bool descending) {
    return descending ? (a.received_order < b.received_order) : (a.received_order > b.received_order);
}

int compareGold(item_t a, item_t b, bool descending) {
    return descending ? (a.gold < b.gold) : (a.gold > b.gold);
}

int compareKilo(item_t a, item_t b, bool descending) {
    return descending ? (a.kilo < b.kilo) : (a.kilo > b.kilo);
}

int compareRarity(item_t a, item_t b, bool descending) {
    return descending ? (a.rarity < b.rarity) : (a.rarity > b.rarity);
}

uint32_t j_hash(char* name) {
    size_t i = 0;
    int length = strnlen(name, MAX_NAME);
    uint32_t hash = 0;
    while (i != length) {
      hash += name[i++];
      hash += hash << 10;
      hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash % TOTAL_ITEMS;
  }

void insertionSort(item_t *arr, int n, bool descending, CompareFunc cmp){
    int i, j;
    item_t key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && cmp(arr[j], key, descending)) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void sortItems(item_t *arr, int n, bool descending, SortCriteria criteria) {
    switch (criteria) {
        case SORT_BY_GOLD: 
            insertionSort(arr, n, descending, compareGold); 
            break;
        case SORT_BY_RARITY: 
            insertionSort(arr, n, descending, compareRarity); 
            break;
        case SORT_BY_WEIGHT: 
            insertionSort(arr, n, descending, compareKilo); 
            break;
        default: 
            insertionSort(arr, n, descending, compareReceivedOrder); 
            break;
    }
}

item_t* hash_table[TOTAL_ITEMS];
char item_text[256];

void init_hash_table(){
    for (int i =0; i < TOTAL_ITEMS; i++){
        hash_table[i] = NULL;
    }
}

bool insert_hash_table(item_t *t) {
    if(t == NULL) return false;
    int index = j_hash(t->name);
    int original_index = index;
    
    while (hash_table[index] != NULL) {
        index = (index + 1) % TOTAL_ITEMS; 
        
        if (index == original_index) {
            return false;
        }
    }
    hash_table[index] = t;
    return true;
}

void extract_items(item_t *arr, int *count) {
    *count = 0; // Reset count

    for (int i = 0; i < TOTAL_ITEMS; i++) {
        if (hash_table[i] != NULL) {
            arr[*count] = *hash_table[i]; // Copy the item
            (*count)++;
        }
    }
}

void print_sorted_table(item_t *sorted_items, int count) {
    int y_offset = 50;
    for (int i = 0; i < count; i++) {
        sprintf(item_text, "Name - Gold - Kilo - Rarity - Newest");
        DrawText(item_text, 450, 10, 20, DARKGRAY);
        sprintf(item_text, "Item: %-15s %5d %8.2f %5d %5d", sorted_items[i].name, sorted_items[i].gold, sorted_items[i].kilo, sorted_items[i].rarity,sorted_items[i].received_order);
        DrawText(item_text, 400, y_offset, 20, DARKGRAY);
        y_offset += 30;
    }
}

void print_table(){
    sprintf(item_text, "Hash Table");
    DrawText(item_text, 50, 10, 20, WHITE);
    for (int i =0; i < TOTAL_ITEMS; i++){
        if(hash_table[i] == NULL){
            sprintf(item_text, "Item: ---");
            DrawText(item_text, 50, 50 + (i * 20), 20, DARKGRAY);
        }
        else{
            sprintf(item_text, "Item: %s, %.2d, %d, %.2f, %d", hash_table[i]->name, hash_table[i]->gold, hash_table[i]->rarity, hash_table[i]->kilo, hash_table[i]->received_order);
        }
        DrawText(item_text, 50, 50 + (i * 20), 20, DARKGRAY);
    }
}

int main(){

    SetTargetFPS(60);
    InitWindow(1200, 800, "RPG - Inventory");

    item_t sorted_items[TOTAL_ITEMS];
    int item_count = 0;
    bool descending = false;

    init_hash_table();

    item_t axe = {.name="Axe", .gold=30, .rarity=1, .kilo=40.0F, .received_order=1};
    item_t dagger = {.name="Dagger", .gold=20, .rarity=1, .kilo=10.0F, .received_order=2};
    item_t sword = {.name="Sword", .gold=40, .rarity=1, .kilo=25.0F, .received_order=3};
    item_t silver_sword = {.name="Silver Sword", .gold=50, .rarity=2, .kilo=35.0F, .received_order=4};
    item_t gold_sword = {.name="Gold Sword", .gold=60, .rarity=5, .kilo=45.0F, .received_order=5};
    item_t battle_axe = {.name="Battle Axe", .gold=55, .rarity=2, .kilo=50.0F, .received_order=6};
    item_t bow = {.name="Bow", .gold=45, .rarity=2, .kilo=20.0F, .received_order=7};
    item_t crossbow = {.name="Crossbow", .gold=65, .rarity=4, .kilo=30.0F, .received_order=8};
    item_t spear = {.name="Spear", .gold=50, .rarity=2, .kilo=35.0F, .received_order=9};
    item_t halberd = {.name="Halberd", .gold=70, .rarity=3, .kilo=60.0F, .received_order=10};

    insert_hash_table(&sword);
    insert_hash_table(&silver_sword);
    insert_hash_table(&gold_sword);
    insert_hash_table(&axe);
    insert_hash_table(&battle_axe);
    insert_hash_table(&dagger);
    insert_hash_table(&bow);
    insert_hash_table(&crossbow);
    insert_hash_table(&spear);
    insert_hash_table(&halberd);
    
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
           
        print_table();

        print_sorted_table(sorted_items, item_count);

        if (IsKeyPressed(KEY_A)) {
            descending = !descending;
            extract_items(sorted_items, &item_count);
            sortItems(sorted_items, item_count, descending, SORT_BY_GOLD);
        }
        if (IsKeyPressed(KEY_S)) {
            descending = !descending;
            extract_items(sorted_items, &item_count);
            sortItems(sorted_items, item_count, descending, SORT_BY_WEIGHT);
        }
        if (IsKeyPressed(KEY_D)) {
            descending = !descending;
            extract_items(sorted_items, &item_count);
            sortItems(sorted_items, item_count, descending, SORT_BY_RARITY);
        }
        if (IsKeyPressed(KEY_F)) {
            descending = !descending;
            extract_items(sorted_items, &item_count);
            sortItems(sorted_items, item_count, descending, SORT_BY_ORDER);
        }

        sprintf(item_text, "Press A to sort ascen and descen gold");
        DrawText(item_text, 200, 450, 20, WHITE);
        sprintf(item_text, "Press S to sort ascen and descen kilo");
        DrawText(item_text, 200, 500, 20, WHITE);
        sprintf(item_text, "Press D to sort ascen and descen rarity");
        DrawText(item_text, 200, 550, 20, WHITE);
        sprintf(item_text, "Press f to sort ascen and descen newest");
        DrawText(item_text, 200, 600, 20, WHITE);

        EndDrawing();
    }
    CloseWindow();
}