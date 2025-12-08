#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "jogo.h"
#include "snake.h"
#include "frutinha.h"
#include "mapa.h"
#include <time.h>

//Colocado: IniciaMapa
//Retirado: DefineTunel
void IniciaJogo(Jogo *jogo){

    jogo->mapa.resize_var = jogo->resize_var;
    jogo->frutinha.resize_var = jogo->resize_var;
    jogo->cobra.resize_var = jogo->resize_var;

    jogo->nivel = 2;
    IniciaMapa(&jogo->mapa, jogo->nivel);
    IniciaCobra(&jogo->cobra);
    IniciaFrutinha(&jogo->frutinha);
    AtualizaPosFrutinha(jogo);
    InicializaMenu(jogo);
    InicializaConfig(jogo);
    InicializaLeaderboard(jogo);
    jogo->music_game = LoadMusicStream("assets/ingame_music.mp3");

    jogo->game_state = menu_prin;

    jogo->tempo = GetTime();
    jogo->cobra.cooldown = 0.2;
}

//Retirado: DesenhaFundo, DesenhaBordas
//Colocado: DesenhaMapa
void DesenhaJogo(Jogo* jogo){
    
    DesenhaMapa(&jogo->mapa);
    MostraTempo(jogo);
    DesenhaCobra(&jogo->cobra); 
    DesenhaFrutinha(&jogo->frutinha, &jogo->cobra);
}

int AtualizaRodada(Jogo* jogo){
    
    AtualizaDirecao(&jogo->cobra);
    
    if(GetTime() - jogo->tempo >= 0.2){
        
        jogo->tempo = GetTime();
        AtualizaPosCobra(&jogo->cobra);
        jogo->cobra.cooldown = 0.2;
        jogo->sessao += 0.2;
        CobraGulosa(jogo);
        UsaTunel(jogo);
        TrocaMapa(jogo);
        cruzaCobra(&jogo->cobra);
    }
    
    tocaMusica(jogo);

    return MataCobra(jogo);
}

void tocaMusica(Jogo* jogo){
    if(IsMusicStreamPlaying(jogo->music_game)){
        UpdateMusicStream(jogo->music_game);
    }else if(!IsMusicStreamPlaying(jogo->music_game) && jogo->game_state == start){
        PlayMusicStream(jogo->music_game);
    }
}
void LiberaEspaco(Jogo* jogo){

    DescarregaFundo(&jogo->mapa);
    DescarregaFrutinha(&jogo->frutinha);
    LiberaEspacoCobra(&jogo->cobra);
    DescarregaText(jogo);
}

void MostraTempo(Jogo* jogo){
    int minutos, segundos;
    minutos = jogo->sessao/60;
    segundos = (int)(jogo->sessao)%60;
    DrawRectangle(490*jogo->resize_var, 25*jogo->resize_var, 105*jogo->resize_var, 35*jogo->resize_var, (Color){0,0,0,150});
    DrawText(TextFormat("Tempo: %d:%02d", minutos, segundos), 500*jogo->resize_var, 30*jogo->resize_var, 15*jogo->resize_var, RAYWHITE);
    DrawText(TextFormat("Pontos: %03d", jogo->frutinha.pontuacao), 500*jogo->resize_var, 45*jogo->resize_var, 15*jogo->resize_var, RAYWHITE);

}

void CobraGulosa(Jogo* jogo){

    if(CheckCollisionRecs(jogo->cobra.Cabeca->posicao, jogo->frutinha.posicao)){
        
        AumentaCobra(&jogo->cobra);
        jogo->frutinha.pontuacao++;
        jogo->frutinha.existe = false;
        AtualizaPosFrutinha(jogo);
    }
}

