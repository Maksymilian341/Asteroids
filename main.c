#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define screenWidth 800
#define screenHeight 600
#define maxBullets 10
#define maxSmallAsteroids 6
#define maxMediumAsteroids 5
#define maxBigAsteroids 3
#define maxHighScores 6



typedef struct Player{
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float radius;
    int score;
    
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


void SaveHighScore(Player *player){
    int high_scores[maxHighScores + 1] = {0};
    int count = 0;
    FILE* plik = fopen("high_scores.txt", "r");
    if (plik != NULL) { 
        while (count < maxHighScores && fscanf(plik, "%d", &high_scores[count]) == 1) {
            count++;
        }
        fclose(plik);
    }
    high_scores[count] = player->score;
    count++;

                
    for (int j = 0; j < count - 1; j++) {
        for (int k = 0; k < count - j - 1; k++) {
            if (high_scores[k] < high_scores[k + 1]) {
                int temp = high_scores[k];
                high_scores[k] = high_scores[k + 1];
                high_scores[k + 1] = temp;
            }
        }
    }

    plik = fopen("high_scores.txt", "w");
    if (plik != NULL) {
        int limit = (count < maxHighScores) ? count : maxHighScores;
        for (int j = 0; j < limit; j++) {
            fprintf(plik, "%d\n", high_scores[j]);
        }
        fclose(plik);
    }
}
void EndScreen(Player player, int *game_state){
    ClearBackground(BLACK);
    DrawText(TextFormat("YOUR SCORE: %06i",player.score), 200, screenHeight/2 - 200, 40, RAYWHITE);
    DrawText("PRESS ENTER TO SAVE YOUR SCORE", 220, screenHeight - 40, 20, RAYWHITE);    
}

void NewGame(Asteroids *big_asteroids, Asteroids *medium_asteroids, Asteroids *small_asteroids,Bullet *bullets,Player *player, int *game_state){
    player->position = (Vector2){screenWidth/2, screenHeight/2};
    player->velocity = (Vector2){0, 0};
    player->rotation = 0.0f;
    player->radius = 15.0f;
    //player->score = 0;

    for(int i = 0; i < maxBullets; i++)
        bullets[i].active = false;

    for(int i = 0; i < maxBigAsteroids; i++)
        big_asteroids[i].active = false;

    for(int i = 0; i < maxMediumAsteroids; i++)
        medium_asteroids[i].active = false;

    for(int i = 0; i < maxSmallAsteroids; i++)
        small_asteroids[i].active = false;

    *game_state = 3;
}

void UpdatePlayer(Player *player){
    /* rotacja w lewo*/
            if (IsKeyDown(KEY_LEFT)){
                player->rotation -= 4.5f;
            }

            /* rotacja w prawo */
            if (IsKeyDown(KEY_RIGHT)){
                player->rotation += 4.5f; 
            }

            /* podstawowy ruch nadanie predkosci i kontrola wyjezdzania z mapy */
            if (IsKeyDown(KEY_UP)){
            player->velocity.x += cosf((player->rotation - 90) * DEG2RAD) * 0.1f;
            player->velocity.y += sinf((player->rotation - 90) * DEG2RAD) * 0.1f;
            }
            
            player->position.x += player->velocity.x;
            player->position.y += player->velocity.y;
            
            if (player->position.x > screenWidth){
                player->position.x = 0;
            } 
            else if (player->position.x < 0){
                player->position.x = screenWidth;
            }

            if (player->position.y > screenHeight){
                player->position.y = 0;
            } 
            else if (player->position.y < 0){
                player->position.y = screenHeight;
            }
    }

void Shooting(float *shoot_cooldown, Player *player, Bullet *bullets){
/* wystrzeliwanie bulleta i nadanie mu predkosci */
    if (IsKeyPressed(KEY_SPACE)){
        if(*shoot_cooldown <= 0.0f){
            for (int i = 0;i < maxBullets;i++){
                    if (!bullets[i].active){
                        bullets[i].active = true;

                        bullets[i].position.x = player->position.x + cosf((player->rotation - 90) * DEG2RAD) * player->radius;
                        bullets[i].position.y = player->position.y + sinf((player->rotation - 90) * DEG2RAD) * player->radius;
                        
                        bullets[i].velocity.x = cosf((player->rotation - 90) * DEG2RAD) * 7.0f;
                        bullets[i].velocity.y = sinf((player->rotation - 90) * DEG2RAD) * 7.0f;
                        break; 
                    }
            }
        }
                *shoot_cooldown = 0.17f;
    }
}

void DeleteBullet(Bullet *bullets){
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
}

void GeneratingAsteroids(Asteroids *big_asteroids, Asteroids *medium_asteroids, Asteroids *small_asteroids){
            for (int i = 0;i < maxBigAsteroids;i++){
                if (!big_asteroids[i].active){
                    int temp = GetRandomValue(0, 1);
                    big_asteroids[i].active = true;
                    if(temp == 0){
                    big_asteroids[i].position.x = GetRandomValue(0,screenWidth);
                    big_asteroids[i].position.y = screenHeight;
                    }
                    if(temp == 1){
                    big_asteroids[i].position.x = GetRandomValue(0,screenWidth);;
                    big_asteroids[i].position.y = 0;
                    }
                    /*
                    if(temp == 2){
                    big_asteroids[i].position.x = screenWidth;
                    big_asteroids[i].position.y = 0;
                    }
                    if(temp == 3){
                    big_asteroids[i].position.x = screenWidth;
                    big_asteroids[i].position.y = screenHeight;
                    }
                    */
                    big_asteroids[i].velocity.x = cosf((GetRandomValue(0, 360)) * DEG2RAD) * 1.0f;
                    big_asteroids[i].velocity.y = sinf(GetRandomValue(0, 360) * DEG2RAD) * 1.0f;

                    big_asteroids[i].rotation = 2.0f; 
                    big_asteroids[i].radius = 30.0f;
                    break; 
                }
            }
            
            for (int i = 0;i < maxMediumAsteroids;i++){
                if (!medium_asteroids[i].active){
                    int temp = GetRandomValue(0, 1);
                    medium_asteroids[i].active = true;
                    if(temp == 0){
                    medium_asteroids[i].position.x = GetRandomValue(0,screenWidth);
                    medium_asteroids[i].position.y = screenHeight;
                    }
                    if(temp == 1){
                    medium_asteroids[i].position.x = GetRandomValue(0,screenWidth);;
                    medium_asteroids[i].position.y = 0;
                    }
                    medium_asteroids[i].velocity.x = cosf((GetRandomValue(0, 360)) * DEG2RAD) * 2.0f;
                    medium_asteroids[i].velocity.y = sinf(GetRandomValue(0, 360) * DEG2RAD) * 2.0f;

                    medium_asteroids[i].rotation = 2.0f; 
                    medium_asteroids[i].radius = 20.0f;
                    break; 
                }
            }
            
            for (int i = 0;i < maxSmallAsteroids;i++){
                if (!small_asteroids[i].active){
                    int temp = GetRandomValue(0, 1);
                    small_asteroids[i].active = true;
                    if(temp == 0){
                    small_asteroids[i].position.x = GetRandomValue(0,screenWidth);
                    small_asteroids[i].position.y = screenHeight;
                    }
                    if(temp == 1){
                    small_asteroids[i].position.x = GetRandomValue(0,screenWidth);;
                    small_asteroids[i].position.y = 0;
                    }
                    small_asteroids[i].velocity.x = cosf((GetRandomValue(0, 360)) * DEG2RAD) * 2.0f;
                    small_asteroids[i].velocity.y = sinf(GetRandomValue(0, 360) * DEG2RAD) * 2.0f;

                    small_asteroids[i].rotation = 2.0f; 
                    small_asteroids[i].radius = 10.0f;
                    break; 
                }
            }
}


void DeleteAsteroids(Asteroids *big_asteroids, Asteroids *medium_asteroids, Asteroids *small_asteroids){
    /* Usuwanie big asteroid ktore opuscily plansze */
            for (int i = 0; i < maxBigAsteroids; i++){
                if (big_asteroids[i].active){
                    big_asteroids[i].position.x += big_asteroids[i].velocity.x;
                    big_asteroids[i].position.y += big_asteroids[i].velocity.y;

                if (big_asteroids[i].position.x < 0 || big_asteroids[i].position.x > screenWidth ||
                    big_asteroids[i].position.y < 0 || big_asteroids[i].position.y > screenHeight){
                    big_asteroids[i].active = false;
                }
                }
            }

            /* Usuwanie medium asteroid ktore opuscily plansze */
            for (int i = 0; i < maxMediumAsteroids; i++){
                if (medium_asteroids[i].active){
                    medium_asteroids[i].position.x += medium_asteroids[i].velocity.x;
                    medium_asteroids[i].position.y += medium_asteroids[i].velocity.y;

                if (medium_asteroids[i].position.x < 0 || medium_asteroids[i].position.x > screenWidth ||
                    medium_asteroids[i].position.y < 0 || medium_asteroids[i].position.y > screenHeight){
                    medium_asteroids[i].active = false;
                }
                }
            }

             /* Usuwanie small asteroid ktore opuscily plansze */
            for (int i = 0; i < maxSmallAsteroids; i++){
                if (small_asteroids[i].active){
                    small_asteroids[i].position.x += small_asteroids[i].velocity.x;
                    small_asteroids[i].position.y += small_asteroids[i].velocity.y;

                if (small_asteroids[i].position.x < 0 || small_asteroids[i].position.x > screenWidth ||
                    small_asteroids[i].position.y < 0 || small_asteroids[i].position.y > screenHeight){
                    small_asteroids[i].active = false;
                }
                }
            }
}

void ShipCollision(Asteroids *big_asteroids, Asteroids *medium_asteroids, Asteroids *small_asteroids, Player *player,Bullet *bullets, int *game_state){
            for(int i = 0; i < maxBigAsteroids; i++){
                if(big_asteroids[i].active){
                    if(CheckCollisionCircles(player->position, player->radius, big_asteroids[i].position, big_asteroids[i].radius)){
                        SaveHighScore(player);
                        //EndScreen(*player, game_state);
                        NewGame(big_asteroids,medium_asteroids,small_asteroids,bullets,player,game_state);
                    }
                }
            }

            for(int i = 0; i < maxMediumAsteroids; i++){
                if(medium_asteroids[i].active){
                    if(CheckCollisionCircles(player->position, player->radius, medium_asteroids[i].position, medium_asteroids[i].radius)){
                        SaveHighScore(player);
                        //EndScreen(*player, game_state);
                        NewGame(big_asteroids,medium_asteroids,small_asteroids,bullets,player,game_state);
                    }
                }
            }

            for(int i = 0; i < maxSmallAsteroids; i++){
                if(small_asteroids[i].active){
                    if(CheckCollisionCircles(player->position, player->radius, small_asteroids[i].position, small_asteroids[i].radius)){
                        SaveHighScore(player);
                        NewGame(big_asteroids,medium_asteroids,small_asteroids,bullets,player,game_state);
                        //EndScreen(*player, game_state);
                    }
                }
            }
}

void BulletCollision(Asteroids *big_asteroids, Asteroids *medium_asteroids, Asteroids *small_asteroids,Bullet *bullets,Player *player){
            for(int i = 0; i < maxBigAsteroids;i++){
                if (!big_asteroids[i].active) continue;
                for(int j = 0; j < maxBullets; j++){
                    if (!bullets[j].active) continue;
                    if(CheckCollisionPointCircle(bullets[j].position, big_asteroids[i].position, big_asteroids[i].radius)){
                    big_asteroids[i].active = false;
                    bullets[j].active = false;
                    player->score = player->score + 50;
                    }
                }
            }

            for(int i = 0; i < maxMediumAsteroids;i++){
                if (!medium_asteroids[i].active) continue;
                for(int j = 0; j < maxBullets; j++){
                    if (!bullets[j].active) continue;
                    if(CheckCollisionPointCircle(bullets[j].position, medium_asteroids[i].position, medium_asteroids[i].radius)){
                    medium_asteroids[i].active = false;
                    bullets[j].active = false;
                    player->score = player->score + 50;
                    }
                }
            }

            for(int i = 0; i < maxSmallAsteroids;i++){
                if (!small_asteroids[i].active) continue;
                for(int j = 0; j < maxBullets; j++){
                    if (!bullets[j].active) continue;
                    if(CheckCollisionPointCircle(bullets[j].position, small_asteroids[i].position, small_asteroids[i].radius)){
                    small_asteroids[i].active = false;
                    bullets[j].active = false;
                    player->score = player->score + 50;
                    }
                }
            }
}

void SlowDownShip(Player *player){
            player->velocity.x *=  0.99f;
            player->velocity.y *= 0.99f;
            
            float maxSpeed = 3.0f;
            float currentSpeed = sqrtf(player->velocity.x * player->velocity.x + player->velocity.y * player->velocity.y);
            if(currentSpeed > maxSpeed){
                player->velocity.x = (player->velocity.x / currentSpeed) * maxSpeed;
                player->velocity.y = (player->velocity.y / currentSpeed) * maxSpeed;
            }
}

void Menu(){
    ClearBackground(BLACK);
    DrawText("ASTEROIDS", 185, screenHeight/2 - 200, 80, RAYWHITE);
    DrawText("PRESS N TO START", 310, screenHeight/2, 20, RAYWHITE);
    DrawText("PRESS H FOF HIGHSCORE", 277, screenHeight/2 + 40, 20, RAYWHITE);
    /*
    for(int i = 0; i < screenWidth; i++){
        for(int j = 0; j < screenHeight; j++){
            int if_star = GetRandomValue(0,1000);
            if(if_star == 67){
                DrawCircle(i, j, 2, RAYWHITE);
            }
        }
    }
    */
}

void HighScore(){
    ClearBackground(BLACK);
    DrawText("HIGH SCORES", 272, screenHeight/2 - 200, 40, RAYWHITE);
    DrawText("PRESS U TO GO BACK", 560, screenHeight - 40, 20, RAYWHITE);
    char wiersz[6];
    FILE* plik = fopen("high_scores.txt", "r");
    int down = 150;
    for(int i = 1; i <= 6; i++){
        fgets(wiersz,sizeof wiersz,plik);
        DrawText(TextFormat("%d. %s",i,wiersz), 272, screenHeight/2 - down, 40, RAYWHITE);
        
        down = down - 50;
    }
    /*
    DrawText(TextFormat(". %s",wiersz), 272, screenHeight/2 - 150, 40, RAYWHITE);
    DrawText("2.", 272, screenHeight/2 - 100, 40, RAYWHITE);
    DrawText("3.", 272, screenHeight/2 - 50, 40, RAYWHITE);
    DrawText("4.", 272, screenHeight/2, 40, RAYWHITE);
    DrawText("5.", 272, screenHeight/2 + 50, 40, RAYWHITE);
    */
    fclose(plik);
}

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
                //player.name[10] = ""; 
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
            BulletCollision(&big_asteroids, &medium_asteroids, &small_asteroids, bullets, &player);
            
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
