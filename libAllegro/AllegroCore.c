#include "AllegroCore.h"


bool coreInit(){
    //modules and add-ons initialization
	if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar Allegro.\n");
        return false;
    }

    if (!al_init_image_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        return false;
    }

    if (!al_init_font_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_font.\n");
        return false;
    }

    if (!al_init_ttf_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return false;
    }

    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_primitives.\n");
        return false;
    }


    eventsQueue = al_create_event_queue();
    if (!eventsQueue)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        return false;
    }

 	

    return true;
}

bool windowInit(int W, int H, char title[])
{
    //window and event queue creation
    main_window = al_create_display(W, H);
    if (!main_window)
    {
        fprintf,(stderr, "Falha ao criar janela.\n");
        return false;
    }
    al_set_window_title(main_window, title);

    //registra janela na fila de eventos
    al_register_event_source(eventsQueue, al_get_display_event_source(main_window));

    return true;
}

bool inputInit()
{
	/*------------------------------MOUSE--------------------------------*/
	//Inicializa Mouse
	if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(main_window);
        return false;
    }

    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(main_window, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(main_window);
        return false;
    }
    /*------------------------------MOUSE--------------------------------*/

    /*------------------------------TECLADO------------------------------*/
    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return false;
    }

    /*------------------------------TECLADO------------------------------*/


    //Registra mouse e teclado na fila de eventos
    al_register_event_source(eventsQueue, al_get_mouse_event_source());
    al_register_event_source(eventsQueue, al_get_keyboard_event_source());

    return true;
}

bool fontInit()
{
    /*------------------------------FONTE--------------------------------*/
    start = al_load_font("Resources/Fonts/pressStart.ttf", 20, 0);
    if (!start)
    {
        fprintf(stderr, "Falha ao carregar \"pressStart.ttf\".\n");
        return false;
    }
    
    starthigh = al_load_font("Resources/Fonts/pressStart.ttf", 30, 0);
    if (!start)
    {
        fprintf(stderr, "Falha ao carregar \"pressStart.ttf\".\n");
        return false;
    }

    ubuntu = al_load_font("Resources/Fonts/pressStart.ttf", 50, 0);
    if (!ubuntu)
    {
        fprintf(stderr, "Falha ao carregar \"Ubuntu-R.ttf\".\n");
        return false;
    }

    return true;
}

void allegroEnd()
{
    al_destroy_display(main_window);
    al_destroy_event_queue(eventsQueue);
}



void startTimer()
{
    startingTime = al_get_time();
}

double getTimer()
{
    return al_get_time() - startingTime;
}

void FPSLimit()
{
	if (getTimer() < 1.0/FPS)
    {
        al_rest((1.0 / FPS) - getTimer());
    }
}