void FimdeJogotxt(Jogo* jogo){
    DrawText("Você Perdeu!", 225*jogo->resize_var, 200*jogo->resize_var, 40*jogo->resize_var, WHITE);
    DrawText(TextFormat("Tempo da partida anterior: %d:%02d", (int)jogo->sessao/60, (int)jogo->sessao%60), 225*jogo->resize_var, 300*jogo->resize_var, 20*jogo->resize_var, WHITE);
    DrawText(TextFormat("Pontuação: %d", jogo->frutinha.pontuacao), 225*jogo->resize_var, 350*jogo->resize_var, 20*jogo->resize_var, WHITE);
    DrawText("Pressione ENTER para tentar novamente.", 150*jogo->resize_var, 400*jogo->resize_var, 20*jogo->resize_var, WHITE); 
}

void DescarregaText(Jogo* jogo){
    UnloadTexture(jogo->textura);
    UnloadTexture(jogo->frutinha.textura);
}
//DAQUI PRA BAIXO, SOMENTE A PARTE 2--------------------------------------------------------------------------------------------------/

//MENU--------------------------------------------------------------------------------------------------/
void InicializaMenu(Jogo* jogo){
    jogo->menu.qual_button = 0;
    jogo->menu.imagem = LoadImage("assets/cobrinha_menu.png");
    ImageResize(&jogo->menu.imagem, (LARGURA*jogo->resize_var)/2.5, (ALTURA*jogo->resize_var)/2.5);
    jogo->menu.textura = LoadTextureFromImage(jogo->menu.imagem);
    UnloadImage(jogo->menu.imagem);
    jogo->menu.start = (Rectangle){(LARGURA*jogo->resize_var)*0.6, ((ALTURA*jogo->resize_var)/10)*2, (LARGURA*jogo->resize_var)*0.3, (ALTURA*jogo->resize_var)*0.125};
    jogo->menu.leaderboards = (Rectangle){(LARGURA*jogo->resize_var)*0.6, ((ALTURA*jogo->resize_var)/10)*4, (LARGURA*jogo->resize_var)*0.3, (ALTURA*jogo->resize_var)*0.125};
    jogo->menu.config = (Rectangle){(LARGURA*jogo->resize_var)*0.6, ((ALTURA*jogo->resize_var)/10)*6, (LARGURA*jogo->resize_var)*0.3, (ALTURA*jogo->resize_var)*0.125};
    jogo->menu.exit = (Rectangle){(LARGURA*jogo->resize_var)*0.6, ((ALTURA*jogo->resize_var)/10)*8, (LARGURA*jogo->resize_var)*0.3, (ALTURA*jogo->resize_var)*0.125};
    jogo->menu.som = LoadSound("assets/som_menu.wav");
  
}

void DrawMenu(Jogo* jogo){
    switch (jogo->menu.qual_button){
    case 0:
        DrawRectangle(jogo->menu.start.x, jogo->menu.start.y, jogo->menu.start.width+(LARGURA*jogo->resize_var)*0.01, jogo->menu.start.height+(ALTURA*jogo->resize_var)*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            jogo->game_state = start;
            PlaySound(jogo->menu.som);
        }
        break;
    case 1:
        DrawRectangle(jogo->menu.leaderboards.x, jogo->menu.leaderboards.y, jogo->menu.leaderboards.width+(LARGURA*jogo->resize_var)*0.01, jogo->menu.leaderboards.height+(ALTURA*jogo->resize_var)*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            jogo->game_state = leaderboards;
            PlaySound(jogo->menu.som);
        }
        break;
    case 2:
        DrawRectangle(jogo->menu.config.x, jogo->menu.config.y, jogo->menu.config.width+(LARGURA*jogo->resize_var)*0.01, jogo->menu.config.height+(ALTURA*jogo->resize_var)*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            jogo->game_state = config;
            PlaySound(jogo->menu.som);
        }
        break;
    case 3:
        DrawRectangle(jogo->menu.exit.x, jogo->menu.exit.y, jogo->menu.exit.width+(LARGURA*jogo->resize_var)*0.01, jogo->menu.exit.height+(ALTURA*jogo->resize_var)*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            jogo->game_state = sair;
        }
        break;
    }
    DrawTexture(jogo->menu.textura, 0, 0, WHITE);
    DrawText("Jogo da Crobinha", (LARGURA*jogo->resize_var)*0.4, (ALTURA*jogo->resize_var)*0.1, 40, RAYWHITE);
    DrawRectangleRec(jogo->menu.start, RAYWHITE);
    DrawText("Jogar", jogo->menu.start.x+(LARGURA*jogo->resize_var)*0.08, jogo->menu.start.y+(ALTURA*jogo->resize_var)*0.01, 25, BLACK);
    DrawRectangleRec(jogo->menu.leaderboards, RAYWHITE);
    DrawText("Rankings", jogo->menu.leaderboards.x+(LARGURA*jogo->resize_var)*0.06, jogo->menu.leaderboards.y+(ALTURA*jogo->resize_var)*0.01, 25, BLACK);
    DrawRectangleRec(jogo->menu.config, RAYWHITE);
    DrawText("Configurações", jogo->menu.config.x+(LARGURA*jogo->resize_var)*0.03, jogo->menu.config.y+(ALTURA*jogo->resize_var)*0.01, 25, BLACK);
    DrawRectangleRec(jogo->menu.exit, RAYWHITE);
    DrawText("Sair", jogo->menu.exit.x+(LARGURA*jogo->resize_var)*0.1, jogo->menu.exit.y+(ALTURA*jogo->resize_var)*0.01, 25, BLACK);
}

