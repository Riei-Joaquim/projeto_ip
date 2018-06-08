#include "libSocket/server.h"
#include "libAllegro/AllegroCore.h"

#define max 6
#define tam 2240
typedef struct{
    int life;
    int x;
    int y;
    char hori;
    char ataque;
}person;
void sort_posi(int *vetor){
    int a;
    for(a=0; a<6;a++){
        vetor[a]=rand()%tam;
    }
}
void veri_hits_lanca(person jogadores[max], int id_ana, int num_jogadores){
    int ind, distx, disty;
    if(jogadores[id_ana].hori =='w'){
        for(ind=0;ind<num_jogadores;ind++){
           if(ind!=id_ana){
               distx = (jogadores[id_ana].x -jogadores[ind].x);
               disty = (jogadores[id_ana].y -jogadores[ind].y);
               if(((distx >-32)&&(distx<32))&&(disty<64)){
                   jogadores[ind].life--;
                   if(jogadores[ind].y>64){
                       jogadores[ind].y -= 64;
                   }else{
                       jogadores[ind].y = 0;
                   }
                   
                   if(jogadores[ind].y <32){
                       jogadores[ind].life = 0;
                       printf("morte nos espinhos\n");
                   }
               }
           } 
        }
    }else if(jogadores[id_ana].hori =='s'){
        for(ind=0;ind<num_jogadores;ind++){
           if(ind!=id_ana){
               distx = (jogadores[id_ana].x -jogadores[ind].x);
               disty = (jogadores[id_ana].y -jogadores[ind].y);
               if(((distx >-32)&&(distx<32))&&(disty> -64)){
                   jogadores[ind].life--;
                   if(jogadores[ind].y <(tam*2-96){
                       jogadores[ind].y += 64;
                   }else{
                       jogadores[ind].y  = (tam*2 -32);
                   }
                      
                   if(jogadores[ind].y >(tam*2 -32)){
                       jogadores[ind].life = 0;
                       printf("morte nos espinhos\n");
                   }
               }
           } 
        }
    }else if(jogadores[id_ana].hori =='d'){
        for(ind=0;ind<num_jogadores;ind++){
           if(ind!=id_ana){
               distx = (jogadores[id_ana].x -jogadores[ind].x);
               disty = (jogadores[id_ana].y -jogadores[ind].y);
               if(((disty >-32)&&(disty<32))&&(distx> 64)){
                   jogadores[ind].life--;
                   if(jogadores[ind].x <(tam*2 - 96)){
                       jogadores[ind].x +=64;
                   }else{
                       jogadores[ind].x = (tam*2 - 32);
                   }
                   
                   if(jogadores[ind].x >(alt*2 -32)){
                       jogadores[ind].life = 0;
                       printf("morte nos espinhos\n");
                   }
                   
               }
           } 
        }
    }else{
        for(ind=0;ind<num_jogadores;ind++){
           if(ind!=id_ana){
               distx = (jogadores[id_ana].x -jogadores[ind].x);
               disty = (jogadores[id_ana].y -jogadores[ind].y);
               if(((disty >-32)&&(disty<32))&&(distx>-64)){
                   jogadores[ind].life--;
                   if(jogadores[ind].x >64){
                       jogadores[ind].x -=64;
                   }else{
                       jogadores[ind].x = 0;
                   }
                   
                   if((jogadores[ind].x <32)){
                       jogadores[ind].life = 0;
                       printf("morte nos espinhos\n");
                   }
               }
           } 
        }
    }
}

void veri_hits_esp(person jogadores[max], int id_ana, int num_jogadores){
    int ind, distx, disty;
    if(jogadores[id_ana].hori =='w'){
        for(ind=0;ind<num_jogadores;ind++){
           if(ind!=id_ana){
               distx = (jogadores[id_ana].x -jogadores[ind].x );
               disty = (jogadores[id_ana].y -jogadores[ind].y);
               if((distx <= 32)&&(disty<=32)){
                   jogadores[ind].life--;
                   jogadores[ind].y -= 32;
                   jogadores[ind].x += 32;
               }
               
               if((jogadores[ind].x >(tam*2 - 64))||(jogadores[ind].y <32)){
                       jogadores[ind].life = 0;
                       printf("morte nos espinhos\n");
               }
           } 
        }
    }else if(jogadores[id_ana].hori =='s'){
        for(ind=0;ind<num_jogadores;ind++){
           if(ind!=id_ana){
               distx = (jogadores[id_ana].x -jogadores[ind].x);
               disty = (jogadores[ind].y -jogadores[id_ana].y);
               if((distx <=32)&&(disty<=32)){
                   jogadores[ind].life--;
                   jogadores[ind].y += 32;
                   jogadores[ind].x -= 32;
               }
               
               if((jogadores[ind].x <32)||(jogadores[ind].y >(tam*2 -64))){
                       jogadores[ind].life = 0;
                       printf("morte nos espinhos\n");
               }
           } 
        }
    }else if(jogadores[id_ana].hori =='d'){
        for(ind=0;ind<num_jogadores;ind++){
           if(ind!=id_ana){
               distx = (jogadores[id_ana].x -jogadores[ind].x);
               disty = (jogadores[id_ana].y -jogadores[ind].y);
               if((disty <=32)&&(distx<=32)){
                   jogadores[ind].life--;
                   jogadores[ind].y += 32;
                   jogadores[ind].x += 32;
               }
               
               if((jogadores[ind].x >(tam*2 -64))||(jogadores[ind].y >(tam*2 -64))){
                       jogadores[ind].life = 0;
                       printf("morte nos espinhos\n");
               }
           } 
        }
    }else{
        for(ind=0;ind<num_jogadores;ind++){
           if(ind!=id_ana){
               distx = (jogadores[id_ana].x -jogadores[ind].x);
               disty = (jogadores[id_ana].y -jogadores[ind].y);
               if((disty<=32)&&(distx<=32)){
                   jogadores[ind].life--;
                   jogadores[ind].y -= 32;
                   jogadores[ind].x -= 32;
               }
               
               if((jogadores[ind].x <32)||(jogadores[ind].y <32)){
                       jogadores[ind].life = 0;
                       printf("morte nos espinhos\n");
               }
           } 
        }
    }
}
int main(){
    serverInit(max);
    //exibe configurações de rede para facilitar a conexão
    printf("-------------------------------[CONFIGURACAO DE REDE]-------------------------------\n");
    system("ifconfig");
    printf("------------------------------------------------------------------------------------\n");

    //essa parte vei esperar a sala ter condições minima de iniciar a partida
    int condi_ini = 0, ind_jog=0, temp;
    double temp_sem_conec=0;
    int players[max]={0};
    int num_jogadores;
    while(condi_ini==false){
        if(ind_jog<max){
            temp=acceptConnection();
            if(temp!=NO_CONNECTION){
                players[ind_jog] = temp;
                sendMsgToClient(&ind_jog,sizeof(int),players[ind_jog]);
                ind_jog++;
                temp_sem_conec = 0.0;
            }else{
                al_rest(0.1);
                temp_sem_conec +=0.1;
            }
        }
        printf("%lf - %i\n", temp_sem_conec, ind_jog);
        if((ind_jog ==(max-1))||((temp_sem_conec >=10.0)&&(ind_jog >1))){
            condi_ini =1;
        } 
    }
    num_jogadores = ind_jog;
    printf("passou aqui1\n");
    //informa a todos os clientes qual foi a condição de inicio
    char status_send, status_recb;
    if(ind_jog <5){
        //nesse caso o servidor fechou a sala e iniciou a partid com as codições minimas(pelo menos 2 jogadores)
        status_send = 'm';
        broadcast(&status_send, sizeof(char));
        broadcast(&num_jogadores, sizeof(int));
    }else{
        //nesse caso o servidor fechou a sala e iniciou a partida com as condições otimas(6 jogadores)
        status_send = 'n';
        broadcast(&status_send, sizeof(char));
    }
    printf("passou aqui2\n");
    //atribuição e distribuição de valores iniciais para os jogadores que se conetaram
    int posicoes[12];
    int ind_id, ind_sort = 0;
    sort_posi(posicoes);
    person jogadores[max];
    for(ind_id=0;ind_id<num_jogadores;ind_id++){
        jogadores[ind_id].life = 5;
        jogadores[ind_id].hori = 'w';
        jogadores[ind_id].ataque= '0';
        jogadores[ind_id].x = posicoes[ind_sort];
        ind_sort++;
        jogadores[ind_id].y = posicoes[ind_sort];
        ind_sort++;
    }
    printf("passou aqui4\n");
    broadcast(jogadores, sizeof(person)*num_jogadores);
    //espera o timer de 5 segundos no client para iniciar a partida
    al_init();
    al_rest(5);

    //laço de uma partida
    bool partida = true;
    int ids[max];
    while(partida == true){
        printf("entrou\n");
        rejectConnection();
        startTimer();

        //-------(CODIGOS)--------

        //recebe as modificações do jogador
        for(ind_id=0; ind_id<ind_jog;ind_id++){
            recvMsgFromClient(&jogadores[ind_id], players[ind_id], WAIT_FOR_IT);
            ids[ind_id] = ind_id;
        }

        //verificação de hits
        for(ind_id=0;ind_id<num_jogadores;ind_id++){
            if(jogadores[ind_id].ataque == '1'){
                veri_hits_lanca(jogadores,ind_id,num_jogadores);
            }else if(jogadores[ind_id].ataque =='2'){
                veri_hits_esp(jogadores,ind_id,num_jogadores);
            }
        }
        
        broadcast(jogadores, sizeof(person)*ind_jog);

        // verificação de mortes
        for(ind_id=0;ind_id<num_jogadores;ind_id++){
            if(jogadores[ind_id].life == 0){
                disconnectClient(players[ind_id]);
            }
        }

        for(ind_id=0;ind_id<num_jogadores;ind_id++){
            printf("%i - %c - %i - %i - %i \n",jogadores[ind_id].life,jogadores[ind_id].hori,jogadores[ind_id].ataque,jogadores[ind_id].x, jogadores[ind_id].y);
            
        }
        /*com os dados da rodada e com quais ids eles remetem será dado um bubble sort
        para organizar e processar as atualização no servidor pela ordem cronologica*/
        //bubble_sort(rod_dados,ids);
        FPSLimit();
        
        
    }
    serverReset();
    return 0;
}
