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

unsigned int hash(char *name){
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++){
        hash_value += name[i];
        hash_value = (hash_value * name[i] % 31);
    }
    return hash_value;
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

void insertionSort(item_t *arr, int n, bool descending)
{
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


void print_table(){
    for (int i =0; i < TOTAL_ITEMS; i++){
        if(hash_table[i] == NULL){
            sprintf(item_text, "Item: ---");
            DrawText(item_text, 200, 50 + (i * 20), 20, DARKGRAY);
        }
        else{
            // printf("\t%i\t%s\n", i, hash_table[i]->name);
            sprintf(item_text, "Item: %s", hash_table[i]->name);
            DrawText(item_text, 200, 50 + (i * 20), 20, DARKGRAY);
        }
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

int main(){

    SetTargetFPS(60);
    InitWindow(800, 600, "RPG - Inventory");

    bool descending = true;

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
    

    // item_t item[TOTAL_ITEMS] = {
    //     {"Sword", 10, 1, 25.0f, 3},
    //     {"Sword", 50, 5, 50.0f, 1}, 
    //     {"Armor", 150, 5, 50.0f, 2}, 
    //     {"Stick", 25, 5, 50.0f, 4},
    //     {"Apple", 5, 5, 50.0f, 10},
    //     {"Bread", 10, 5, 50.0f, 9},
    //     {"Silver Sword", 250, 5, 50.0f, 8},
    //     {"Black Sword", 500, 5, 50.0f, 5,},
    //     {"Gold Sword", 1000, 5, 50.0f, 6},
    //     {"Platinum Sword", 5000, 5, 50.0f, 7}
    // };

  
    

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        char item_text[256];

        print_table();

        // Format the debug information into a string
        // for(int i = 0; i < TOTAL_ITEMS; i++){
        //     sprintf(item_text, "Name - Gold - Rarity - Kilo - Newest");
        //     DrawText(item_text, 200, 50, 20, WHITE);
        //     sprintf(item_text, "Press S to sort Newest and again for Oldest");
        //     DrawText(item_text, 200, 500, 20, DARKGRAY);
        //     sprintf(item_text, "Item: %s, %.2d, %d, %.2f, %d", item[i].name, item[i].gold, item[i].rarity, item[i].kilo, item[i].received_order);
        //     DrawText(item_text, 200, 100 + (i * 30), 20, DARKGRAY);
        // }

        // if (IsKeyPressed(KEY_S)) {
        //     descending = !descending;
        //     insertionSort(item, 10, descending);
        // }
        
        EndDrawing();
    }
    CloseWindow();
}