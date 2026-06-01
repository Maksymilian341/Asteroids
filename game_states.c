#include "raylib.h"
#include "asteroidy.h"
#include "bullety.h"
#include "player.h"
#include "game_states.h"

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
        for (int j = 0; j < 6; j++) {
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