void AtualizaMenu(Jogo* jogo){
    if(IsKeyPressed(KEY_DOWN)){
        jogo->menu.qual_button++;
    }if(IsKeyPressed(KEY_UP)){
        jogo->menu.qual_button--;
    }
    if(jogo->menu.qual_button < 0){
        jogo->menu.qual_button = 3;
        
    }
    if(jogo->menu.qual_button > 3){
            jogo->menu.qual_button = 0;
        }
}

//CONFIG--------------------------------------------------------------------------------------------------/
void InicializaConfig(Jogo *jogo){
    jogo->config.res660 = (Rectangle){(LARGURA*jogo->resize_var)*0.60, (ALTURA*jogo->resize_var)*0.15, (LARGURA*jogo->resize_var)*0.35, (ALTURA*jogo->resize_var)*0.2};
    jogo->config.res858 = (Rectangle){(LARGURA*jogo->resize_var)*0.60, (ALTURA*jogo->resize_var)*0.45, (LARGURA*jogo->resize_var)*0.35, (ALTURA*jogo->resize_var)*0.2};
    jogo->config.voltar = (Rectangle){(LARGURA*jogo->resize_var)*0.60, (ALTURA*jogo->resize_var)*0.75, (LARGURA*jogo->resize_var)*0.35, (ALTURA*jogo->resize_var)*0.2};
}

void DrawConfig(Jogo *jogo){
    switch (jogo->config.qual_button){
        case 0:
        DrawRectangle(jogo->config.res660.x, jogo->config.res660.y, jogo->config.res660.width+(LARGURA)*0.01, jogo->config.res660.height+(ALTURA)*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            PlaySound(jogo->menu.som);
            jogo->resize_var = 1;
            SetWindowSize(660, 660);
            DescarregaFundo(&jogo->mapa);
            DescarregaMapa(&jogo->mapa);
            IniciaJogo(jogo);
           
            
        }
        break;
    case 1:
        DrawRectangle(jogo->config.res858.x, jogo->config.res858.y, jogo->config.res858.width+(LARGURA)*0.01, jogo->config.res858.height+(ALTURA)*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            PlaySound(jogo->menu.som);
            jogo->resize_var = 1.5;
            SetWindowSize(990,990);
            DescarregaFundo(&jogo->mapa);
            DescarregaMapa(&jogo->mapa);
            IniciaJogo(jogo);
        
        }
        break;
    case 2:
        DrawRectangle(jogo->config.voltar.x, jogo->config.voltar.y, jogo->config.voltar.width+(LARGURA*jogo->resize_var)*0.01, jogo->config.voltar.height+(ALTURA*jogo->resize_var)*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            PlaySound(jogo->menu.som);
            jogo->game_state = menu_prin;
        }
        break;

    }
    DrawText("Configurações", (LARGURA*jogo->resize_var)*0.1, (ALTURA*jogo->resize_var)*0.1, 35, WHITE);
    DrawRectangleRec(jogo->config.res660, WHITE);
    DrawText("660x660", jogo->config.res660.x+(LARGURA*jogo->resize_var)*0.15, jogo->config.res660.y+(ALTURA*jogo->resize_var)*0.015, 25, BLACK);
    DrawRectangleRec(jogo->config.res858, WHITE);
    DrawText("858x858", jogo->config.res858.x+(LARGURA*jogo->resize_var)*0.15, jogo->config.res858.y+(ALTURA*jogo->resize_var)*0.015, 25, BLACK);
    DrawRectangleRec(jogo->config.voltar, WHITE);
    DrawText("Voltar", jogo->config.voltar.x+(LARGURA*jogo->resize_var)*0.15, jogo->config.voltar.y+(ALTURA*jogo->resize_var)*0.015, 25, BLACK);
}