bool loadGraphics()
{
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

    return true;
}
int digitemenu(){
    int posicao=0;
    while (1){
        ALLEGRO_EVENT evento;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.05);
 
        int tem_eventos = al_wait_for_event_until(eventsQueue, &evento, &timeout);
        
        if (tem_eventos && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            allegroEnd();
            printf("Janela fechada\n");
            return 0;
        }
        if(tem_eventos && evento.type == ALLEGRO_EVENT_KEY_DOWN){
            if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN&& posicao == 0){
                posicao++;
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 220, ALLEGRO_ALIGN_CENTRE, "Start Game");
                al_draw_text(start, al_map_rgb(255, 255, 30), (larg/2)-40, 420, ALLEGRO_ALIGN_CENTRE, "Credits");
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 620, ALLEGRO_ALIGN_CENTRE, "Quit Game");
                al_flip_display();
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN && posicao == 1){
                posicao++;
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 220, ALLEGRO_ALIGN_CENTRE, "Start Game");
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 420, ALLEGRO_ALIGN_CENTRE, "Credits");
                al_draw_text(start, al_map_rgb(255, 255, 30), (larg/2)-40, 620, ALLEGRO_ALIGN_CENTRE, "Quit Game");
                al_flip_display();

            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_UP&& posicao == 2){
                posicao--;
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 220, ALLEGRO_ALIGN_CENTRE, "Start Game");
                al_draw_text(start, al_map_rgb(255, 255, 30), (larg/2)-40, 420, ALLEGRO_ALIGN_CENTRE, "Credits");
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 620, ALLEGRO_ALIGN_CENTRE, "Quit Game");
                al_flip_display();
 
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_UP&& posicao == 1){
                posicao--;
                al_draw_text(start, al_map_rgb(255, 255, 30), (larg/2)-40, 220, ALLEGRO_ALIGN_CENTRE, "Start Game");
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 420, ALLEGRO_ALIGN_CENTRE, "Credits");
                al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 620, ALLEGRO_ALIGN_CENTRE, "Quit Game");
                al_flip_display();
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_ENTER){
                if(posicao==0){
                    printf("O JOGO COMECOU\n");
                    return 1;
                }
                else if(posicao==1){
                    printf("CREDITOS\n");
                    return 2;
                }
                else if(posicao==2){
                    printf("GAME QUITADO\n");
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
    int mat_posicao[2][3] = {1,2,3,4,5,6};
    int x = 0, y = 0;
    int key=1;
    int n = 1;
    while (1){
        startTimer();
        ALLEGRO_EVENT evento;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.05);
 
        int tem_eventos = al_wait_for_event_until(eventsQueue, &evento, &timeout);
        
        /*while(n--){
            
            
            
            al_draw_scaled_bitmap(actor1_select,87,162,100,105,303,378,216,216,0);
            al_draw_scaled_bitmap(actor2,343,162,100,105,559,378,216,216,0);
            al_draw_scaled_bitmap(actor3,599,162,100,105,815,378,216,216,0);
            al_draw_scaled_bitmap(actor4,87,458,100,105,303,674,216,216,0);
            al_draw_scaled_bitmap(actor5,343,458,100,105,559,674,216,216,0);
            al_draw_scaled_bitmap(actor6,599,458,100,105,815,674,216,216,0);
            al_flip_display();
        }   */
        //printf("%i %i\n", evento.mouse.x, evento.mouse.y);
        if(tem_eventos && evento.type == ALLEGRO_EVENT_KEY_DOWN){
            if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN && x == 0){
                
                x++;
                
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_UP && x == 1){
                
                x--;
                
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_RIGHT && y != 2){
                
                y++;
                
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_LEFT && y != 0){
                
                y--;
                
            }
            else if(evento.keyboard.keycode == ALLEGRO_KEY_ENTER){
                if(mat_posicao[x][y]==1){
                    printf("ACTOR 1");
                    return 1;
                }
                else if(mat_posicao[x][y]==2){
                    printf("ACTOR 2");
                    return 2;
                }
                else if(mat_posicao[x][y]==3){
                    printf("ACTOR 3");
                    return 3;
                }
                else if(mat_posicao[x][y]==4){
                    printf("ACTOR 4");
                    return 4;
                }
                else if(mat_posicao[x][y]==5){
                    printf("ACTOR 5");
                    return 5;
                }
                else if(mat_posicao[x][y]==6){
                    printf("ACTOR 6");
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
        al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "SELECT YOUR FIGHTER");
        al_flip_display();
        al_rest(0.05);
        al_draw_text(ubuntu, al_map_rgb(205, 205, 205), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "SELECT YOUR FIGHTER");
        al_flip_display();
        al_rest(0.05);
        al_draw_text(ubuntu, al_map_rgb(150, 150, 150), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "SELECT YOUR FIGHTER");
        al_flip_display();
        al_rest(0.05);
        al_draw_text(ubuntu, al_map_rgb(205, 205, 205), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "SELECT YOUR FIGHTER");
        al_flip_display();
        al_rest(0.05);
        al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2), 50, ALLEGRO_ALIGN_CENTRE, "SELECT YOUR FIGHTER");
        al_flip_display();
        FPSLimit();
    }
}    
