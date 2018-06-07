#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define FPS 60
#define WIDTH 1120
#define HEIGHT 720
#define larg 1120
#define alt 720

double startingTime;
ALLEGRO_DISPLAY *main_window;
ALLEGRO_EVENT_QUEUE *eventsQueue;
ALLEGRO_FONT *ubuntu;
ALLEGRO_FONT *start;
ALLEGRO_BITMAP *objects;
ALLEGRO_BITMAP *hscs;

//Funções Centrais da Allegro
bool coreInit();
bool windowInit(int W, int H, char title[]);
bool inputInit();
bool fontInit();
void allegroEnd();

//Funções para Controle da quantidade de Frames por Segundo
void startTimer();
double getTimer();
void FPSLimit();

//Função de Carregamento de Gráficos
bool loadGraphics();
#endif
