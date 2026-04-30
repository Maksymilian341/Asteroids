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
    player.position = (Vector2){screenWidth/2, screenHeight/2};
    player.velocity = (Vector2){0, 0};
    player.rotation = 0.0f; 
    player.radius = 15.0f;

    SetTargetFPS(60); 

    while (!WindowShouldClose()) {
    
        BeginDrawing();
            ClearBackground(BLACK);
            DrawPolyLines(player.position, 3, player.radius, player.rotation, RAYWHITE);

            if (IsKeyDown(KEY_LEFT)) player.rotation -= 4.5f;

            if (IsKeyDown(KEY_RIGHT)) player.rotation += 4.5f; 

            if (IsKeyDown(KEY_UP)) {
            player.velocity.x += cosf(player.rotation * DEG2RAD) * 0.1f;
            player.velocity.y += sinf(player.rotation * DEG2RAD) * 0.1f;
        }

            player.position.x += player.velocity.x;
            player.position.y += player.velocity.y;

            if (player.position.x > screenWidth){
                player.position.x = 0;
            } 
            else if (player.position.x < 0) {
                player.position.x = screenWidth;
            }


            if (player.position.y > screenHeight) {
                player.position.y = 0;
            } 
            else if (player.position.y < 0) {
                player.position.y = screenHeight;
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
