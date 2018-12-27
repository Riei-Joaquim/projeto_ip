#include "libSocket/client.h"
#include "libAllegro/AllegroCore.h"
#include "libSocket/server.h"
#define max 4

bool mov_valid(char mov, person jogadores[max], int num_jogadores, int meu_id){
    int ind;
    if(mov == 'w'){
        for(ind=0;ind<num_jogadores;ind++){
            if(ind!=meu_id){
                if((jogadores[ind].x == jogadores[meu_id].x)&&(jogadores[ind].y == (jogadores[meu_id].y-32))){
                    return false;
                }
            }
        }
    }else if(mov == 's'){
        for(ind=0;ind<num_jogadores;ind++){
            if(ind!=meu_id){
                if((jogadores[ind].x == jogadores[meu_id].x)&&(jogadores[ind].y == (jogadores[meu_id].y+32))){
                    return false;
                }
            }
        }
    }else if(mov == 'a'){
        for(ind=0;ind<num_jogadores;ind++){
            if(ind!=meu_id){
                if((jogadores[ind].x == (jogadores[meu_id].x-32))&&(jogadores[ind].y == (jogadores[meu_id].y))){
                    return false;
                }
            }
        }
    }else if(mov == 'd'){
        for(ind=0;ind<num_jogadores;ind++){
            if(ind!=meu_id){
                if((jogadores[ind].x == (jogadores[meu_id].x+32))&&(jogadores[ind].y == (jogadores[meu_id].y))){
                    return false;
                }
            }
        }
    }
    return true;
}
int main(){
    int skin_player;
    int map_number;
    int x_close=9;
    int id_local;

    //inicialização das funções allegro
    coreInit();
    windowInit(larg, alt, "PUNCH KILL");
    inputInit();
    fontInit();
    loadGraphics_and_sounds();
    
    //setagem da musica
    al_attach_audio_stream_to_mixer(musica,al_get_default_mixer());
    al_set_audio_stream_playing(musica,true);

    //impressão da tela inicial 
    al_draw_bitmap(hscs, 0, 0, 0);
    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, 70, ALLEGRO_ALIGN_CENTRE, "PUNCH KILL");
    al_draw_text(start, al_map_rgb(255, 255, 0), (larg/2)-40, 220, ALLEGRO_ALIGN_CENTRE, "Start Game");
    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 420, ALLEGRO_ALIGN_CENTRE, "Credits");
    al_draw_text(start, al_map_rgb(255, 255, 255), (larg/2)-40, 620, ALLEGRO_ALIGN_CENTRE, "Quit Game");
    al_flip_display();

    //funções do menu
    x_close = digitemenu();
    if(x_close==0){
        //exit do jogo
        return 0;
    }
    else if(x_close==1){
        //funções do jogo em si
        char ip[12]={"___________"};
        //conexão com o servidor
        int ret_conec, ind;
        do{
        digite_ip(ip);
        ret_conec = connectToServer(ip);
        if(ret_conec==SERVER_UP){

            //impressão da mensagem de conexão 
            al_draw_bitmap(hscs, 0, 0, 0);
            al_draw_text(telaip, al_map_rgb(255, 255, 255), (larg/2)-40, 300, ALLEGRO_ALIGN_CENTRE, "Conexão estabelecida!");
            al_flip_display();
            al_rest(2.0);
            recvMsgFromServer(&id_local,WAIT_FOR_IT);
        }else{
            //impressão da mensagem de conexão 
            al_draw_bitmap(hscs, 0, 0, 0);
            al_draw_text(telaip, al_map_rgb(255, 255, 255), (larg/2)-40, 300, ALLEGRO_ALIGN_CENTRE, "Conexão nao estabelecida!");
            al_flip_display();
            al_rest(2.0);

            //limpeza do ip para excluir o ip invalidos
            for(ind = 0; ind<11;ind++){
                ip[ind] = '_';
            }

            if(ret_conec== SERVER_CLOSED){
                //impressão da mensagem de conexão 
                al_draw_bitmap(hscs, 0, 0, 0);
                al_draw_text(telaip, al_map_rgb(255, 255, 255), (larg/2)-40, 300, ALLEGRO_ALIGN_CENTRE, "Sala fechada!");
                al_flip_display();
                al_rest(2.0);
            }
        }
        }while(ret_conec!=SERVER_UP);

        person jogadores[max];
        //seleção da skin do pesonagem e de mapa
        skin_player = select_player();
        map_number = select_map();

        //tela de espera
        al_draw_bitmap(hscs, 0, 0, 0);
        al_draw_text(telaip, al_map_rgb(255, 255, 255), (larg/2)-40, 200, ALLEGRO_ALIGN_CENTRE,"Aguardando mais jogadores");
        al_draw_text(telaip, al_map_rgb(255, 255, 255), (larg/2)-40, 300, ALLEGRO_ALIGN_CENTRE,"Use as teclas:");
        al_draw_text(telaip, al_map_rgb(255, 255, 255), (larg/2)-40, 400, ALLEGRO_ALIGN_CENTRE,"W, A, S, D para se mover");
        al_draw_text(telaip, al_map_rgb(255, 255, 255), (larg/2)-40, 500, ALLEGRO_ALIGN_CENTRE,"J e K para atacar");
        
        al_flip_display();

        //envio da skin local
        sendMsgToServer(&skin_player, sizeof(int));

        //envio da escolha local
        sendMsgToServer(&map_number,sizeof(int));

        //recebimento da do mapa matriz
        recvMsgFromServer(&map_number, WAIT_FOR_IT);

        //espera o servidor dar o sinal que a sala foi fechada
        char status_recb;
        int num_jogadores;
        char mensg1[] = {"(a jogadores)"};
        char mensg2[] = {"Partida iniciada com sala cheia"};
        recvMsgFromServer(&status_recb, WAIT_FOR_IT);
        if(status_recb == 'm'){
            recvMsgFromServer(&num_jogadores, WAIT_FOR_IT);
            //edição da mensagem
            status_recb = num_jogadores +'0';
            mensg1[1] = status_recb;
            //impressão da mensagem de sala fechada em condições abaixo das maximas
            al_draw_bitmap(hscs, 0, 0, 0);
            al_draw_text(telaip, al_map_rgb(255, 255, 255), (larg/2)-40, 200, ALLEGRO_ALIGN_CENTRE, "Partida iniciada");
            al_draw_text(telaip, al_map_rgb(255, 255, 255), (larg/2)-40, 300, ALLEGRO_ALIGN_CENTRE, mensg1);
            al_flip_display();
            al_rest(2.0);
        }else{
            //impressão da mensagem de sala fechada em condições nas condições otimas
            al_draw_bitmap(hscs, 0, 0, 0);
            al_draw_text(telaip, al_map_rgb(255, 255, 255), (larg/2)-40, 300, ALLEGRO_ALIGN_CENTRE, mensg2);
            al_flip_display();
            al_rest(2.0);
        }

        //recebe as posições iniciais dos jogadores
        al_draw_bitmap(hscs, 0, 0, 0);
        al_draw_text(telaip, al_map_rgb(255, 255, 255), (larg/2)-40, 300, ALLEGRO_ALIGN_CENTRE,"Aguardando os outros jogadores");
        al_flip_display();
        recvMsgFromServer(jogadores,WAIT_FOR_IT);

        //distribui os jogadores por uma matriz que representa o mapa do campo
        char mapa_jog[alt][larg];
        int i,j;
        //zerando a matriz
        for(i=0;i<alt;i++){
            for(j=0;j<larg;j++){
                mapa_jog[i][j]= '0';
            }
        }
        //colocando os jogadores nela
        int a;
        bool tem_jog;
        for(i=0;i<alt;i++){
            for(j=0;j<larg;j++){
                for(a=0;a<num_jogadores;a++){
                    if((jogadores[a].y == i)&&(jogadores[a].x == j)){
                        mapa_jog[i][j] = (a+'a');
                    } 
                }
            }
        }
       
        //impressao do timer já no mapa
        game_begin(map_number, jogadores[id_local],0,0);

        //stream de musica
        if(map_number==0){
            setAudio("Resources/audios/mapa1.ogg");
        }
        else if(map_number==1){
            setAudio("Resources/audios/mapa2.ogg");
        }
        else{
            setAudio("Resources/audios/mapa3.ogg");
        }

        // laço da partida
        bool partida = true;
        char caracter; 
        int ind_vivo;
        char mens_win[13]={"O jogador a"};
        int contfps=0;
        while(partida ==true){
            startTimer();

            //reset da musica
            if(contfps>=600){
                contfps=0;
               if(map_number==0){
                    setAudio("Resources/audios/mapa1.ogg");
                }
                else if(map_number==1){
                    setAudio("Resources/audios/mapa2.ogg");
                }
                else{
                    setAudio("Resources/audios/mapa3.ogg");
                }
            }else{
                contfps++;
            }

            // impressão do quadro atual
            imprimi_mapa(map_number);
            imprimi_jog(mapa_jog,jogadores);
            attack(num_jogadores,jogadores, mapa_jog, id_local, map_number);
            
            //coleta a entrada do cliente para a rodada
            if(jogadores[id_local].life>0){
                caracter = move();
                if(caracter == 'W'||caracter == 'w'){
                    if((jogadores[id_local].y>32)&&(mov_valid('w',jogadores,num_jogadores,id_local))){
                        jogadores[id_local].y-=32;
                        jogadores[id_local].hori = 'w';
                    }
                }else if(caracter == 'S'||caracter == 's'){
                    if((jogadores[id_local].y<(larg-32))&&(mov_valid('s',jogadores,num_jogadores,id_local))){
                        jogadores[id_local].y+=32;
                        jogadores[id_local].hori = 's';
                    }
                }else if(caracter == 'A'||caracter == 'a'){
                    if((jogadores[id_local].x>32)&&(mov_valid('a',jogadores,num_jogadores,id_local))){
                    jogadores[id_local].x-=32;
                    jogadores[id_local].hori = 'a';
                }
                }else if(caracter == 'D'||caracter == 'd'){
                    if((jogadores[id_local].x<(larg-32))&&(mov_valid('d',jogadores,num_jogadores,id_local))){
                        jogadores[id_local].x+=32;
                        jogadores[id_local].hori = 'd';
                    }
                }
                if((caracter == 'j')||(caracter == 'J')){
                    jogadores[id_local].ataque = 'j';
                }else if((caracter == 'k')||(caracter == 'K')){
                    jogadores[id_local].ataque = 'k';
                }else{
                    jogadores[id_local].ataque = ' ';
                }
            }else{
                jogadores[id_local].ataque = ' ';
            }

            //envia minhas alterações para o server e recebe as alterações de todos os jogadores
            sendMsgToServer(&jogadores[id_local], sizeof(person));
            recvMsgFromServer(jogadores,WAIT_FOR_IT);

            //verificação local de se o jogador está vivo
            if((jogadores[id_local].x <32)||(jogadores[id_local].x > (larg -32))||(jogadores[id_local].y <32)||(jogadores[id_local].y > (alt -32))){
                jogadores[id_local].life = 0;
            }

            //atualiza a matriz com as novas posições recebidas do server
            for(i=0;i<alt;i++){
                for(j=0;j<larg;j++){
                    tem_jog = false;
                    for(a=0;a<num_jogadores;a++){
                        if((jogadores[a].y == i)&&(jogadores[a].x == j)){
                            mapa_jog[i][j] = (a+'a');
                            tem_jog = true;
                        } 
                    }
                    if(tem_jog==false){
                        mapa_jog[i][j] = '0';
                    }
                }

            }

            //verificação de se a partida acabou
            recvMsgFromServer(&status_recb, WAIT_FOR_IT);
            if(status_recb == '1'){
                partida = false;
                al_draw_bitmap(hscs, 0, 0, 0);
                for(ind=0;ind<num_jogadores;ind++){
                    if(jogadores[ind].life>0){
                        ind_vivo = ind;
                    }
                }
                if((ind_vivo == id_local)&&(jogadores[id_local].life>0)){
                    setAudio("Resources/audios/vitoria.ogg");
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, 300, ALLEGRO_ALIGN_CENTRE, "You-win");
                }else{
                    setAudio("Resources/audios/derrota.ogg");
                    mens_win[10]= ind_vivo +'1';
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, 300, ALLEGRO_ALIGN_CENTRE,mens_win);
                    al_draw_text(ubuntu, al_map_rgb(255, 255, 255), (larg/2)-40, 400, ALLEGRO_ALIGN_CENTRE, "ganhou a partida!");
                }
                al_flip_display();
                al_rest(10.0);
            }

            //exibição de proximo quadro
            al_flip_display();
            FPSLimit();
        }
        //encerrando as funções allegro
        allegroEnd(); 
    }
    else if(x_close==3){
        allegroEnd();
        return 0;
    }
    return 0;
}
