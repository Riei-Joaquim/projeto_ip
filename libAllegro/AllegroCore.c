#include "AllegroCore.h"


bool coreInit(){
    //modules and add-ons initialization
	if (!al_init()){
        fprintf(stderr, "Falha ao inicializar Allegro.\n");
        return false;
    }
    if (!al_init_image_addon()){
        fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        return false;
    }
    if (!al_init_font_addon()){
        fprintf(stderr, "Falha ao inicializar add-on allegro_font.\n");
        return false;
    }
    if (!al_init_ttf_addon()){
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return false;
    }
    if (!al_init_primitives_addon()){
        fprintf(stderr, "Falha ao inicializar add-on allegro_primitives.\n");
        return false;
    }
    eventsQueue = al_create_event_queue();
    if (!eventsQueue){
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        return false;
    }
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);
    return true;
}

bool windowInit(int W, int H, char title[]){
    //window and event queue creation
    main_window = al_create_display(W, H);
    if (!main_window){
        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }
    al_set_window_title(main_window, title);
    //registra janela na fila de eventos
    al_register_event_source(eventsQueue, al_get_display_event_source(main_window));
    return true;
}

bool inputInit(){
	/*------------------------------MOUSE--------------------------------*/
	//Inicializa Mouse
	if (!al_install_mouse()){
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(main_window);
        return false;
    }
    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(main_window, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(main_window);
        return false;
    }
    /*------------------------------MOUSE--------------------------------*/

    /*------------------------------TECLADO------------------------------*/
    if (!al_install_keyboard()){
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return false;
    }

    /*------------------------------TECLADO------------------------------*/
    //Registra mouse e teclado na fila de eventos
    al_register_event_source(eventsQueue, al_get_mouse_event_source());
    al_register_event_source(eventsQueue, al_get_keyboard_event_source());
    return true;
}

bool fontInit(){
    /*------------------------------FONTE--------------------------------*/
    start = al_load_font("Resources/Fonts/pressStart.ttf", 20, 0);
    if (!start){
        fprintf(stderr, "Falha ao carregar \"pressStart.ttf\".\n");
        return false;
    }
    
    ubuntu = al_load_font("Resources/Fonts/pressStart.ttf", 50, 0);
    if (!ubuntu){
        fprintf(stderr, "Falha ao carregar \"Ubuntu-R.ttf\".\n");
        return false;
    }
    telaip = al_load_font("Resources/Fonts/pressStart.ttf", 30, 0);
    if (!telaip){
        fprintf(stderr, "Falha ao carregar \"Ubuntu-R.ttf\".\n");
        return false;
    }
    pedrito = al_load_font("Resources/Fonts/pressStart.ttf", 50, 0);
    return true;
}

void allegroEnd(){
    al_destroy_display(main_window);
    al_destroy_event_queue(eventsQueue);
}

void startTimer(){
    startingTime = al_get_time();
}

double getTimer(){
    return al_get_time() - startingTime;
}

void FPSLimit(){
	if (getTimer() < 1.0/FPS){
        al_rest((1.0 / FPS) - getTimer());
    }
}

void blinkTimer(){
    blinkingTime = al_get_time();
}

double blink(){
    return al_get_time() - blinkingTime;
}

bool loadGraphics_and_sounds(){
    hscs = al_load_bitmap("Resources/Etc/fundo.png");
    if (!hscs){
        fprintf(stderr, "Falha carregando world.png\n");
        return false;
    }

    objects = al_load_bitmap("Resources/Tilesets/objects.png");
    if (!objects){
        fprintf(stderr, "Falha carregando objects.png\n");
        return false;
    }
    //personagens
    actor1 = al_load_bitmap("Resources/Etc/actor1.jpeg");
    actor2 = al_load_bitmap("Resources/Etc/actor2.jpeg");
    actor3 = al_load_bitmap("Resources/Etc/actor3.jpeg");
    actor4 = al_load_bitmap("Resources/Etc/actor4.jpeg");
    actor5 = al_load_bitmap("Resources/Etc/actor5.jpeg");
    actor6 = al_load_bitmap("Resources/Etc/actor6.jpeg");
    //personagens selecionados
    actor1_select = al_load_bitmap("Resources/Etc/actor1_select.jpeg");
    actor2_select = al_load_bitmap("Resources/Etc/actor2_select.jpeg");
    actor3_select = al_load_bitmap("Resources/Etc/actor3_select.jpeg");
    actor4_select = al_load_bitmap("Resources/Etc/actor4_select.jpeg");
    actor5_select = al_load_bitmap("Resources/Etc/actor5_select.jpeg");
    actor6_select = al_load_bitmap("Resources/Etc/actor6_select.jpeg");
    //mapa
    mapa1 = al_load_bitmap("Resources/IN_GAME/mapa1.png");
    mapa2 = al_load_bitmap("Resources/IN_GAME/mapa2.png");
    mapa3 = al_load_bitmap("Resources/IN_GAME/mapa3.png");
    //barra de vida
    cori = al_load_bitmap("Resources/IN_GAME/cori.png");
    
    //load de sprites de personagens
    hero1 = al_load_bitmap("Resources/IN_GAME/Actor1.png");
    hero2 = al_load_bitmap("Resources/IN_GAME/Actor3.png");
    hero3 = al_load_bitmap("Resources/IN_GAME/Actor5.png");

    //load de sprites de ataque
    ataque_w = al_load_bitmap("Resources/IN_GAME/Blow2.png");
    ataque_s = al_load_bitmap("Resources/IN_GAME/Blow1.png");
    ataque_a = al_load_bitmap("Resources/IN_GAME/Blow3.png");
    ataque_d = al_load_bitmap("Resources/IN_GAME/Blow4.png");

    //load da musica
    musica = al_load_audio_stream("Resources/audios/menu.ogg",4,1024);
    //load dos samples
    cursor = al_load_sample("Resources/audios/Cursor2.ogg");
    enter = al_load_sample("Resources/audios/enter.ogg");
    espada = al_load_sample("Resources/audios/sword.ogg");
    lanca = al_load_sample("Resources/audios/spear.ogg");
    return true;
}
void setAudio(char k[]){ //comeca musiquinha
    al_set_audio_stream_playing(musica, false);
    musica = al_load_audio_stream(k, 4, 1024);
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playing(musica, true);
}

