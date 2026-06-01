#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Asteroids Asteroids;
typedef struct Bullet Bullet;

typedef struct Player {
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float radius;
    int score;
} Player;

void UpdatePlayer(Player *player);
void ShipCollision(Asteroids *big_asteroids, Asteroids *medium_asteroids, Asteroids *small_asteroids, Player *player,Bullet *bullets, int *game_state);
void SlowDownShip(Player *player);
#endif