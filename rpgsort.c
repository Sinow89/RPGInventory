#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

#define TOTAL_ITEMS 10


typedef struct item_t{
    char name[20];
    int gold;
    int rarity;
    float kilo;
} item_t;

int main(){

    SetTargetFPS(60);
    InitWindow(800, 600, "RPG - Inventory");

    item_t item[TOTAL_ITEMS] = {
        {"Dagger", 10, 1, 25.0f},
        {"Sword", 50, 5, 50.0f}, 
        {"Armor", 150, 5, 50.0f}, 
        {"Stick", 25, 5, 50.0f},
        {"Apple", 5, 5, 50.0f},
        {"Bread", 10, 5, 50.0f},
        {"Silver Sword", 250, 5, 50.0f},
        {"Black Sword", 500, 5, 50.0f},
        {"Gold Sword", 1000, 5, 50.0f},
        {"Platinum Sword", 5000, 5, 50.0f}
    };

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        char item_text[256];

        // Format the debug information into a string
        for(int i = 0; i < TOTAL_ITEMS; i++){
            sprintf(item_text, "Item: %s, %.2d, %d, %.2f", item[i].name, item[i].gold, item[i].rarity, item[i].kilo);
            DrawText(item_text, 200, 100 + (i * 30), 20, DARKGRAY);
        }


        EndDrawing();
    }
    CloseWindow();
}