void imprimi_mapa(int num_map){
    if(num_map == 0){
        al_draw_bitmap(mapa1,0,0,0);
    }else if(num_map==1){
        al_draw_bitmap(mapa2,0,0,0);
    }else{
        al_draw_bitmap(mapa3,0,0,0);
    }
}

void imprimi_status(person jogador){
    int i;
    if(jogador.life >0){
        for(i=0; i<jogador.life;i++){
            al_draw_bitmap_region(cori,5,8,50,50,50*i,0,0);
        }
    }else{
        al_draw_text(telaip, al_map_rgb(255, 255, 255), larg/2, 500, ALLEGRO_ALIGN_CENTRE, "YOU-DIED!");
        al_draw_text(telaip, al_map_rgb(255, 255, 255), larg/2, 600, ALLEGRO_ALIGN_CENTRE, "Modo observador");
    }
}

int digitemenu(){
    al_draw_bitmap(hscs, 0, 0, 0);
    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, 70, ALLEGRO_ALIGN_CENTRE, "PUNCH KILL");
    al_draw_text(start, al_map_rgb(255, 255, 0), (larg/2)-40, 220, ALLEGRO_ALIGN_CENTRE, "Start Game");
    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 420, ALLEGRO_ALIGN_CENTRE, "Credits");
    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 620, ALLEGRO_ALIGN_CENTRE, "Quit Game");
    al_flip_display();
    int posicao=0;
    int bu;
    while (1){
        ALLEGRO_EVENT evento;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.016);
        al_flush_event_queue(eventsQueue);
        int tem_eventos = al_wait_for_event_until(eventsQueue, &evento, &timeout);
        
        if (tem_eventos && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            allegroEnd();
            return 0;
        }
        if(tem_eventos && evento.type == ALLEGRO_EVENT_KEY_DOWN){
            if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN&& posicao == 0){
                al_play_sample(cursor, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                posicao++;
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 220, ALLEGRO_ALIGN_CENTRE, "Start Game");
                al_draw_text(start, al_map_rgb(255, 255, 30), (larg/2)-40, 420, ALLEGRO_ALIGN_CENTRE, "Credits");
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 620, ALLEGRO_ALIGN_CENTRE, "Quit Game");
                al_flip_display();
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN && posicao == 1){
                al_play_sample(cursor, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                posicao++;
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 220, ALLEGRO_ALIGN_CENTRE, "Start Game");
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 420, ALLEGRO_ALIGN_CENTRE, "Credits");
                al_draw_text(start, al_map_rgb(255, 255, 30), (larg/2)-40, 620, ALLEGRO_ALIGN_CENTRE, "Quit Game");
                al_flip_display();

            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_UP&& posicao == 2){
                al_play_sample(cursor, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                posicao--;
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 220, ALLEGRO_ALIGN_CENTRE, "Start Game");
                al_draw_text(start, al_map_rgb(255, 255, 30), (larg/2)-40, 420, ALLEGRO_ALIGN_CENTRE, "Credits");
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 620, ALLEGRO_ALIGN_CENTRE, "Quit Game");
                al_flip_display();
 
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_UP&& posicao == 1){
                al_play_sample(cursor, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                posicao--;
                al_draw_text(start, al_map_rgb(255, 255, 30), (larg/2)-40, 220, ALLEGRO_ALIGN_CENTRE, "Start Game");
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 420, ALLEGRO_ALIGN_CENTRE, "Credits");
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 620, ALLEGRO_ALIGN_CENTRE, "Quit Game");
                al_flip_display();
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_ENTER){
                al_play_sample(cursor, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                if(posicao==0){
                    return 1;
                }
                else if(posicao==1){

                al_draw_bitmap(hscs,0,0,0);
                al_draw_text(ubuntu, al_map_rgb(255, 255, 255), larg / 2,(20),ALLEGRO_ALIGN_CENTRE,"Creditos");
                al_draw_text(start, al_map_rgb(255, 255, 255), 150,100,ALLEGRO_ALIGN_LEFT,"Washington Igor");
                al_draw_text(start, al_map_rgb(255, 255, 255), 150,150,ALLEGRO_ALIGN_LEFT,"Riei Joaquim");
                al_draw_text(start, al_map_rgb(255, 255, 255), 150,200,ALLEGRO_ALIGN_LEFT,"Pedro Nogueira");
                al_draw_text(start, al_map_rgb(255, 255, 255), 150,250,ALLEGRO_ALIGN_LEFT,"Victor Ximenes");
                al_draw_text(start, al_map_rgb(255, 255, 255), 150,300,ALLEGRO_ALIGN_LEFT,"Rafael Augusto");
                al_draw_text(start, al_map_rgb(255, 255, 255), 150,350,ALLEGRO_ALIGN_LEFT,"Fernando do Rego");
                al_draw_text(pedrito, al_map_rgb(255, 255,255 ), 150,450,ALLEGRO_ALIGN_LEFT,"Agradecimentos:");
                al_draw_text(start, al_map_rgb(255, 255, 255), 150,550,ALLEGRO_ALIGN_LEFT,"Marcos Oliveira");
                al_draw_text(start, al_map_rgb(255, 255, 255), 150,600,ALLEGRO_ALIGN_LEFT,"Heitor Sammuel");
                al_draw_text(ubuntu, al_map_rgb(255, 255, 0), 250,650,ALLEGRO_ALIGN_CENTRE,"Back");
                al_flip_display();
            
                int aux=0;
                while(aux==0){
                    ALLEGRO_EVENT finish;
                    ALLEGRO_TIMEOUT PNC;
                    al_init_timeout(&PNC, 1.0);
                    int tem_finish = al_wait_for_event_until(eventsQueue, &finish, &PNC);
                    if(tem_finish && finish.type == ALLEGRO_EVENT_KEY_DOWN){
                        if(finish.keyboard.keycode==ALLEGRO_KEY_ENTER){
                            aux++;
                        }
                    }
                }
                bu = digitemenu();
                return bu;  
                }
                else if(posicao==2){
                    return 3;
                }
            }
        }
    }
}

