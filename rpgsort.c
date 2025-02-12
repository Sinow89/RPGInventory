#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "raymath.h"

#define TOTAL_ITEMS 10
#define MAX_NAME 255

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
    }
    return hash_value;
}

void insertionSort(item_t arr[], int n)
{
    int i, j;
    item_t key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j].received_order > key.received_order) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void insertionSortDec(item_t arr[], int n)
{
    int i, j;
    item_t key;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        // Change comparison to flip the order (descending)
        while (j >= 0 && arr[j].received_order < key.received_order) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main(){

    SetTargetFPS(60);
    InitWindow(800, 600, "RPG - Inventory");

    bool key_pressed = true;

    item_t item[TOTAL_ITEMS] = {
        {"Dagger", 10, 1, 25.0f, 3},
        {"Sword", 50, 5, 50.0f, 1}, 
        {"Armor", 150, 5, 50.0f, 2}, 
        {"Stick", 25, 5, 50.0f, 4},
        {"Apple", 5, 5, 50.0f, 10},
        {"Bread", 10, 5, 50.0f, 9},
        {"Silver Sword", 250, 5, 50.0f, 8},
        {"Black Sword", 500, 5, 50.0f, 5,},
        {"Gold Sword", 1000, 5, 50.0f, 6},
        {"Platinum Sword", 5000, 5, 50.0f, 7}
    };

    printf("Dagger=> %u\n", hash(item[0].name));
    printf("Sword=> %u\n", hash(item[1].name));
    printf("Armor=> %u\n", hash(item[2].name));
    printf("Stick=> %u\n", hash(item[3].name));
    printf("Apple=> %u\n", hash(item[4].name));
    printf("Bread=> %u\n", hash(item[5].name));
    printf("Silver Sword=> %u\n", hash(item[6].name));
    printf("Black Sword=> %u\n", hash(item[7].name));
    printf("Gold Sword=> %u\n", hash(item[8].name));
    
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        char item_text[256];

        // Format the debug information into a string
        for(int i = 0; i < TOTAL_ITEMS; i++){
            sprintf(item_text, "Name - Gold - Rarity - Kilo - Newest");
            DrawText(item_text, 200, 50, 20, WHITE);
            sprintf(item_text, "Press S to sort Newest and again for Oldest");
            DrawText(item_text, 200, 500, 20, DARKGRAY);
            sprintf(item_text, "Item: %s, %.2d, %d, %.2f, %d", item[i].name, item[i].gold, item[i].rarity, item[i].kilo, item[i].received_order);
            DrawText(item_text, 200, 100 + (i * 30), 20, DARKGRAY);
        }

        if (IsKeyPressed(KEY_S)) {
            if (key_pressed) {
                insertionSort(item, 10);
            } else {
                insertionSortDec(item, 10);
            }
            key_pressed = !key_pressed;
        }
        
        EndDrawing();
    }
    CloseWindow();
}