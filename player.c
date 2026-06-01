#include "raylib.h"
#include "asteroidy.h"
#include "bullety.h"
#include "player.h"
#include "game_states.h"

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