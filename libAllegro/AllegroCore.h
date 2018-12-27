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
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#define max 4
#define FPS 60
#define WIDTH 1120
#define HEIGHT 720
#define larg 1120
#define alt 720

typedef struct{
    int life;
    int x;
    int y;
    char hori;
    char ataque;
    int skin;
    int pe;
}person;

double startingTime;
double blinkingTime;
double control_animation;
int chupeta;

ALLEGRO_DISPLAY *main_window;
ALLEGRO_EVENT_QUEUE *eventsQueue;
ALLEGRO_FONT *ubuntu;
ALLEGRO_FONT *start;
ALLEGRO_FONT *pedrito;
ALLEGRO_BITMAP *objects;
ALLEGRO_BITMAP *hscs;
ALLEGRO_FONT *telaip;
//personagens
ALLEGRO_BITMAP *actor1;
ALLEGRO_BITMAP *actor2;
ALLEGRO_BITMAP *actor3;
ALLEGRO_BITMAP *actor4;
ALLEGRO_BITMAP *actor5;
ALLEGRO_BITMAP *actor6;
//personagens selecionados
ALLEGRO_BITMAP *actor1_select;
ALLEGRO_BITMAP *actor2_select;
ALLEGRO_BITMAP *actor3_select;
ALLEGRO_BITMAP *actor4_select;
ALLEGRO_BITMAP *actor5_select;
ALLEGRO_BITMAP *actor6_select;
//ponteiro para o mapa
ALLEGRO_BITMAP *mapa1;
ALLEGRO_BITMAP *mapa2;
ALLEGRO_BITMAP *mapa3;
//coracoes
ALLEGRO_BITMAP *cori;
ALLEGRO_BITMAP *cori2;
ALLEGRO_BITMAP *cori3;
ALLEGRO_BITMAP *cori4;
ALLEGRO_BITMAP *cori5;
//sprites de personagem
ALLEGRO_BITMAP *hero;
ALLEGRO_BITMAP *hero1;
ALLEGRO_BITMAP *hero2;
ALLEGRO_BITMAP *hero3;
//sprite de ataque
ALLEGRO_BITMAP *ataque_w;
ALLEGRO_BITMAP *ataque_s;
ALLEGRO_BITMAP *ataque_a;
ALLEGRO_BITMAP *ataque_d;
//animacoes espada
ALLEGRO_BITMAP *sword_up_1;
ALLEGRO_BITMAP *sword_down_1;
ALLEGRO_BITMAP *sword_left_1;
ALLEGRO_BITMAP *sword_right_1;

ALLEGRO_BITMAP *sword_up_2;
ALLEGRO_BITMAP *sword_down_2;
ALLEGRO_BITMAP *sword_left_2;
ALLEGRO_BITMAP *sword_right_2;

ALLEGRO_BITMAP *sword_up_3;
ALLEGRO_BITMAP *sword_down_3;
ALLEGRO_BITMAP *sword_left_3;
ALLEGRO_BITMAP *sword_right_3;

ALLEGRO_BITMAP *sword_up_4;
ALLEGRO_BITMAP *sword_down_4;
ALLEGRO_BITMAP *sword_left_4;
ALLEGRO_BITMAP *sword_right_4;

ALLEGRO_BITMAP *sword_up_5;
ALLEGRO_BITMAP *sword_down_5;
ALLEGRO_BITMAP *sword_left_5;
ALLEGRO_BITMAP *sword_right_5;

ALLEGRO_BITMAP *sword_up_6;
ALLEGRO_BITMAP *sword_down_6;
ALLEGRO_BITMAP *sword_left_6;
ALLEGRO_BITMAP *sword_right_6;

//animacao lanca

ALLEGRO_BITMAP *spear_up_1;
ALLEGRO_BITMAP *spear_down_1;
ALLEGRO_BITMAP *spear_left_1;
ALLEGRO_BITMAP *spear_right_1;

ALLEGRO_BITMAP *spear_up_2;
ALLEGRO_BITMAP *spear_down_2;
ALLEGRO_BITMAP *spear_left_2;
ALLEGRO_BITMAP *spear_right_2;

ALLEGRO_BITMAP *spear_up_3;
ALLEGRO_BITMAP *spear_down_3;
ALLEGRO_BITMAP *spear_left_3;
ALLEGRO_BITMAP *spear_right_3;

ALLEGRO_BITMAP *spear_up_4;
ALLEGRO_BITMAP *spear_down_4;
ALLEGRO_BITMAP *spear_left_4;
ALLEGRO_BITMAP *spear_right_4;

ALLEGRO_BITMAP *spear_up_5;
ALLEGRO_BITMAP *spear_down_5;
ALLEGRO_BITMAP *spear_left_5;
ALLEGRO_BITMAP *spear_right_5;

ALLEGRO_BITMAP *spear_up_6;
ALLEGRO_BITMAP *spear_down_6;
ALLEGRO_BITMAP *spear_left_6;
ALLEGRO_BITMAP *spear_right_6;

//musicas
ALLEGRO_AUDIO_STREAM *musica;
//samples
ALLEGRO_SAMPLE *cursor;
ALLEGRO_SAMPLE *enter;
ALLEGRO_SAMPLE *espada;
ALLEGRO_SAMPLE *lanca;

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
double blink();
void blinkTimer();
//Função de Carregamento de Gráficos
bool loadGraphics_and_sounds();

// função de coleta de caracter
char move();

//funções de impressão de tela
void imprimi_jog(char mapa[alt][larg], person jogadores[max]);
void attack(int num_jogadores, person jogadores[max], char mapa[alt][larg], int id_local,int in_mapa);
void imprimi_mapa(int num_map);
void imprimi_status(person jogador);
//função de audio
void setAudio(char k[]); 

int digitemenu();
void digite_ip(char ip[12]);
int select_player();
int select_map();
void game_begin(int map_number, person jogador, int l_inic, int c_inic);

#endif