int select_player(){
    al_draw_bitmap(hscs, 0, 0, 0);
    al_draw_bitmap(actor1_select,87,162,0);
    al_draw_bitmap(actor2,343,162,0);
    al_draw_bitmap(actor3,599,162,0);
    al_draw_bitmap(actor4,87,458,0);
    al_draw_bitmap(actor5,343,458,0);
    al_draw_bitmap(actor6,599,458,0);
    al_flip_display();
    int mat_posicao[2][3] = {{1,2,3},
                             {4,5,6}};
    int x = 0, y = 0;
    int key=1;
    int n = 1;
    int bu;
    blinkTimer();
    double xtime;
    xtime = blink(); 
    while (1){
        startTimer();
        
        ALLEGRO_EVENT evento;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.03);
 
        int tem_eventos = al_wait_for_event_until(eventsQueue, &evento, &timeout);

        if(tem_eventos && evento.type == ALLEGRO_EVENT_KEY_DOWN){
            if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN && x == 0){
                al_play_sample(cursor, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                x++;
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_UP && x == 1){
                al_play_sample(cursor, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                x--;
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_RIGHT && y != 2){
                al_play_sample(cursor, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                y++;
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_LEFT && y != 0){
                al_play_sample(cursor, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                y--;
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_ENTER){
                al_play_sample(enter, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                if(mat_posicao[x][y]==1){
                    //ACTOR 1
                    return 1;
                }
                else if(mat_posicao[x][y]==2){
                    //ACTOR 2
                    return 2;
                }
                else if(mat_posicao[x][y]==3){
                    //ACTOR 3
                    return 3;
                }
                else if(mat_posicao[x][y]==4){
                    //ACTOR 4
                    return 4;
                }
                else if(mat_posicao[x][y]==5){
                    //ACTOR 5
                    return 5;
                }
                else if(mat_posicao[x][y]==6){
                    //ACTOR 6
                    return 6;
                }   
            }
            if(mat_posicao[x][y]==1){
                al_draw_bitmap(actor1_select,87,162,0);
                al_draw_bitmap(actor2,343,162,0);
                al_draw_bitmap(actor3,599,162,0);
                al_draw_bitmap(actor4,87,458,0);
                al_draw_bitmap(actor5,343,458,0);
                al_draw_bitmap(actor6,599,458,0);
                al_flip_display();
            }
            else if(mat_posicao[x][y]==2){
                al_draw_bitmap(actor1,87,162,0);
                al_draw_bitmap(actor2_select,343,162,0);
                al_draw_bitmap(actor3,599,162,0);
                al_draw_bitmap(actor4,87,458,0);
                al_draw_bitmap(actor5,343,458,0);
                al_draw_bitmap(actor6,599,458,0);
                al_flip_display();
            }
            else if(mat_posicao[x][y]==3){
                al_draw_bitmap(actor1,87,162,0);
                al_draw_bitmap(actor2,343,162,0);
                al_draw_bitmap(actor3_select,599,162,0);
                al_draw_bitmap(actor4,87,458,0);
                al_draw_bitmap(actor5,343,458,0);
                al_draw_bitmap(actor6,599,458,0);
                al_flip_display();
            }
            else if(mat_posicao[x][y]==4){
                al_draw_bitmap(actor1,87,162,0);
                al_draw_bitmap(actor2,343,162,0);
                al_draw_bitmap(actor3,599,162,0);
                al_draw_bitmap(actor4_select,87,458,0);
                al_draw_bitmap(actor5,343,458,0);
                al_draw_bitmap(actor6,599,458,0);
                al_flip_display();
            }
            else if(mat_posicao[x][y]==5){
                al_draw_bitmap(actor1,87,162,0);
                al_draw_bitmap(actor2,343,162,0);
                al_draw_bitmap(actor3,599,162,0);
                al_draw_bitmap(actor4,87,458,0);
                al_draw_bitmap(actor5_select,343,458,0);
                al_draw_bitmap(actor6,599,458,0);
                al_flip_display();
            }
            else if(mat_posicao[x][y]==6){
                al_draw_bitmap(actor1,87,162,0);
                al_draw_bitmap(actor2,343,162,0);
                al_draw_bitmap(actor3,599,162,0);
                al_draw_bitmap(actor4,87,458,0);
                al_draw_bitmap(actor5,343,458,0);
                al_draw_bitmap(actor6_select,599,458,0);
                al_flip_display();
            }
        }
        
        xtime = blink();
        if(xtime<0.25){
        al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "SELECT YOUR FIGHTER");
        al_flip_display();
        }
        if(xtime>=0.25/2 && xtime<0.50/2){
        al_draw_text(ubuntu, al_map_rgb(205, 205, 205), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "SELECT YOUR FIGHTER");
        al_flip_display();
        }
        if(xtime>=0.50/2 && xtime<0.75/2){
        al_draw_text(ubuntu, al_map_rgb(150, 150, 150), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "SELECT YOUR FIGHTER");
        al_flip_display();
        }
        if(xtime>=0.75/2){
        al_draw_text(ubuntu, al_map_rgb(205, 205, 205), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "SELECT YOUR FIGHTER");
        al_flip_display();
        blinkTimer();
        }
        FPSLimit();
    }
}

void digite_ip(char ip[12]){
    int ret_conec, id_local, ind ,i = 0;
    char digito='_';
    int apertou;
    while ((i<=11)&&(digito!='\0')){
        al_draw_bitmap(hscs, 0, 0, 0);
        al_draw_text(telaip, al_map_rgb(255, 255, 255), (larg/2-80), 120, ALLEGRO_ALIGN_CENTRE, "Digite o IP do server:");
        al_draw_text(telaip, al_map_rgb(255, 255, 255), 150, 210, ALLEGRO_ALIGN_LEFT, ip);


        ALLEGRO_EVENT evento;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.05);

        apertou = al_wait_for_event_until(eventsQueue, &evento, &timeout);

        if(apertou && evento.type == ALLEGRO_EVENT_KEY_DOWN){
           al_play_sample(cursor, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            switch(evento.keyboard.keycode){
                case ALLEGRO_KEY_0:
                digito='0';
                break;
                case ALLEGRO_KEY_1:
                digito='1';
                break;            
                case ALLEGRO_KEY_2:
                digito='2';
                break;        
                case ALLEGRO_KEY_3:
                digito='3';
                break;
                case ALLEGRO_KEY_4:
                digito='4';
                break;
                case ALLEGRO_KEY_5:
                digito='5';
                break;
                case ALLEGRO_KEY_6:
                digito='6';
                break;
                case ALLEGRO_KEY_7:
                digito='7';
                break;
                case ALLEGRO_KEY_8:
                digito='8';
                break;
                case ALLEGRO_KEY_9:
                digito='9';
                break;
                case ALLEGRO_KEY_PAD_0:
                digito='0';
                break;
                case ALLEGRO_KEY_PAD_1:
                digito='1';
                break;
                case ALLEGRO_KEY_PAD_2:
                digito='2';
                break;
                case ALLEGRO_KEY_PAD_3:
                digito='3';
                break;
                case ALLEGRO_KEY_PAD_4:
                digito='4';
                break;
                case ALLEGRO_KEY_PAD_5:
                digito='5';
                break;
                case ALLEGRO_KEY_PAD_6:
                digito='6';
                break;
                case ALLEGRO_KEY_PAD_7:
                digito='7';
                break;
                case ALLEGRO_KEY_PAD_8:
                digito='8';
                break;
                case ALLEGRO_KEY_PAD_9:
                digito='9';
                break;
                case ALLEGRO_KEY_BACKSPACE:
                digito= 'b';
                break;
                case ALLEGRO_KEY_FULLSTOP:
                digito= '.';
                break;
                case ALLEGRO_KEY_ENTER:
                digito= '\0';
                break;
                case ALLEGRO_KEY_PAD_ENTER:
                digito= '\0';
                break;
                default:
                digito ='_';
            }
            if((digito !='b')&&(digito !='_')&&(i<=11)){
                ip[i] = digito;
                i++;
            }else if(i>0){
                i--;
                ip[i] = '_';
            }
            
        }
        al_flip_display();  
    }
}
int select_map(){
    al_draw_bitmap(hscs,0,0,0);
    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
    al_flip_display();
     char digito[2]={"00"};
     int final;
     digito[1]= '\0'; 
     while (1){
        ALLEGRO_EVENT evento;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.05);
 
        int tem_eventos = al_wait_for_event_until(eventsQueue, &evento, &timeout);
        
        if (tem_eventos && evento.type == ALLEGRO_EVENT_KEY_DOWN){
            al_play_sample(cursor, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            switch(evento.keyboard.keycode){
                    case ALLEGRO_KEY_0:
                    digito[0]='0';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_1:
                    digito[0]='1';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;            
                    case ALLEGRO_KEY_2:
                    digito[0]='2';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;        
                    case ALLEGRO_KEY_3:
                    digito[0]='3';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_4:
                    digito[0]='4';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_5:
                    digito[0]='5';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_6:
                    digito[0]='6';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;

                    case ALLEGRO_KEY_7:
                    digito[0]='7';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_8:
                    digito[0]='8';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_9:
                    digito[0]='9';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_PAD_0:
                    digito[0]='0';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_PAD_1:
                    digito[0]='1';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_PAD_2:
                    digito[0]='2';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_PAD_3:
                    digito[0]='3';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_PAD_4:
                    digito[0]='4';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_PAD_5:
                    digito[0]='5';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_PAD_6:
                    digito[0]='6';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_PAD_7:
                    digito[0]='7';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_PAD_8:
                    digito[0]='8';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_PAD_9:
                    digito[0]='9';
                    al_draw_bitmap(hscs,0,0,0);
                    al_draw_text(start, al_map_rgb(255, 255, 255), larg/2-40, 70, ALLEGRO_ALIGN_CENTRE, "DIGITE UM NUMERO ALEATORIO");
                    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, "_");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, (alt/2)+2, ALLEGRO_ALIGN_CENTRE, digito);
                    al_flip_display();
                    break;
                    case ALLEGRO_KEY_ENTER:
                    final = digito[0]-'0';
                    return final;     
                    break;
            }
        }    
    }
}  

