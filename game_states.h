#ifndef GAMESTATES_H
#define GAMESTATES_H


#include "raylib.h"
#include "player.h" 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define maxHighScores 6


typedef struct Asteroids Asteroids;
typedef struct Bullet Bullet;

void SaveHighScore(Player *player);
void EndScreen(Player player, int *game_state);
void NewGame(Asteroids *big_asteroids, Asteroids *medium_asteroids, Asteroids *small_asteroids,Bullet *bullets,Player *player, int *game_state);
void Menu();
void HighScore();
#endif