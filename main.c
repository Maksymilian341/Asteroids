#include "raylib.h"
#include <math.h>

#define screenWidth 800
#define screenHeight 600

typedef struct Player {
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float radius;
} Player;

int main(void) {
    InitWindow(screenWidth, screenHeight, "Asteroids - Maks");

    Player player = { 0 };
    player.position = (Vector2){ screenWidth/2, screenHeight/2 };
    player.velocity = (Vector2){ 0, 0 };
    player.rotation = 0.0f; 
    player.radius = 15.0f;

    SetTargetFPS(60); 

    while (!WindowShouldClose()) {
    
        BeginDrawing();
            ClearBackground(BLACK);
            DrawPolyLines(player.position, 3, player.radius, player.rotation, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
