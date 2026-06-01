#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#include "asteroidy.h"
#include "bullety.h"
#include "player.h"
#include "game_states.h"


int main(void) {
    InitWindow(screenWidth, screenHeight, "Asteroids - Maks");
    Player player = {0};
    player.position = (Vector2){screenWidth/2, screenHeight/2};
    player.velocity = (Vector2){0, 0};
    player.rotation = 0.0f; 
    player.radius = 15.0f;
    player.score = 0;

    Bullet bullets[maxBullets] = {0};
    Asteroids small_asteroids[maxSmallAsteroids] = {0};
    Asteroids medium_asteroids[maxMediumAsteroids] = {0};
    Asteroids big_asteroids[maxBigAsteroids] = {0};
    

    SetTargetFPS(60); 

    float shoot_cooldown = 0.0f;
    
    int game_state = 0;

    while (!WindowShouldClose()){

            if (game_state == 3){
                if (IsKeyPressed(KEY_ENTER)) {
                player.score = 0;
                game_state = 0;
            }
            }

            if (game_state == 0) {
            
            if (IsKeyPressed(KEY_N)) {
                game_state = 1;
            }
            
            if (IsKeyPressed(KEY_H)) {
                game_state = 2;
            }
            }  
            
            if (game_state == 1) {
            float dt = GetFrameTime();
            if(shoot_cooldown > 0.0f) shoot_cooldown -= dt;

            UpdatePlayer(&player);
            /* wystrzeliwanie bulleta i nadanie mu predkosci */
            Shooting(&shoot_cooldown, &player, bullets);

            /* Usuwanie bulletow ktore opuscily plansze */
            DeleteBullet(bullets);
            /* generowanie asteroid w losowym narozniku ekranu */
            GeneratingAsteroids(big_asteroids,medium_asteroids,small_asteroids);

            
            /* Usuwanie big asteroid ktore opuscily plansze */
            DeleteAsteroids(big_asteroids,medium_asteroids,small_asteroids);

            /* kolizja asteroida-statek działa na hitboxach okregow i odleglosci srednic */
            ShipCollision(big_asteroids,medium_asteroids,small_asteroids,&player,bullets,&game_state);

            /* kolizja pocisk-asteroida za pomoca kolizji okregu z punktem */
            BulletCollision(big_asteroids, medium_asteroids, small_asteroids, bullets, &player);
            
            /* (bardzo udane :) )proby zapobiegniecia nieskonczonej predkosci statku */
            SlowDownShip(&player);
            }
            
        BeginDrawing();

            if (game_state == 3){
               EndScreen(player, &game_state);
            }

            if (game_state == 0) {
                Menu();
            }
            if (game_state == 2) {
                HighScore();
                if (IsKeyPressed(KEY_U)) {
                game_state = 0;
            }
            } 
            
            else if (game_state == 1) {
            ClearBackground(BLACK);
            DrawText(TextFormat("Score: %06i", player.score), 10, 10, 20, RAYWHITE);

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
                    DrawCircleV(bullets[i].position, 2, RAYWHITE);
                }   
            }
            /* asteroidy */
            for (int i = 0; i < maxBigAsteroids;i++){
                if (big_asteroids[i].active){
                    DrawPolyLines(big_asteroids[i].position, 7, big_asteroids[i].radius, big_asteroids[i].rotation, RAYWHITE);
                }   
            }

            for (int i = 0; i < maxMediumAsteroids;i++){
                if (medium_asteroids[i].active){
                    DrawPolyLines(medium_asteroids[i].position, 7, medium_asteroids[i].radius, medium_asteroids[i].rotation, RAYWHITE);
                }   
            }

            for (int i = 0; i < maxSmallAsteroids;i++){
                if (small_asteroids[i].active){
                    DrawPolyLines(small_asteroids[i].position, 7, small_asteroids[i].radius, small_asteroids[i].rotation, RAYWHITE);
                }   
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
