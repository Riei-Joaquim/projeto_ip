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
}janela;
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
void anali_em_janela(char mapa[tam][tam],janela localizados[max], int ini_lin, int ini_col){
    int im, jm, ind = 0;
    /*nova ideia para como coletar a janela no cliente da matriz campo
    for(im=ini_lin; im<(ini_lin +alt);im++){
        for(jm = ini_col; jm<(ini_col + larg);jm++){
            if(mapa[im][jm]!='0'){
                if(mapa[im][jm]!='a'){
                    localizados[ind].id = 0;
                    localizados[ind].x = 
                    localizados[ind].y = 
                }else if(mapa[im][jm]!='0'){

                }else if(mapa[im][jm]!='0'){
                    
                }else if(mapa[im][jm]!='0'){
                    
                }else if(mapa[im][jm]!='0'){
                    
                }
            }
        }
    }*/
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
    /*
    windowInit(larg, alt, "PUNCH KILL");
    inputInit();
    fontInit();
    loadGraphics();
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
        //jogo
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
    }*/
    //conexão com o servidor
    char ip[12];
    int ret_conec, id_local;
    do{
        printf("digite seu IP: ");
        scanf(" %s", ip);
        ret_conec = connectToServer(ip);
        if(ret_conec==SERVER_UP){
            printf("conexao estabelecida!\n");
            recvMsgFromServer(&id_local,WAIT_FOR_IT);
        }else{
            printf("conexao nao estabelecida!\n");
        }
    }while(ret_conec!=SERVER_UP);

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
    ini_col = (jogadores[id_local].x - 545);

    // laço da partida
    bool vivo = true;
    char caracter;
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
        //extrai_janela(mapa, janela_p,ini_lin, ini_col);

        //codigo da allegro para exibir a tela atual...

        //envia minhas alterações para o server e recebo as alterações de todos os jogadores
        sendMsgToServer(&jogadores[id_local], sizeof(person));
        recvMsgFromServer(jogadores,WAIT_FOR_IT);
        if(jogadores[id_local].life == 0){
            printf("YOU-DIED\n");
            vivo = false;
        }
        printf("coordenadas(%i,%i)\n",jogadores[id_local].x, jogadores[id_local].y);
        
        //atualiza a matriz com as novas posições recebidas do server
        att_mapa(mapa,jogadores, num_jogadores);
        
        //verifiação de se o cliente ainda está vivo
        if(jogadores[id_local].life == 0){
            vivo = false;
        }
        FPSLimit();
    }
    return 0;
}
