#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "raylib.h"
#include "raymath.h"

#define TOTAL_ITEMS 100
#define MAX_NAME 256

typedef struct item_t{
    char name[MAX_NAME];
    int gold;
    int rarity;
    float kilo;
    int received_order;
} item_t;

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

void insertionSort(item_t *arr, int n, bool descending){
    int i, j;
    item_t key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        if (descending) {
            while (j >= 0 && arr[j].received_order < key.received_order) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
        } else {
            while (j >= 0 && arr[j].received_order > key.received_order) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
        }
        arr[j + 1] = key;
    }
}

item_t* hash_table[TOTAL_ITEMS];
char item_text[256];

void init_hash_table(){
    for (int i =0; i < TOTAL_ITEMS; i++){
        hash_table[i] = NULL;
    }
}

bool insert_hash_table(item_t *t){
    if(t == NULL) return false;
    int index = j_hash(t->name);
    if(hash_table[index] != NULL){
        return false;
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
        DrawText(item_text, 200, 10, 20, DARKGRAY);
        sprintf(item_text, "Item: %s, %d, %.2f, %d, %d", sorted_items[i].name, sorted_items[i].gold, sorted_items[i].kilo, sorted_items[i].rarity,sorted_items[i].received_order);
        DrawText(item_text, 200, y_offset, 20, DARKGRAY);
        y_offset += 30;
    }
}

int main(){

    SetTargetFPS(60);
    InitWindow(800, 800, "RPG - Inventory");

    item_t sorted_items[10];
    int item_count = 0;
    bool descending = false;

    init_hash_table();

    item_t axe = {.name="Axe", .gold=30, .rarity=1, .kilo=40.0F, .received_order=1};
    item_t dagger = {.name="Dagger", .gold=20, .rarity=1, .kilo=10.0F, .received_order=2};
    item_t sword = {.name="Sword", .gold=40, .rarity=1, .kilo=25.0F, .received_order=3};
    item_t silver_sword = {.name="Silver Sword", .gold=50, .rarity=2, .kilo=35.0F, .received_order=4};
    item_t gold_sword = {.name="Gold Sword", .gold=60, .rarity=3, .kilo=45.0F, .received_order=5};
    item_t battle_axe = {.name="Battle Axe", .gold=55, .rarity=2, .kilo=50.0F, .received_order=6};
    item_t bow = {.name="Bow", .gold=45, .rarity=2, .kilo=20.0F, .received_order=7};
    item_t crossbow = {.name="Crossbow", .gold=65, .rarity=3, .kilo=30.0F, .received_order=8};
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
                
        print_sorted_table(sorted_items, item_count);
        
        if (IsKeyPressed(KEY_S)) {
            descending = !descending;
            extract_items(sorted_items, &item_count); // Extract items from hash_table
            insertionSort(sorted_items, item_count, descending); // Sort items
        }
        EndDrawing();
    }
    CloseWindow();
}