#include "raylib.h"
#include <math.h>

#define szerokosc 800
#define wysokosc 600
#define maxPocisk 10

typedef struct Zawodnik {
    Vector2 pozycja;
    Vector2 predkosc;
    float rotacja;
    float srednica;
} Zawdonik;

typedef struct Pocisk {
    Vector2 pozycja;
    Vector2 predkosc;
    bool aktywny;
} Pocisk;


int main(void) {
    InitWindow(szerokosc, wysokosc, "Asteroids - Maks");

    Zawdonik zawdonik = {0};
    zawdonik.pozycja = (Vector2){szerokosc/2, wysokosc/2};
    zawdonik.predkosc = (Vector2){0, 0};
    zawdonik.rotacja = 0.0f; 
    zawdonik.srednica = 15.0f;

    Pocisk pocisk[maxPocisk] = {0};

    SetTargetFPS(60); 

    while (!WindowShouldClose()){

            if (IsKeyDown(KEY_LEFT)) zawdonik.rotacja -= 4.5f;

            if (IsKeyDown(KEY_RIGHT)) zawdonik.rotacja += 4.5f; 

            if (IsKeyDown(KEY_UP)){
            zawdonik.predkosc.x += cosf((zawdonik.rotacja - 90) * DEG2RAD) * 0.1f;
            zawdonik.predkosc.y += sinf((zawdonik.rotacja - 90) * DEG2RAD) * 0.1f;
        }

            zawdonik.pozycja.x += zawdonik.predkosc.x;
            zawdonik.pozycja.y += zawdonik.predkosc.y;

            if (zawdonik.pozycja.x > szerokosc){
                zawdonik.pozycja.x = 0;
            } 
            else if (zawdonik.pozycja.x < 0){
                zawdonik.pozycja.x = szerokosc;
            }

            if (zawdonik.pozycja.y > wysokosc){
                zawdonik.pozycja.y = 0;
            } 
            else if (zawdonik.pozycja.y < 0){
                zawdonik.pozycja.y = wysokosc;
            }

            if (IsKeyPressed(KEY_SPACE)){
                for (int i = 0;i < maxPocisk;i++){
                    if (!pocisk[i].aktywny){
                        pocisk[i].aktywny = true;

                        pocisk[i].pozycja.x = zawdonik.pozycja.x + cosf((zawdonik.rotacja - 90) * DEG2RAD) * zawdonik.srednica;
                        pocisk[i].pozycja.y = zawdonik.pozycja.y + sinf((zawdonik.rotacja - 90) * DEG2RAD) * zawdonik.srednica;
                        
                        pocisk[i].predkosc.x = cosf((zawdonik.rotacja - 90) * DEG2RAD) * 7.0f;
                        pocisk[i].predkosc.y = sinf((zawdonik.rotacja - 90) * DEG2RAD) * 7.0f;
                        break; 
                    }
                }
            }

            for (int i = 0; i < maxPocisk; i++){
                if (pocisk[i].aktywny){
                    pocisk[i].pozycja.x += pocisk[i].predkosc.x;
                    pocisk[i].pozycja.y += pocisk[i].predkosc.y;

                if (pocisk[i].pozycja.x < 0 || pocisk[i].pozycja.x > szerokosc ||
                    pocisk[i].pozycja.y < 0 || pocisk[i].pozycja.y > wysokosc){
                    pocisk[i].aktywny = false;
                }
                }
            }

        BeginDrawing();
            ClearBackground(BLACK);

            Vector2 v1 = { 
            zawdonik.pozycja.x + cosf((zawdonik.rotacja - 90) * DEG2RAD) * zawdonik.srednica, 
            zawdonik.pozycja.y + sinf((zawdonik.rotacja - 90) * DEG2RAD) * zawdonik.srednica 
            };

            Vector2 v2 = { 
                zawdonik.pozycja.x + cosf((zawdonik.rotacja + 45) * DEG2RAD) * zawdonik.srednica, 
                zawdonik.pozycja.y + sinf((zawdonik.rotacja + 45) * DEG2RAD) * zawdonik.srednica 
            };

            Vector2 v3 = { 
                zawdonik.pozycja.x + cosf((zawdonik.rotacja + 135) * DEG2RAD) * zawdonik.srednica, 
                zawdonik.pozycja.y + sinf((zawdonik.rotacja + 135) * DEG2RAD) * zawdonik.srednica 
            };

            DrawTriangleLines(v1, v2, v3, RAYWHITE);
            
            for (int i = 0; i < maxPocisk;i++){
                if (pocisk[i].aktywny){
                    DrawCircleV(pocisk[i].pozycja, 2, RED);
                }   
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
