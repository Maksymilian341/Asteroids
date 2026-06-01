#ifndef ASTEROIDY_H
#define ASTEROIDY_H

#include "raylib.h"
#include <math.h>

#define screenWidth 800
#define screenHeight 600
#define maxSmallAsteroids 6
#define maxMediumAsteroids 5
#define maxBigAsteroids 3

typedef struct Asteroids{
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float radius;
    bool active;
}Asteroids;

void GeneratingAsteroids(Asteroids *big_asteroids, Asteroids *medium_asteroids, Asteroids *small_asteroids);
void DeleteAsteroids(Asteroids *big_asteroids, Asteroids *medium_asteroids, Asteroids *small_asteroids);
#endif