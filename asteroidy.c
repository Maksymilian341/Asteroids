#include "raylib.h"
#include "asteroidy.h"
#include "bullety.h"
#include "player.h"
#include "game_states.h"

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