void game_begin(int map_number, person jogador, int l_inic, int c_inic){
        if (map_number==0){
            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(mapa1,0,0,0);
            al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "3");
            al_flip_display();
            al_rest(1.0);

            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(mapa1,0,0,0);
            al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "2");
            al_flip_display();
            al_rest(1.0);

            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(mapa1,0,0,0);
            al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "1");
            al_flip_display();
            al_rest(1.0);

            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(mapa1,0,0,0);
            al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "FIGHT");
            al_flip_display();
            al_rest(1.0);
    
        }else if (map_number==1){
            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(mapa2,0,0,0);

            al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "3");
            al_flip_display();
            al_rest(1.0);

            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(mapa2,0,0,0);

            al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "2");
            al_flip_display();
            al_rest(1.0);

            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(mapa2,0,0,0);
            al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "1");
            al_flip_display();
            al_rest(1.0);

            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(mapa2,0,0,0);
            al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "FIGHT");
            al_flip_display();
            al_rest(1.0);
    
        }else{
            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(mapa3,0,0,0);
            al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "3");
            al_flip_display();
            al_rest(1.0);

            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(mapa3,0,0,0);
            al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "2");
            al_flip_display();
            al_rest(1.0);

            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(mapa3,0,0,0);
            al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "1");
            al_flip_display();
            al_rest(1.0);

            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(mapa3,0,0,0);
            al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "FIGHT");
            al_flip_display();
            al_rest(1.0);
        }
}

