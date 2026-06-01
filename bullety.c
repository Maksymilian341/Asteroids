#include "raylib.h"
#include "asteroidy.h"
#include "bullety.h"
#include "player.h"
#include "game_states.h"

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