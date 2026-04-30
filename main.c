#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define screenWidth 800
#define screenHeight 600
#define maxBullets 10
#define maxAsteroids 15


typedef struct Player{
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float radius;
}Player;

typedef struct Bullet{
    Vector2 position;
    Vector2 velocity;
    bool active;
}Bullet;

typedef struct Asteroids{
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float radius;
    bool active;
}Asteroids;

int main(void) {
    InitWindow(screenWidth, screenHeight, "Asteroids - Maks");
    Player player = {0};
    player.position = (Vector2){screenWidth/2, screenHeight/2};
    player.velocity = (Vector2){0, 0};
    player.rotation = 0.0f; 
    player.radius = 15.0f;

    Bullet bullets[maxBullets] = {0};
    Asteroids asteroids[maxAsteroids] = {0};


    SetTargetFPS(60); 

    while (!WindowShouldClose()){

            /* rotacja w lewo*/
            if (IsKeyDown(KEY_LEFT)){
                player.rotation -= 4.5f;
            }

            /* rotacja w prawo */
            if (IsKeyDown(KEY_RIGHT)){
                player.rotation += 4.5f; 
            }

            /* podstawowy ruch */
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
            
            /* wystrzeliwanie bulleta */
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
            /* Usuwanie bulletow ktore opuscily plansze */
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

            /* generowanie asteroid */
            for (int i = 0;i < maxAsteroids;i++){
                if (!asteroids[i].active){
                    int temp = GetRandomValue(0, 3);
                    asteroids[i].active = true;
                    if(temp == 0){
                    asteroids[i].position.x = 0;
                    asteroids[i].position.y = 0;
                    }
                    if(temp == 1){
                    asteroids[i].position.x = 0;
                    asteroids[i].position.y = screenHeight;
                    }
                    if(temp == 2){
                    asteroids[i].position.x = screenWidth;
                    asteroids[i].position.y = 0;
                    }
                    if(temp == 3){
                    asteroids[i].position.x = screenWidth;
                    asteroids[i].position.y = screenHeight;
                    }
                    asteroids[i].velocity.x = cosf((GetRandomValue(0, 360)) * DEG2RAD) * 2.5f;
                    asteroids[i].velocity.y = sinf(GetRandomValue(0, 360) * DEG2RAD) * 2.5f;

                    asteroids[i].rotation = 2.0f; 
                    asteroids[i].radius = 30.0f;
                    break; 
                }
            }
            
            /* Usuwanie asteroid ktore opuscily plansze */
            for (int i = 0; i < maxAsteroids; i++){
                if (asteroids[i].active){
                    asteroids[i].position.x += asteroids[i].velocity.x;
                    asteroids[i].position.y += asteroids[i].velocity.y;

                if (asteroids[i].position.x < 0 || asteroids[i].position.x > screenWidth ||
                    asteroids[i].position.y < 0 || asteroids[i].position.y > screenHeight){
                    asteroids[i].active = false;
                }
                }
            }
        

        BeginDrawing();
            ClearBackground(BLACK);

            /* rysowanie trojkata rownoramiennego */
            Vector2 v1 = { 
            player.position.x + cosf((player.rotation - 90) * DEG2RAD) * player.radius, 
            player.position.y + sinf((player.rotation - 90) * DEG2RAD) * player.radius 
            };

            Vector2 v2 = { 
                player.position.x + cosf((player.rotation + 45) * DEG2RAD) * player.radius, 
                player.position.y + sinf((player.rotation + 45) * DEG2RAD) * player.radius 
            };

            Vector2 v3 = { 
                player.position.x + cosf((player.rotation + 135) * DEG2RAD) * player.radius, 
                player.position.y + sinf((player.rotation + 135) * DEG2RAD) * player.radius 
            };

            DrawTriangleLines(v1, v2, v3, RAYWHITE);
            
            /* strzelanie */
            for (int i = 0; i < maxBullets;i++){
                if (bullets[i].active){
                    DrawCircleV(bullets[i].position, 2, RED);
                }   
            }
            for (int i = 0; i < maxAsteroids;i++){
                if (asteroids[i].active){
                    DrawPolyLines(asteroids[i].position, 7, asteroids[i].radius, asteroids[i].rotation, RAYWHITE);
                }   
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