char move(){
    char digito = ' ';
    ALLEGRO_EVENT evento;
    ALLEGRO_TIMEOUT timeout;
    al_init_timeout(&timeout, 0.01);
    int tem_eventos = al_wait_for_event_until(eventsQueue, &evento, &timeout);
    if (tem_eventos&&evento.type == ALLEGRO_EVENT_KEY_DOWN){
        switch(evento.keyboard.keycode){
            case ALLEGRO_KEY_W:
                digito='w';
                break;
            case ALLEGRO_KEY_S:
                digito='s';
                break;            
            case ALLEGRO_KEY_A:
                digito='a';
                break;        
            case ALLEGRO_KEY_D:
                digito='d';
                break;
            case ALLEGRO_KEY_J:
                al_play_sample(lanca, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                digito='j';
                break;
            case ALLEGRO_KEY_K:
                al_play_sample(espada, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                digito='k';
                break;
        }
    }
    al_flush_event_queue(eventsQueue);
    return digito;           
}

void imprimi_jog(char mapa[alt][larg], person jogadores[max]){
    int i,j;
    for(i=0; i<alt;i++){
        for(j=0; j<larg; j++){
            if(mapa[i][j]!='0'){
                if((mapa[i][j]== 'a')&&(jogadores[0].life>0)){
                    if(jogadores[0].skin == 1){
                        if(jogadores[0].hori == 'w'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero1,64,96,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero1,0,96,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 's'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero1,0,0,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero1,64,0,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 'a'){
                           if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero1,0,32,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero1,64,32,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }     
                        }else if(jogadores[0].hori == 'd'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero1,0,64,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero1,64,64,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }
                    }else if(jogadores[0].skin == 2){
                        if(jogadores[0].hori == 'w'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero1,96,96,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero1,160,96,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 's'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero1,96,0,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero1,160,0,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 'a'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero1,96,32,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero1,160,32,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 'd'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero1,96,64,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero1,160,64,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }
                    }else if(jogadores[0].skin == 3){
                        if(jogadores[0].hori == 'w'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero1,288,224,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero1,352,224,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 's'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero1,288,128,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero1,352,128,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 'a'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero1,288,160,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero1,352,160,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 'd'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero1,288,192,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero1,352,192,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }
                    }else if(jogadores[0].skin == 4){
                        if(jogadores[0].hori == 'w'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero2,64,224,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero2,0,224,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 's'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero2,0,128,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero2,64,128,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 'a'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero2,0,160,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero2,64,160,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 'd'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero2,0,192,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero2,64,192,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }
                    }else if(jogadores[0].skin == 5){
                        if(jogadores[0].hori == 'w'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero2,192,228,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero2,256,228,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 's'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero2,192,128,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero2,256,128,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 'a'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero2,256,160,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero2,192,160,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 'd'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero2,192,192,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero2,256,192,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }
                    }else if(jogadores[0].skin == 6){
                        if(jogadores[0].hori == 'w'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero3,192,96,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero3,256,96,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 's'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero3,192,0,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero3,256,0,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 'a'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero3,192,32,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero3,256,32,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }else if(jogadores[0].hori == 'd'){
                            if(jogadores[0].pe==0){
                                al_draw_bitmap_region(hero3,192,64,32,32,j,i,0);
                                jogadores[0].pe = 1;
                            }
                            else if(jogadores[0].pe==1){
                                al_draw_bitmap_region(hero3,256,64,32,32,j,i,0);
                                jogadores[0].pe = 0;
                            }
                        }
                    }
                }
                
                
                
                
                
                
                
                else if((mapa[i][j]== 'b')&&(jogadores[1].life>0)){
                    if(jogadores[1].skin == 1){
                        if(jogadores[1].hori == 'w'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero1,64,96,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero1,0,96,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 's'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero1,0,0,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero1,64,0,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 'a'){
                           if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero1,0,32,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero1,64,32,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }     
                        }else if(jogadores[1].hori == 'd'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero1,0,64,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero1,64,64,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }
                    }else if(jogadores[1].skin == 2){
                        if(jogadores[1].hori == 'w'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero1,96,96,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero1,160,96,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 's'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero1,96,0,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero1,160,0,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 'a'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero1,96,32,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero1,160,32,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 'd'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero1,96,64,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero1,160,64,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }
                    }else if(jogadores[1].skin == 3){
                        if(jogadores[1].hori == 'w'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero1,288,224,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero1,352,224,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 's'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero1,288,128,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero1,352,128,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 'a'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero1,288,160,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero1,352,160,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 'd'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero1,288,192,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero1,352,192,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }
                    }else if(jogadores[1].skin == 4){
                        if(jogadores[1].hori == 'w'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero2,64,224,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero2,0,224,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 's'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero2,0,128,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero2,64,128,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 'a'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero2,0,160,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero2,64,160,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 'd'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero2,0,192,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero2,64,192,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }
                    }else if(jogadores[1].skin == 5){
                        if(jogadores[1].hori == 'w'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero2,192,224,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero2,256,224,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 's'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero2,192,128,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero2,256,128,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 'a'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero2,256,160,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero2,192,160,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 'd'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero2,192,192,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero2,256,192,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }
                    }else if(jogadores[1].skin == 6){
                        if(jogadores[1].hori == 'w'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero3,192,96,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero3,256,96,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 's'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero3,192,0,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero3,256,0,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 'a'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero3,192,32,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero3,256,32,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }else if(jogadores[1].hori == 'd'){
                            if(jogadores[1].pe==0){
                                al_draw_bitmap_region(hero3,192,64,32,32,j,i,0);
                                jogadores[1].pe = 1;
                            }
                            else if(jogadores[1].pe==1){
                                al_draw_bitmap_region(hero3,256,64,32,32,j,i,0);
                                jogadores[1].pe = 0;
                            }
                        }
                    }
                }
                
                
                
                
                
                
                else if((mapa[i][j]== 'c')&&(jogadores[2].life>0)){
                    if(jogadores[2].skin == 1){
                        if(jogadores[2].hori == 'w'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero1,64,96,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero1,0,96,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 's'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero1,0,0,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero1,64,0,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 'a'){
                           if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero1,0,32,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero1,64,32,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }     
                        }else if(jogadores[2].hori == 'd'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero1,0,64,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero1,64,64,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }
                    }else if(jogadores[2].skin == 2){
                        if(jogadores[2].hori == 'w'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero1,96,96,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero1,160,96,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 's'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero1,96,0,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero1,160,0,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 'a'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero1,96,32,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero1,160,32,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 'd'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero1,96,64,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero1,160,64,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }
                    }else if(jogadores[2].skin == 3){
                        if(jogadores[2].hori == 'w'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero1,288,224,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero1,352,224,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 's'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero1,288,128,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero1,352,128,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 'a'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero1,288,160,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero1,352,160,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 'd'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero1,288,192,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero1,352,192,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }
                    }else if(jogadores[2].skin == 4){
                        if(jogadores[2].hori == 'w'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero2,64,224,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero2,0,224,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 's'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero2,0,128,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero2,64,128,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 'a'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero2,0,160,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero2,64,160,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 'd'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero2,0,192,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero2,64,192,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }
                    }else if(jogadores[2].skin == 5){
                        if(jogadores[2].hori == 'w'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero2,192,224,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero2,256,224,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 's'){
                             if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero2,192,128,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero2,256,128,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 'a'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero2,256,160,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero2,192,160,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 'd'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero2,192,192,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero2,256,192,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }
                    }else if(jogadores[2].skin == 6){
                        if(jogadores[2].hori == 'w'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero3,192,96,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero3,256,96,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 's'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero3,192,0,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero3,256,0,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 'a'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero3,192,32,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero3,256,32,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }else if(jogadores[2].hori == 'd'){
                            if(jogadores[2].pe==0){
                                al_draw_bitmap_region(hero3,192,64,32,32,j,i,0);
                                jogadores[2].pe = 1;
                            }
                            else if(jogadores[2].pe==1){
                                al_draw_bitmap_region(hero3,256,64,32,32,j,i,0);
                                jogadores[2].pe = 0;
                            }
                        }
                    }
                }
                
                
                
                
                
                
                
                else if((mapa[i][j]== 'd')&&(jogadores[3].life>0)){
                    if(jogadores[3].skin == 1){
                        if(jogadores[3].hori == 'w'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero1,64,96,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero1,0,96,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 's'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero1,0,0,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero1,64,0,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 'a'){
                           if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero1,0,32,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero1,64,32,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }     
                        }else if(jogadores[3].hori == 'd'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero1,0,64,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero1,64,64,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }
                    }else if(jogadores[3].skin == 2){
                        if(jogadores[3].hori == 'w'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero1,96,96,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero1,160,96,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 's'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero1,96,0,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero1,160,0,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 'a'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero1,96,32,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero1,160,32,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 'd'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero1,96,64,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero1,160,64,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }
                    }else if(jogadores[3].skin == 3){
                        if(jogadores[3].hori == 'w'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero1,288,224,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero1,352,224,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 's'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero1,288,128,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero1,352,128,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 'a'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero1,288,160,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero1,352,160,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 'd'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero1,288,192,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero1,352,192,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }
                    }else if(jogadores[3].skin == 4){
                        if(jogadores[3].hori == 'w'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero2,64,224,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero2,0,224,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 's'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero2,0,128,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero2,64,128,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 'a'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero2,0,160,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero2,64,160,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 'd'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero2,0,192,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero2,64,192,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }
                    }else if(jogadores[3].skin == 5){
                        if(jogadores[3].hori == 'w'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero2,192,224,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero2,256,224,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 's'){
                             if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero2,192,128,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero2,256,128,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 'a'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero2,256,160,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero2,192,160,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 'd'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero2,192,192,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero2,256,192,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }
                    }else if(jogadores[3].skin == 6){
                        if(jogadores[3].hori == 'w'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero3,192,96,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero3,256,96,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 's'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero3,192,0,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero3,256,0,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 'a'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero3,192,32,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero3,256,32,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }else if(jogadores[3].hori == 'd'){
                            if(jogadores[3].pe==0){
                                al_draw_bitmap_region(hero3,192,64,32,32,j,i,0);
                                jogadores[3].pe = 1;
                            }
                            else if(jogadores[3].pe==1){
                                al_draw_bitmap_region(hero3,256,64,32,32,j,i,0);
                                jogadores[3].pe = 0;
                            }
                        }
                    }
                }
                
                
                
                
                
                
                
                
                else if((mapa[i][j]== 'e')&&(jogadores[4].life>0)){
                    if(jogadores[4].skin == 1){
                        if(jogadores[4].hori == 'w'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero1,64,96,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero1,0,96,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 's'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero1,0,0,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero1,64,0,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 'a'){
                           if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero1,0,32,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero1,64,32,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }     
                        }else if(jogadores[4].hori == 'd'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero1,0,64,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero1,64,64,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }
                    }else if(jogadores[4].skin == 2){
                        if(jogadores[4].hori == 'w'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero1,96,96,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero1,160,96,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 's'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero1,96,0,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero1,160,0,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 'a'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero1,96,32,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero1,160,32,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 'd'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero1,96,64,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero1,160,64,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }
                    }else if(jogadores[4].skin == 3){
                        if(jogadores[4].hori == 'w'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero1,288,224,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero1,352,224,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 's'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero1,288,128,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero1,352,128,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 'a'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero1,288,160,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero1,352,160,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 'd'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero1,288,192,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero1,352,192,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }
                    }else if(jogadores[4].skin == 4){
                        if(jogadores[4].hori == 'w'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero2,64,224,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero2,0,224,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 's'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero2,0,128,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero2,64,128,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 'a'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero2,0,160,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero2,64,160,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 'd'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero2,0,192,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero2,64,192,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }
                    }else if(jogadores[4].skin == 5){
                        if(jogadores[4].hori == 'w'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero2,192,224,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero2,256,224,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 's'){
                             if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero2,192,128,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero2,256,128,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 'a'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero2,256,160,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero2,192,160,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 'd'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero2,192,192,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero2,256,192,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }
                    }else if(jogadores[4].skin == 6){
                        if(jogadores[4].hori == 'w'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero3,192,96,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero3,256,96,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 's'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero3,192,0,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero3,256,0,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 'a'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero3,192,32,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero3,256,32,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }else if(jogadores[4].hori == 'd'){
                            if(jogadores[4].pe==0){
                                al_draw_bitmap_region(hero3,192,64,32,32,j,i,0);
                                jogadores[4].pe = 1;
                            }
                            else if(jogadores[4].pe==1){
                                al_draw_bitmap_region(hero3,256,64,32,32,j,i,0);
                                jogadores[4].pe = 0;
                            }
                        }
                    }
                }
                
                
                
                
                
                
                
                
                else if((mapa[i][j]== 'f')&&(jogadores[5].life>0)){
                    if(jogadores[5].skin == 1){
                        if(jogadores[5].hori == 'w'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero1,64,96,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero1,0,96,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 's'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero1,0,0,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero1,64,0,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 'a'){
                           if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero1,0,32,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero1,64,32,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }     
                        }else if(jogadores[5].hori == 'd'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero1,0,64,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero1,64,64,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }
                    }else if(jogadores[5].skin == 2){
                        if(jogadores[5].hori == 'w'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero1,96,96,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero1,160,96,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 's'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero1,96,0,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero1,160,0,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 'a'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero1,96,32,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero1,160,32,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 'd'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero1,96,64,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero1,160,64,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }
                    }else if(jogadores[5].skin == 3){
                        if(jogadores[5].hori == 'w'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero1,288,224,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero1,352,224,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 's'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero1,288,128,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero1,352,128,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 'a'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero1,288,160,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero1,352,160,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 'd'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero1,288,192,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero1,352,192,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }
                    }else if(jogadores[5].skin == 4){
                        if(jogadores[5].hori == 'w'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero2,64,224,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero2,0,224,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 's'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero2,0,128,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero2,64,128,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 'a'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero2,0,160,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero2,64,160,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 'd'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero2,0,192,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero2,64,192,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }
                    }else if(jogadores[5].skin == 5){
                        if(jogadores[5].hori == 'w'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero2,192,224,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero2,256,224,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 's'){
                             if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero2,192,128,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero2,256,128,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 'a'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero2,256,160,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero2,192,160,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 'd'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero2,192,192,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero2,256,192,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }
                    }else if(jogadores[5].skin == 6){
                        if(jogadores[5].hori == 'w'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero3,192,96,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero3,256,96,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 's'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero3,192,0,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero3,256,0,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 'a'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero3,192,32,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero3,256,32,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }else if(jogadores[5].hori == 'd'){
                            if(jogadores[5].pe==0){
                                al_draw_bitmap_region(hero3,192,64,32,32,j,i,0);
                                jogadores[5].pe = 1;
                            }
                            else if(jogadores[5].pe==1){
                                al_draw_bitmap_region(hero3,256,64,32,32,j,i,0);
                                jogadores[5].pe = 0;
                            }
                        }
                    }
                }            
            }
        }
    }   
}

