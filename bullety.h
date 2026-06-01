#ifndef BULLETY_H
#define BULLETY_H

#include "raylib.h"
#include <math.h>

#define screenWidth 800
#define screenHeight 600
#define maxBullets 10

typedef struct Asteroids Asteroids;
typedef struct Player Player;

typedef struct Bullet{
    Vector2 position;
    Vector2 velocity;
    bool active;
}Bullet;

void Shooting(float *shoot_cooldown, Player *player, Bullet *bullets);
void DeleteBullet(Bullet *bullets);
void BulletCollision(Asteroids *big_asteroids, Asteroids *medium_asteroids, Asteroids *small_asteroids,Bullet *bullets,Player *player);

#endif