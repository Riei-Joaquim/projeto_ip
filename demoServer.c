#include "libSocket/server.h"
#include "libAllegro/AllegroCore.h"
#include <math.h>

#define max 6

void veri_hits_lanca(person jogadores[max], int id_ana, int num_jogadores){
    int ind, distx, disty;
    if(jogadores[id_ana].hori =='w'){
        for(ind=0;ind<num_jogadores;ind++){
           if(ind!=id_ana){
               distx = (jogadores[id_ana].x -jogadores[ind].x);
               disty = (jogadores[id_ana].y -jogadores[ind].y);
               if(distx < 0){
                   distx *=(-1);
               }
               if(disty < 0){
                   disty *=(-1);
               }
               if((distx==0)&&(disty<=64)&&(jogadores[id_ana].y > jogadores[ind].y)){
                   jogadores[ind].life--;
                   if(jogadores[ind].y>64){
                       jogadores[ind].y -= 64;
                   }else{
                       jogadores[ind].y = 0;
                   }
                   if(jogadores[ind].y <32){
                       jogadores[ind].life = 0;
                   }
               }
           } 
        }
    }else if(jogadores[id_ana].hori =='s'){
        for(ind=0;ind<num_jogadores;ind++){
           if(ind!=id_ana){
               distx = (jogadores[id_ana].x -jogadores[ind].x);
               disty = (jogadores[id_ana].y -jogadores[ind].y);
               if(distx < 0){
                   distx *=(-1);
               }
               if(disty < 0){
                   disty *=(-1);
               }
               if((distx==0)&&(disty<=96)&&(jogadores[id_ana].y < jogadores[ind].y)){
                   jogadores[ind].life--;
                   if(jogadores[ind].y <(alt-96)){
                       jogadores[ind].y += 64;
                   }
                   else{
                       jogadores[ind].y  = (alt -32);
                   }
                      
                   if(jogadores[ind].y >(alt -32)){
                       jogadores[ind].life = 0;
                   }
               }
           } 
        }
    }else if(jogadores[id_ana].hori =='d'){
        for(ind=0;ind<num_jogadores;ind++){
           if(ind!=id_ana){
               distx = (jogadores[ind].x -jogadores[id_ana].x);
               disty = (jogadores[id_ana].y -jogadores[ind].y);
               if(distx < 0){
                   distx *=(-1);
               }
               if(disty < 0){
                   disty *=(-1);
               }
               if((disty==0)&&(distx <= 96)&&(jogadores[id_ana].x < jogadores[ind].x)){
                   jogadores[ind].life--;
                   if(jogadores[ind].x <(larg - 96)){
                       jogadores[ind].x +=64;
                   }else{
                       jogadores[ind].x = (larg - 32);
                   }
                   
                   if(jogadores[ind].x >(larg -32)){
                       jogadores[ind].life = 0;
                   }
                   
               }
           } 
        }
    }else if(jogadores[id_ana].hori =='a'){
        for(ind=0;ind<num_jogadores;ind++){
           if(ind!=id_ana){
               distx = (jogadores[id_ana].x -jogadores[ind].x);
               disty = (jogadores[id_ana].y -jogadores[ind].y);
               if(distx < 0){
                   distx *=(-1);
               }
               if(disty < 0){
                   disty *=(-1);
               }
               if((disty==0)&&(distx <= 96)&&(jogadores[id_ana].x > jogadores[ind].x)){
                   jogadores[ind].life--;
                   if(jogadores[ind].x >64){
                       jogadores[ind].x -=64;
                   }else{
                       jogadores[ind].x = 0;
                   }
                   
                   if((jogadores[ind].x <32)){
                       jogadores[ind].life = 0;
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
               if(distx < 0){
                   distx *=(-1);
               }
               if(disty < 0){
                   disty *=(-1);
               }
               if((distx == 0)&&(jogadores[id_ana].y == (jogadores[ind].y+32))){
                   jogadores[ind].life--;
                   jogadores[ind].y -= 32;
                   jogadores[ind].x += 32;
               }
               else if((jogadores[id_ana].x == (jogadores[ind].x-32))&&(jogadores[id_ana].y == (jogadores[ind].y+32))){
                   jogadores[ind].life--;
                   jogadores[ind].y -= 32;
                   jogadores[ind].x += 32;
               }
               else if((jogadores[id_ana].x == (jogadores[ind].x-32))&&(jogadores[id_ana].y == jogadores[ind].y)){
                   jogadores[ind].life--;
                   jogadores[ind].y -= 32;
                   jogadores[ind].x += 32;
               }
               
               if((jogadores[ind].x >(larg - 32))||(jogadores[ind].y <32)){
                    jogadores[ind].life = 0;
               }
           } 
        }
    }else if(jogadores[id_ana].hori =='s'){
        for(ind=0;ind<num_jogadores;ind++){
           if(ind!=id_ana){
               distx = (jogadores[id_ana].x -jogadores[ind].x);
               disty = (jogadores[ind].y -jogadores[id_ana].y);
               if(distx < 0){
                   distx *=(-1);
               }
               if(disty < 0){
                   disty *=(-1);
               }
               if((distx == 0)&&(jogadores[id_ana].y == (jogadores[ind].y-32))){
                   jogadores[ind].life--;
                   jogadores[ind].y += 32;
                   jogadores[ind].x -= 32;
               }
               else if((jogadores[id_ana].x == (jogadores[ind].x+32))&&(jogadores[id_ana].y == (jogadores[ind].y-32))){
                   jogadores[ind].life--;
                   jogadores[ind].y += 32;
                   jogadores[ind].x -= 32;
               }
               else if((jogadores[id_ana].x == (jogadores[ind].x+32))&&(jogadores[id_ana].y == jogadores[ind].y)){
                   jogadores[ind].life--;
                   jogadores[ind].y += 32;
                   jogadores[ind].x -= 32;
               }
               
               if((jogadores[ind].x <32)||(jogadores[ind].y >(alt -32))){
                    jogadores[ind].life = 0;
               }
           } 
        }
    }else if(jogadores[id_ana].hori =='d'){
        for(ind=0;ind<num_jogadores;ind++){
           if(ind!=id_ana){
               distx = (jogadores[id_ana].x -jogadores[ind].x);
               disty = (jogadores[id_ana].y -jogadores[ind].y);
               if(distx < 0){
                   distx *=(-1);
               }
               if(disty < 0){
                   disty *=(-1);
               }

               if((disty == 0)&&(jogadores[id_ana].x == (jogadores[ind].x-32))){
                   jogadores[ind].life--;
                   jogadores[ind].y += 32;
                   jogadores[ind].x += 32;
               }
               else if((jogadores[id_ana].x == (jogadores[ind].x-32))&&(jogadores[id_ana].y == (jogadores[ind].y-32))){
                   jogadores[ind].life--;
                   jogadores[ind].y += 32;
                   jogadores[ind].x += 32;
               }
               else if((jogadores[id_ana].x == jogadores[ind].x)&&(jogadores[id_ana].y == (jogadores[ind].y-32))){
                   jogadores[ind].life--;
                   jogadores[ind].y += 32;
                   jogadores[ind].x += 32;
               }
               
               if((jogadores[ind].x >(larg -32))||(jogadores[ind].y >(alt -32))){
                    jogadores[ind].life = 0;
               }
           } 
        }
    }else if(jogadores[id_ana].hori =='a'){
        for(ind=0;ind<num_jogadores;ind++){
           if(ind!=id_ana){
               distx = (jogadores[id_ana].x -jogadores[ind].x);
               disty = (jogadores[id_ana].y -jogadores[ind].y);
               if(distx < 0){
                   distx *=(-1);
               }
               if(disty < 0){
                   disty *=(-1);
               }
               if((disty == 0)&&(jogadores[id_ana].x == (jogadores[ind].x+32))){
                   jogadores[ind].life--;
                   jogadores[ind].y -= 32;
                   jogadores[ind].x -= 32;
               }
               else if((jogadores[id_ana].x == (jogadores[ind].x+32))&&(jogadores[id_ana].y == (jogadores[ind].y+32))){
                   jogadores[ind].life--;
                   jogadores[ind].y -= 32;
                   jogadores[ind].x -= 32;
               }
               else if((jogadores[id_ana].x == jogadores[ind].x)&&(jogadores[id_ana].y == (jogadores[ind].y+32))){
                   jogadores[ind].life--;
                   jogadores[ind].y -= 32;
                   jogadores[ind].x -= 32;
               }               
               if((jogadores[ind].x <32)||(jogadores[ind].y <32)){
                    jogadores[ind].life = 0;
               }
           } 
        }
    }
}

int main(){
    serverInit(max);
    while(true){
        //exibe configurações de rede para facilitar a conexão
        printf("-------------------------------[CONFIGURACAO DE REDE]-------------------------------\n");
        system("ifconfig");
        printf("------------------------------------------------------------------------------------\n");

        //essa parte vei esperar a sala ter condições minima de iniciar a partida
        int condi_ini = 0, ind_jog=0, temp;
        double temp_sem_conec=0;
        int players[max]={0};
        int num_jogadores, jog_esp;
        int skins[max];
        printf("Quantos jogadores deseja esperar? ");
        scanf("%i", &jog_esp);
        printf("Server running...\n");
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
            if((ind_jog ==(max-1))||((temp_sem_conec>10.0))&&(ind_jog>=jog_esp)){
                condi_ini =true;
            } 
        }
        num_jogadores = ind_jog;
        //coleta do numero do mapa e da skin
        int ind_id,map_number = 0, map_temp = 0;
        for(ind_id = 0; ind_id < num_jogadores; ind_id++){
            recvMsgFromClient(&skins[ind_id], players[ind_id], WAIT_FOR_IT);
            recvMsgFromClient(&map_temp, players[ind_id], WAIT_FOR_IT);
            map_number +=map_temp;
        }
    
        map_number %= 3;
        broadcast(&map_number,sizeof(int));
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
        
        //atribuição e distribuição de valores iniciais para os jogadores que se conetaram
        int posicoes[12]={160,160,768,160,160,512,768,512,160,384,512,384};
        int ind_sort = 0;
        person jogadores[max];
        for(ind_id=0;ind_id<num_jogadores;ind_id++){
            jogadores[ind_id].life = 5;
            jogadores[ind_id].hori = 'w';
            jogadores[ind_id].ataque= '0';
            jogadores[ind_id].pe = 0;
            jogadores[ind_id].skin = skins[ind_id];
            jogadores[ind_id].x = posicoes[ind_sort];
            ind_sort++;
            jogadores[ind_id].y = posicoes[ind_sort];
            ind_sort++;
        }

        broadcast(jogadores, sizeof(person)*num_jogadores);
        //espera o timer de 4 segundos no client para iniciar a partida
        al_init();
        al_rest(4);

        //laço de uma partida
        bool partida = true, valido;
        int jog_vivos, ind_vivo;
        while(partida == true){
            rejectConnection();
            startTimer();

            //recebe as modificações do jogador
            for(ind_id=0; ind_id<ind_jog;ind_id++){
                recvMsgFromClient(&jogadores[ind_id], players[ind_id], WAIT_FOR_IT);
            }

            //verificação de hits
            for(ind_id=0;ind_id<num_jogadores;ind_id++){
                if(jogadores[ind_id].ataque == 'j'){
                    veri_hits_lanca(jogadores,ind_id,num_jogadores);
                }else if(jogadores[ind_id].ataque =='k'){
                    veri_hits_esp(jogadores,ind_id,num_jogadores);
                }
            }

            //verificação de se algum jogador foi para a berada
            for(ind_id=0; ind_id<num_jogadores;ind_id++){
                if(jogadores[ind_id].x <=32){
                    jogadores[ind_id].life = 0;
                }else if(jogadores[ind_id].x >=(larg-32)){
                    jogadores[ind_id].life = 0;
                }if(jogadores[ind_id].y <=32){
                    jogadores[ind_id].life = 0;
                }if(jogadores[ind_id].y >=(alt-32)){
                    jogadores[ind_id].life = 0;
                }
            }
            //envio das atualização para todos os jogadores
            broadcast(jogadores, sizeof(person)*ind_jog);
            //verifica se ainda tem jogadores vivo na partida
            jog_vivos = 0;
            for(ind_id=0;ind_id<num_jogadores;ind_id++){
                if(jogadores[ind_id].life > 0){
                    jog_vivos++;
                    ind_vivo = ind_id;
                }
            }
            
            //manda aos clientes se vai ter proxima rodada
            if(jog_vivos==1){
                status_send = '1';
                broadcast(&status_send, sizeof(char));
                partida = false;
            }else{
                status_send = '2';
                broadcast(&status_send, sizeof(char));
            }

            FPSLimit();

        }
        //desconecta os jogadores ao final da partida
        for(ind_id=0;ind_id<num_jogadores;ind_id++){
            disconnectClient(players[ind_id]);
        }
        al_rest(10.0);
        serverReset();
    }
    return 0;
}