void attack(int num_jogadores, person jogadores[max], char mapa[alt][larg], int id_local, int in_mapa){
    int j=0;
    int i=0;
    
        
        //control_animation = blink();
        for (i=0; i<num_jogadores;i++){
            if (jogadores[i].ataque == ' '){
                
            }
            else if(jogadores[i].ataque == 'k'){//espada1
                if (jogadores[i].hori=='w'){
                    al_draw_bitmap_region(ataque_s, 216,248,36,52,jogadores[i].x-19,jogadores[i].y-25,0);
                }
                else if (jogadores[i].hori=='d'){
                    al_draw_bitmap_region(ataque_a,856,217,49,34,jogadores[i].x+4,jogadores[i].y-19,0);
                }
                else if (jogadores[i].hori=='a'){
                    al_draw_bitmap_region(ataque_d,248,711,54,33,jogadores[i].x-8,jogadores[i].y+19,0);
                }
                else if (jogadores[i].hori=='s'){
                    al_draw_bitmap_region(ataque_w, 709,856,33,52,jogadores[i].x+19,jogadores[i].y+5, 0);  
                }
            }
            else if(jogadores[i].ataque == 'j'){//lança1
                if (jogadores[i].hori=='w'){
                        al_draw_bitmap_region(ataque_w,851,1061, 27 ,62,jogadores[i].x-20,jogadores[i].y - 62 ,0);
                }
                else if (jogadores[i].hori=='d'){
                        al_draw_bitmap_region(ataque_d,33,850,66,24,jogadores[i].x+32,jogadores[i].y-2,0);
                }
                else if (jogadores[i].hori=='a'){
                        al_draw_bitmap_region(ataque_a,1056,80,68,26,jogadores[i].x-68,jogadores[i].y+20,0);
                }
                else if (jogadores[i].hori=='s'){
                        al_draw_bitmap_region(ataque_s, 81, 13, 30, 79,jogadores[i].x+20,jogadores[i].y+32,0);
                }
            }
        }
        imprimi_status(jogadores[id_local]);
        al_flip_display();
        imprimi_mapa(in_mapa);
        imprimi_jog(mapa,jogadores);
        imprimi_status(jogadores[id_local]);
        
    for (i=0; i<num_jogadores;i++){
        if(jogadores[i].ataque == 'k'){//espada2
            if (jogadores[i].hori=='w'){
                    al_draw_bitmap_region(ataque_s,405,240,71,57,jogadores[i].x-32,jogadores[i].y-25,0);
            }
            else if (jogadores[i].hori=='d'){
                    al_draw_bitmap_region(ataque_a,859,406,52,71,jogadores[i].x-2,jogadores[i].y-32,0);
            }
            else if (jogadores[i].hori=='a'){
                al_draw_bitmap_region(ataque_d,240,486,58,69,jogadores[i].x-26,jogadores[i].y-8,0);
            }
            else if (jogadores[i].hori=='s'){
                al_draw_bitmap_region(ataque_w, 485,856,70,56,jogadores[i].x,jogadores[i].y,0);
            }
        }
        else if(jogadores[i].ataque == 'j'){//lanca4
            if (jogadores[i].hori=='w'){
                    al_draw_bitmap_region(ataque_w,274,972,32,73,jogadores[i].x,jogadores[i].y-73,0);
            }
            else if (jogadores[i].hori=='d'){
                    al_draw_bitmap_region(ataque_d,103,273,74,28,jogadores[i].x+32,jogadores[i].y,0);
            }
            else if (jogadores[i].hori=='a'){
                    al_draw_bitmap_region(ataque_a,969,848,76,28,jogadores[i].x-76,jogadores[i].y,0);
            }
            else if (jogadores[i].hori=='s'){
                    al_draw_bitmap_region(ataque_s, 658,93,31,85,jogadores[i].x,jogadores[i].y+32,0);           
            }
        }
    }
   
    al_flip_display();
    imprimi_mapa(in_mapa);
    imprimi_jog(mapa,jogadores);
    imprimi_status(jogadores[id_local]);
    for (i=0; i<num_jogadores;i++){
        if(jogadores[i].ataque == 'k'){//espada5
            if (jogadores[i].hori=='w'){
                al_draw_bitmap_region(ataque_s,99,451,49,66,jogadores[i].x,jogadores[i].y-40,0);    
            }
            else if (jogadores[i].hori=='d'){
                al_draw_bitmap_region(ataque_a,633,100,65,48,jogadores[i].x-22,jogadores[i].y+10,0);               
            }
            else if (jogadores[i].hori=='a'){
                al_draw_bitmap_region(ataque_d,458,811,62,49,jogadores[i].x-35,jogadores[i].y-23,0);
            }
            else if (jogadores[i].hori=='s'){
                al_draw_bitmap_region(ataque_w,812,634,44,62,jogadores[i].x-20,jogadores[i].y-4,0);               
            }
        }
        else if(jogadores[i].ataque == 'j'){//lanca5
            if (jogadores[i].hori=='w'){
                al_draw_bitmap_region(ataque_w,84,969,48,61,jogadores[i].x+3,jogadores[i].y-61,0);           
            }
            else if (jogadores[i].hori=='d'){
                al_draw_bitmap_region(ataque_d,126,79,58,24,jogadores[i].x+32,jogadores[i].y,0);       
            }
            else if (jogadores[i].hori=='a'){
                al_draw_bitmap_region(ataque_a,969,848,60,24,jogadores[i].x-60,jogadores[i].y,0);
            }
            else if (jogadores[i].hori=='s'){
                al_draw_bitmap_region(ataque_s,849,105,31,70,jogadores[i].x,jogadores[i].y+32,0);       
            }
        }
    }
   
    al_flip_display();  
    imprimi_mapa(in_mapa);
    imprimi_jog(mapa,jogadores);
    imprimi_status(jogadores[id_local]);
    for (i=0; i<num_jogadores;i++){
        if(jogadores[i].ataque == 'k'){//espada6
            if (jogadores[i].hori=='w'){
                al_draw_bitmap_region(ataque_s,315,485,23,35,jogadores[i].x+32,jogadores[i].y-3,0);
            }
            else if (jogadores[i].hori=='d'){
                al_draw_bitmap_region(ataque_a,634,316,29,23,jogadores[i].x-3,jogadores[i].y+32,0);
            }
            else if (jogadores[i].hori=='a'){
                al_draw_bitmap_region(ataque_d,484,621,35,24,jogadores[i].x-3,jogadores[i].y-26,0);
            }
            else if (jogadores[i].hori=='s'){
                al_draw_bitmap_region(ataque_w,621,632,24,36,jogadores[i].x-26,jogadores[i].y+4,0);  
            }  
        }
        else if(jogadores[i].ataque == 'j'){//lanca6
            if (jogadores[i].hori=='w'){
                    al_draw_bitmap_region(ataque_w,855,775,21,38,jogadores[i].x+3,jogadores[i].y-38,0);    
            }
            else if (jogadores[i].hori=='d'){
                    al_draw_bitmap_region(ataque_d,343,850,38,20,jogadores[i].x+32,jogadores[i].y,0);      
            }
            else if (jogadores[i].hori=='a'){
                    al_draw_bitmap_region(ataque_a,775,87,34,18,jogadores[i].x-34,jogadores[i].y+10,0);      
            }
            else if (jogadores[i].hori=='s'){
                    al_draw_bitmap_region(ataque_s,87,335,20,43,jogadores[i].x+3,jogadores[i].y+32,0);     
            }
        }
    }
    
    al_flip_display();    
    blinkTimer(); 
    imprimi_mapa(in_mapa);
    imprimi_jog(mapa,jogadores);
    imprimi_status(jogadores[id_local]);
}
