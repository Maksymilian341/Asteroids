#include "raylib.h"
#include <math.h>

#define screenWidth 800
#define screenHeight 600
#define maxBullets 10

typedef struct Player {
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float radius;
} Player;

typedef struct Bullet {
    Vector2 position;
    Vector2 velocity;
    bool active;
} Bullet;


int main(void) {
    InitWindow(screenWidth, screenHeight, "Asteroids - Maks");

    Player player = {0};
    player.position = (Vector2){screenWidth/2, screenHeight/2};
    player.velocity = (Vector2){0, 0};
    player.rotation = 0.0f; 
    player.radius = 15.0f;

    Bullet bullets[MAX_BULLETS] = {0};

    SetTargetFPS(60); 

    while (!WindowShouldClose()){

            if (IsKeyDown(KEY_LEFT)) player.rotation -= 4.5f;

            if (IsKeyDown(KEY_RIGHT)) player.rotation += 4.5f; 

            if (IsKeyDown(KEY_UP)){
            player.velocity.x += cosf((player.rotation - 90) * DEG2RAD) * 0.1f;
            player.velocity.y += sinf((player.rotation - 90) * DEG2RAD) * 0.1f;
        }

            player.position.x += player.velocity.x;
            player.position.y += player.velocity.y;

            if (player.position.x > screenWidth){
                player.position.x = 0;
            } 
            else if (player.position.x < 0){
                player.position.x = screenWidth;
            }

            if (player.position.y > screenHeight){
                player.position.y = 0;
            } 
            else if (player.position.y < 0){
                player.position.y = screenHeight;
            }

            if (IsKeyPressed(KEY_SPACE)){
                for (int i = 0;i < maxBullets;i++){
                    if (!bullets[i].active){
                        bullets[i].active = true;

                        bullets[i].position.x = player.position.x + cosf((player.rotation - 90) * DEG2RAD) * player.radius;
                        bullets[i].position.y = player.position.y + sinf((player.rotation - 90) * DEG2RAD) * player.radius;
                        
                        bullets[i].velocity.x = cosf((player.rotation - 90) * DEG2RAD) * 7.0f;
                        bullets[i].velocity.y = sinf((player.rotation - 90) * DEG2RAD) * 7.0f;
                        break; 
                    }
                }
            }

            for (int i = 0; i < maxBullets; i++){
                if (bullets[i].active){
                    bullets[i].position.x += bullets[i].velocity.x;
                    bullets[i].position.y += bullets[i].velocity.y;

                if (bullets[i].position.x < 0 || bullets[i].position.x > screenWidth ||
                    bullets[i].position.y < 0 || bullets[i].position.y > screenHeight){
                    bullets[i].active = false;
                }
                }
            }

        BeginDrawing();
            ClearBackground(BLACK);

            Vector2 v1 = { 
            player.position.x + cosf((player.rotation - 90) * DEG2RAD) * player.radius, 
            player.position.y + sinf((player.rotation - 90) * DEG2RAD) * player.radius 
            };

            Vector2 v2 = { 
                player.position.x + cosf((player.rotation + 30) * DEG2RAD) * player.radius, 
                player.position.y + sinf((player.rotation + 30) * DEG2RAD) * player.radius 
            };

            Vector2 v3 = { 
                player.position.x + cosf((player.rotation + 150) * DEG2RAD) * player.radius, 
                player.position.y + sinf((player.rotation + 150) * DEG2RAD) * player.radius 
            };

            DrawTriangleLines(v1, v2, v3, RAYWHITE);
            
            for (int i = 0; i < maxBullets;i++){
                if (bullets[i].active){
                    DrawCircleV(bullets[i].position, 2, RED);
                }   
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