void AtualizaConfig(Jogo *jogo){
    if(IsKeyPressed(KEY_DOWN)){
        jogo->config.qual_button++;
        if(jogo->config.qual_button > 2){
            jogo->config.qual_button = 0;
        }
    }else if(IsKeyPressed(KEY_UP)){
        jogo->config.qual_button--;
        if(jogo->config.qual_button < 0){
            jogo->config.qual_button = 2;
        }
    }
}

//LEADERBOARD--------------------------------------------------------------------------------------------------/
void InicializaLeaderboard(Jogo* jogo){
    jogo->leaderboard.voltar = (Rectangle){(LARGURA*jogo->resize_var)*0.60, (ALTURA*jogo->resize_var)*0.75, (LARGURA*jogo->resize_var)*0.35, (ALTURA*jogo->resize_var)*0.2};
    jogo->leaderboard.qual_button = 0;
}

void DrawLeaderboard(Jogo *jogo){
    switch (jogo->leaderboard.qual_button){
    case 0:
        DrawRectangle(jogo->leaderboard.voltar.x, jogo->leaderboard.voltar.y, jogo->leaderboard.voltar.width+(LARGURA*jogo->resize_var)*0.01, jogo->leaderboard.voltar.height+(ALTURA*jogo->resize_var)*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            PlaySound(jogo->menu.som);
            jogo->game_state = menu_prin;
        }
        break;
    }
    DrawText("Leaderboard:", (LARGURA*jogo->resize_var)*0.1, (ALTURA*jogo->resize_var)*0.1, 35, WHITE);
    if(jogo->jogos == 0){
        DrawText("Nenhuma pontuação registrada ainda.", (LARGURA*jogo->resize_var)*0.1, (ALTURA*jogo->resize_var)*0.2, 20, WHITE);
    }
    else {
    OrdenaRanking(jogo);
    jogo->ranking = fopen("ranking.txt", "r");
    char linha[30];
    int y_posicao = (ALTURA*jogo->resize_var)*0.2;
    while(fgets(linha, sizeof(linha), jogo->ranking) != NULL){
        DrawText(linha, (LARGURA*jogo->resize_var)*0.1, y_posicao, 20, WHITE);
        y_posicao += 30*jogo->resize_var;
    }
    fclose(jogo->ranking);
    }
    DrawRectangleRec(jogo->leaderboard.voltar, WHITE);
    DrawText("Voltar", jogo->leaderboard.voltar.x, jogo->leaderboard.voltar.y+(ALTURA*jogo->resize_var)*0.01, 25, BLACK);
}

