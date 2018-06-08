#include "libSocket/client.h"
#include "libAllegro/AllegroCore.h"
#include "libSocket/server.h"
#define max 6
#define tam 2240
typedef struct{
    int life;
    int x;
    int y;
    char hori;
    char ataque;
}person;
typedef struct{
    int x;
    int y;
    int id;
}evento;
void att_mapa(char mapa[tam][tam],person jogadores[max], int quant_jogadores){
    int i,j, ind;
    bool tem_jog;
    for(i=0;i<tam;i++){
        for(j=0;j<tam;j++){
            tem_jog = false;
            for(ind=0;ind<quant_jogadores;ind++){
                if((jogadores[ind].y == i)&&(jogadores[ind].x == j)){
                    mapa[i][j] = (ind +'a');
                    tem_jog = true;
                }
                if(tem_jog==false){
                    mapa[i][j] = '0';
                }
            }
        }
    }
}

void att_camera(char mapa[tam][tam], person jogador, int *lin_ini ,int *col_ini){
    //deslocamento dos indices iniciais da matriz que vai ser a janela
    if(jogador.hori == 'w'){
        if(jogador.x <=(*col_ini + 100)){
            *col_ini--;
        }
        if(jogador.y <=(*lin_ini +100)){
            *lin_ini--;
        }
    }else if(jogador.hori == 's'){
        if(jogador.x >=(*col_ini + 988)){
            *col_ini++;
        }
        if(jogador.y >=(*lin_ini + 588)){
            *lin_ini++;
        }
    }else if(jogador.hori == 'a'){
        if(jogador.x <=(*col_ini + 100)){
            *col_ini--;
        }
        if(jogador.y >=(*lin_ini +588)){
            *lin_ini++;
        }
    }else {
        if(jogador.x >=(*col_ini + 988)){
            *col_ini++;
        }
        if(jogador.y <=(*lin_ini +100)){
            *lin_ini--;
        }
    }
}
void anali_jog_janela(char mapa[tam][tam],evento ter_players[max], int ini_lin, int ini_col,int *ind){
    int im, jm;
    for(im=0; im<alt;im++){
        for(jm = 0; jm<larg;jm++){
            if(mapa[im+alt][jm+larg]!='0'){
                if(mapa[im+alt][jm+larg]!='a'){
                    ter_players[*ind].id = 0;
                    ter_players[*ind].x = jm;
                    ter_players[*ind].y = im;
                    *ind++;
                }else if(mapa[im+alt][jm+larg]!='b'){
                    ter_players[*ind].id = 1;
                    ter_players[*ind].x = jm;
                    ter_players[*ind].y = im;
                    *ind++;
                }else if(mapa[im+alt][jm+larg]!='c'){
                    ter_players[*ind].id = 2;
                    ter_players[*ind].x = jm;
                    ter_players[*ind].y = im;
                    *ind++;
                }else if(mapa[im+alt][jm+larg]!='d'){
                    ter_players[*ind].id = 3;
                    ter_players[*ind].x = jm;
                    ter_players[*ind].y = im;
                    *ind++;
                }else if(mapa[im+alt][jm+larg]!='e'){
                    ter_players[*ind].id = 4;
                    ter_players[*ind].x = jm;
                    ter_players[*ind].y = im;
                    *ind++;
                }else if(mapa[im+alt][jm+larg]!='f'){
                    ter_players[*ind].id = 5;
                    ter_players[*ind].x = jm;
                    ter_players[*ind].y = im;
                    *ind++;
                }
            }
        }
    }
}
bool mov_valid(char mov, person jogadores[max], int num_jogadores, int meu_id){
    int ind;
    if(mov == 'w'){
        for(ind=0;ind<num_jogadores;ind++){
            if(ind!=meu_id){
                if((jogadores[ind].x == jogadores[meu_id].x)&&(jogadores[ind].y == (jogadores[meu_id].y-1))){
                    return false;
                }
            }
        }
        return true;
    }else if(mov == 's'){
        for(ind=0;ind<num_jogadores;ind++){
            if(ind!=meu_id){
                if((jogadores[ind].x == jogadores[meu_id].x)&&(jogadores[ind].y == (jogadores[meu_id].y+1))){
                    return false;
                }
            }
        }
        return true;
    }else if(mov == 'a'){
        for(ind=0;ind<num_jogadores;ind++){
            if(ind!=meu_id){
                if((jogadores[ind].x == (jogadores[meu_id].x-1))&&(jogadores[ind].y == (jogadores[meu_id].y))){
                    return false;
                }
            }
        }
        return true;
    }else if(mov == 'd'){
        for(ind=0;ind<num_jogadores;ind++){
            if(ind!=meu_id){
                if((jogadores[ind].x == (jogadores[meu_id].x+1))&&(jogadores[ind].y == (jogadores[meu_id].y))){
                    return false;
                }
            }
        }
        return true;
    }
}
int main(){
    int x_close=9;
    coreInit();
    windowInit(larg, alt, "PUNCH KILL");
    inputInit();
    fontInit();
    loadGraphics();
    /*
    al_draw_bitmap(hscs, 0, 0, 0);
    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, 70, ALLEGRO_ALIGN_CENTRE, "PUNCH KILL");
    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 220, ALLEGRO_ALIGN_CENTRE, "Start Game");
    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 420, ALLEGRO_ALIGN_CENTRE, "Credits");
    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 620, ALLEGRO_ALIGN_CENTRE, "Quit Game");
    al_flip_display();
    x_close = digitemenu();
    if(x_close==0){
        return 0;
    }
    else if(x_close==1){
        
    }
    else if(x_close==2){
        //creditos
        int x=0;
        while(x<720){// (tamanho da imagem mais 720 ) X 1120 (ultima parte eh fundo preto)
          imagem = al_load_bitmap("fundocreditos.jpg");
          al_draw_bitmap(imagem, x , 0, 0);
          al_flip_display();
          al_rest(0.1);
          x+=10;
        }
        if()//se chegar no fim da imagem reseta
        }
        //colocar o press esc to exit
        else if(x_close==3){
            return 0;
        }
    }
    else if(x_close==3){
        return 0;
    }*/

    char ip[12]={"__________"};
    //conexão com o servidor
    int ret_conec, id_local, ind;
    do{
        digite_ip(ip);
        ret_conec = connectToServer(ip);
        if(ret_conec==SERVER_UP){
            printf("conexao estabelecida!\n");
            recvMsgFromServer(&id_local,WAIT_FOR_IT);
        }else{
            printf("conexao nao estabelecida!\n");
            for(ind = 0; ind<11;ind++){
                ip[ind] = '_';
            }
            if(ret_conec== SERVER_CLOSED){
                printf("servidor fechado\n");
            }
        }
    }while(ret_conec!=SERVER_UP);
    printf("\n%i\n", ret_conec);
    //espera o servidor dar o sinal que a sala foi fechada
    char status_send, status_recb;
    int num_jogadores;
    recvMsgFromServer(&status_recb, WAIT_FOR_IT);
    if(status_recb == 'm'){
        recvMsgFromServer(&num_jogadores, WAIT_FOR_IT);
        printf("Partida iniciada com apenas(%i jogadores)\n", num_jogadores);
    }else{
        printf("Partida iniciada com sala cheia\n");
    }
    
    //recebe as posições iniciais dos jogadores
    person jogadores[max];
    recvMsgFromServer(jogadores,WAIT_FOR_IT);

    //distribui os jogadores por uma matriz que representa o mapa do campo
    char mapa[tam][tam];
    memset(mapa,'0', sizeof(mapa));
    att_mapa(mapa,jogadores, num_jogadores);

    //timer para o inicio
    int ind_f;
    for(ind_f = 0;ind_f <5; ind_f++){
        printf("a partida vai começar em (%i) segundos\n", (5 -ind_f));
        al_rest(1);     
    }

    //variaveis para a janela de exibição
    //char janela_p[alt][larg];
    int ini_lin, ini_col;

    //setagem inicial do inicio da janela nas matrizes
    //como inicialmente todos os jogadores estão olhando para frente
    ini_lin =(jogadores[id_local].y - 588);
    if(ini_lin<0){
        ini_lin = 0;
    }else if(ini_lin>alt){
        ini_lin = alt;
    }
    ini_col = (jogadores[id_local].x - 545);
    if(ini_col<0){
        ini_col = 0;
    }else if(ini_col>larg){
        ini_col = larg;
    }
    // laço da partida
    bool vivo = true;
    char caracter;
    evento ter_players[max];
    int num_visi, ind_vivo;
    while(vivo ==true){

        startTimer();
        //coleta a entrada do cliente para a rodada
        caracter = getch();
        if(caracter == 'W'||caracter == 'w'){
            if((jogadores[id_local].y>0)&&(mov_valid('w',jogadores,num_jogadores,id_local))){
                jogadores[id_local].y--;
                jogadores[id_local].hori = 'w';
            }
        }else if(caracter == 'S'||caracter == 's'){
            if((jogadores[id_local].y<(tam-32))&&(mov_valid('s',jogadores,num_jogadores,id_local))){
                jogadores[id_local].y++;
                jogadores[id_local].hori = 's';
            }
        }else if(caracter == 'A'||caracter == 'a'){
            if((jogadores[id_local].x>0)&&(mov_valid('a',jogadores,num_jogadores,id_local))){
                jogadores[id_local].x--;
                jogadores[id_local].hori = 'a';
            }
        }else if(caracter == 'D'||caracter == 'd'){
            if((jogadores[id_local].x<(tam-32))&&(mov_valid('d',jogadores,num_jogadores,id_local))){
                jogadores[id_local].x++;
                jogadores[id_local].hori = 'd';
            }
        }

        if((caracter == 'j')||(caracter == 'J')){
            jogadores[id_local].ataque = '1';
        }else if((caracter == 'k')||(caracter == 'K')){
            jogadores[id_local].ataque = '2';
        }else if((caracter == 'l')||(caracter == 'L')){
            jogadores[id_local].ataque = '3';
        }else{
            jogadores[id_local].ataque = '0';
        }

        // atualizando a posição da camera
        att_camera(mapa, jogadores[id_local],&ini_lin,&ini_col);

        // pegando do mapa de jogadores todo a parte que sera exibida pela na janela
        num_visi= 0;
        anali_jog_janela(mapa, ter_players, ini_lin,ini_col,&num_visi);

        //codigo da allegro para exibir a tela atual...

        //envia minhas alterações para o server e recebo as alterações de todos os jogadores
        sendMsgToServer(&jogadores[id_local], sizeof(person));
        recvMsgFromServer(jogadores,WAIT_FOR_IT);
        if(jogadores[id_local].life == 0){
            printf("YOU-DIED\n");
            vivo = false;
        }
        printf("\n");
        printf("coordenadas(x %i,y %i)\n",jogadores[id_local].x, jogadores[id_local].y);
        printf("inicio da camera(x %i,y %i)\n",ini_col,ini_lin);
        //atualiza a matriz com as novas posições recebidas do server
        att_mapa(mapa,jogadores, num_jogadores);
        
        //verifiação de se o cliente ainda está vivo
        if(jogadores[id_local].life == 0){
            vivo = false;
        }
        
        // verificação de se a partida acabou e recebe que id ganhou
        recvMsgFromServer(&status_recb, WAIT_FOR_IT);
        if(status_recb == '1'){
            recvMsgFromServer(&ind_vivo, WAIT_FOR_IT);
            printf("partida encerrada\n");
            printf("O jogador %i venceu\n", (ind_vivo+1));
        }
        FPSLimit();
        
    }
    return 0;
}