void AtualizaLeaderboard(Jogo *jogo){
    //a estrutura tá pronta, mas tá zerada pq não temos outros botões ainda
    if(IsKeyPressed(KEY_DOWN)){
        jogo->leaderboard.qual_button++;
        if(jogo->leaderboard.qual_button > 0){
            jogo->leaderboard.qual_button = 0;
        }
    }else if(IsKeyPressed(KEY_UP)){
        jogo->leaderboard.qual_button--;
        if(jogo->leaderboard.qual_button < 0){
            jogo->leaderboard.qual_button = 0;
        }
    }
}

void DefineRanking(Jogo* jogo){
    if(jogo->jogos < 19){
        jogo->tempos[jogo->jogos] = jogo->sessao;
        jogo->rankings[jogo->jogos] = jogo->frutinha.pontuacao;
        jogo->jogos++;
        return;
    }
    else{
    int menor_pontuacao = 0;
    for (int i = 1; i < 20; i++){
        if(jogo->rankings[i] < jogo->rankings[menor_pontuacao]){
            menor_pontuacao = i;
        }
    }
    if(jogo->frutinha.pontuacao > jogo->rankings[menor_pontuacao]){
        jogo->rankings[menor_pontuacao] = jogo->frutinha.pontuacao;
        jogo->tempos[menor_pontuacao] = jogo->sessao;
}
}
}

void AtualizaRanking(Jogo* jogo){
    jogo->ranking = fopen("ranking.txt", "r");
    if(jogo->ranking != NULL){
        int i = 0, t;
        int tempomin, temposeg;
        while(fscanf(jogo->ranking, "%d - Tempo: %d:%d | Pontos: %d\n", &t, &tempomin, &temposeg, &jogo->rankings[i]) != EOF){
            jogo->tempos[i] =(float) tempomin * 60 + temposeg;
            i++;
        }
        jogo->jogos = t+1;
        fclose(jogo->ranking);
    }
    DefineRanking(jogo);
    OrdenaRanking(jogo);
    jogo->ranking = fopen("ranking.txt", "w");
    for(int i = 0; i < jogo->jogos; i++){
        if(jogo->tempos[i] == 0){
            break;
        }
    fprintf(jogo->ranking, "%d - Tempo: %d:%02d | Pontos: %d\n",i+1, (int)jogo->tempos[i]/60, (int)jogo->tempos[i]%60, jogo->rankings[i]);
    }
    fclose(jogo->ranking);
}

void OrdenaRanking(Jogo* jogo){
    for(int i = 0; i < 19; i++){
        for(int j = i+1; j < 20; j++){
            if(jogo->rankings[j] > jogo->rankings[i]){
                int temp_pontos = jogo->rankings[i];
                jogo->rankings[i] = jogo->rankings[j];
                jogo->rankings[j] = temp_pontos;
                int temp_tempos = jogo->tempos[i];
                jogo->tempos[i] = jogo->tempos[j];
                jogo->tempos[j] = temp_tempos;
            }
            if(jogo->rankings[j] == jogo->rankings[i]){
                if(jogo->tempos[j] > jogo->tempos[i]){
                    int temp_pontos = jogo->rankings[i];
                    jogo->rankings[i] = jogo->rankings[j];
                    jogo->rankings[j] = temp_pontos;
                    int temp_tempos = jogo->tempos[i];
                    jogo->tempos[i] = jogo->tempos[j];
                    jogo->tempos[j] = temp_tempos;
                }
            }
        }
    }    
}

// TUNEL.............................


void UsaTunel(Jogo* jogo){

    for(int i = 0; i < jogo->mapa.numTunel; i += 2){

        if(CheckCollisionRecs(jogo->mapa.tunel[i], jogo->cobra.Cabeca->posicao)){
            jogo->cobra.Cabeca->posicao = jogo->mapa.tunel[i+1];
        }
        else if(CheckCollisionRecs(jogo->mapa.tunel[i+1], jogo->cobra.Cabeca->posicao)){
            jogo->cobra.Cabeca->posicao = jogo->mapa.tunel[i];
        }
    }
    
}

// MAPA................................

void TrocaMapa(Jogo* jogo){
    //ATENÇÃO
    /*se vcs alterarem o valor do if(jogo->cobra.tamanho >= n), mude a terceira linha
    do atualizaposicaofrutinha*/
    if(jogo->nivel != 3){
        if(jogo->cobra.tamanho >= 10){
    
            DescarregaMapa(&jogo->mapa);
            DescarregaFrutinha(&jogo->frutinha);
            LiberaEspacoCobra(&jogo->cobra);
            jogo->nivel += 1;
            
            FLVCobra(&jogo->cobra);
            IniciaMapa(&jogo->mapa, jogo->nivel);
            IniciaCobra(&jogo->cobra);
            IniciaFrutinha(&jogo->frutinha);
            AtualizaPosFrutinha(jogo);
        }

    }
}

// NOVA MATA COBRA

int MataCobra(Jogo* jogo){

    TipoApontador Testadouro = jogo->cobra.Cabeca->Prox;
    while(Testadouro != NULL){

        if(Testadouro->posicao.x == jogo->cobra.Cabeca->posicao.x && Testadouro->posicao.y == jogo->cobra.Cabeca->posicao.y){
            PlaySound(jogo->cobra.morte);
            AtualizaRanking(jogo);
            return 1;
        }

        Testadouro = Testadouro->Prox;
    }

    Testadouro = jogo->cobra.Cabeca;

    for(int i = 0; i < jogo->mapa.numObstaculos; i++){

        if(CheckCollisionRecs(Testadouro->posicao, jogo->mapa.obstaculos[i])){

            PlaySound(jogo->cobra.morte);
            AtualizaRanking(jogo);
            return 1;
        }
    }

    for(int i = 0; i < jogo->mapa.numBorda; i++){
        
        if(CheckCollisionRecs(Testadouro->posicao, jogo->mapa.borda[i])){

            PlaySound(jogo->cobra.morte);
            AtualizaRanking(jogo);
            return 1;
        }
    }

    return 0;
}

// NOVA POSFRUTINHA
void AtualizaPosFrutinha(Jogo* jogo){

    bool posicaoValida = false;
    int tamanhoBloco_X = STD_SIZE_X * jogo->resize_var;
    int tamanhoBloco_Y = STD_SIZE_Y * jogo->resize_var;
    
    int totalColunas = (LARGURA * jogo->resize_var) / tamanhoBloco_X;
    int totalLinhas = (ALTURA * jogo->resize_var) / tamanhoBloco_Y;

    do{

        posicaoValida = true;

        // CRIA UMA POSICAO PARA A FRUTINHA

        jogo->frutinha.posicao.x = tamanhoBloco_X + (tamanhoBloco_X*(rand() % (totalColunas - 2)));
        jogo->frutinha.posicao.y = tamanhoBloco_Y + (tamanhoBloco_Y*(rand() % (totalLinhas - 2)));

        //TESTA COLISAO COM COBRA
        
        TipoApontador testadouro = jogo->cobra.Cabeca;
         
        while(testadouro != NULL){

            if(CheckCollisionRecs(testadouro->posicao, jogo->frutinha.posicao)){    
                posicaoValida = false;
                break;
            }

            testadouro = testadouro->Prox;
        }

        //TESTA COLISAO COM OBSTACULOS

        for(int i = 0; i < jogo->mapa.numObstaculos; i++){
            if(CheckCollisionRecs(jogo->frutinha.posicao, jogo->mapa.obstaculos[i])){
                posicaoValida = false;
                break;
            }
        }

        // TESTA COLISAO COM A BORDA

        for(int i = 0; i < jogo->mapa.numBorda; i++){
            if(CheckCollisionRecs(jogo->frutinha.posicao, jogo->mapa.borda[i])){
                posicaoValida = false;
                break;
            }
        }


        for(int i = 0; i < jogo->mapa.numTunel; i++){
            if(CheckCollisionRecs(jogo->frutinha.posicao, jogo->mapa.tunel[i])){
                posicaoValida = false;
                break;
            }
        }

    } while(posicaoValida == false);

    jogo->frutinha.existe = true;

}

