#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "jogo.h"
#include "snake.h"
#include "frutinha.h"
#include <time.h>



void IniciaBordas(Jogo *jogo){
    //Borda de cima
    jogo->borda[0] = (Rectangle) {0, 0, LARGURA, 10};
    //Borda da direita
    jogo->borda[1] = (Rectangle) {LARGURA - 10, 0, 10, ALTURA};
    //Borda de baixo
    jogo->borda[2] = (Rectangle) {0, ALTURA - 10, LARGURA, 10};
    //Borda da esquerda
    jogo->borda[3] = (Rectangle) {0, 0, 10, ALTURA};
}

void IniciaFundo(Jogo *jogo){
    jogo->fundo = LoadImage("assets/fundo.png");
    jogo->textura = LoadTextureFromImage(jogo->fundo);
}


void IniciaJogo(Jogo *jogo){
    
    IniciaFundo(jogo);
    IniciaBordas(jogo);
    IniciaCobra(&jogo->cobra);
    IniciaFrutinha(&jogo->frutinha);
    InicializaMenu(jogo);
    InicializaConfig(jogo);
    InicializaLeaderboard(jogo);

    jogo->game_state = menu_prin;

    jogo->tempo = GetTime();
    jogo->cobra.cooldown = 0.2;
}

void DesenhaBordas(Jogo* jogo){

    for(int i = 0; i < 4; i++){
        DrawRectangleRec(jogo->borda[i], GRAY);
    }
}

void DesenhaJogo(Jogo* jogo){
    DesenhaFundo(jogo);
    MostraTempo(jogo);
    DesenhaBordas(jogo);
    DesenhaCobra(&jogo->cobra);
    MostraTempo(jogo);
    DesenhaFrutinha(&jogo->frutinha, &jogo->cobra);
}

void DesenhaFundo(Jogo* jogo){
    
    DrawTexture(jogo->textura, 10, 10, WHITE);
}

int AtualizaRodada(Jogo* jogo){
    
    AtualizaDirecao(&jogo->cobra);
    
    if(GetTime() - jogo->tempo >= 0.2){
        
        jogo->tempo = GetTime();
        AtualizaPosCobra(&jogo->cobra);
        jogo->cobra.cooldown = 0.2;
        jogo->sessao += 0.2;
        CobraGulosa(jogo);
    }
    
    return MataCobra(&jogo->cobra, jogo->borda);
}


void LiberaEspaco(Jogo* jogo){

    LiberaEspacoCobra(&jogo->cobra);
    DescarregaText(jogo);
}

void MostraTempo(Jogo* jogo){
    int minutos, segundos;
    minutos = jogo->sessao/60;
    segundos = (int)(jogo->sessao)%60;
    DrawRectangle(490, 25, 105, 35, (Color){0,0,0,150});
    DrawText(TextFormat("Tempo: %d:%02d", minutos, segundos), 500, 30, 15, RAYWHITE);
    DrawText(TextFormat("Pontos: %03d", jogo->frutinha.pontuacao), 500, 45, 15, RAYWHITE);

}

void CobraGulosa(Jogo* jogo){

    if(CheckCollisionRecs(jogo->cobra.Cabeca->posicao, jogo->frutinha.posicao)){
        
        AumentaCobra(&jogo->cobra);
        jogo->frutinha.pontuacao++;
        jogo->frutinha.existe = false;
    }
}

void FimdeJogotxt(Jogo* jogo){
    DrawText("Você Perdeu!", 225, 200, 40, WHITE);
    DrawText(TextFormat("Tempo da partida anterior: %d:%02d", (int)jogo->sessao/60, (int)jogo->sessao%60), 225, 300, 20, WHITE);
    DrawText(TextFormat("Pontuação: %d", jogo->frutinha.pontuacao), 225, 350, 20, WHITE);
    DrawText("Pressione ENTER para tentar novamente.", 150, 400, 20, WHITE); 
}

void DescarregaText(Jogo* jogo){
    UnloadTexture(jogo->textura);
    UnloadTexture(jogo->frutinha.textura);
}
//DAQUI PRA BAIXO, SOMENTE A PARTE 2--------------------------------------------------------------------------------------------------/

//MENU--------------------------------------------------------------------------------------------------/
void InicializaMenu(Jogo* jogo){
        jogo->menu.qual_button = 0;
        jogo->menu.imagem = LoadImage("assets/cobrinha_menu.jpg");
        ImageResize(&jogo->menu.imagem, LARGURA/2.5, ALTURA/2.5);
        jogo->menu.textura = LoadTextureFromImage(jogo->menu.imagem);
        jogo->menu.start = (Rectangle){LARGURA*0.6, (ALTURA/10)*2, LARGURA*0.3, ALTURA*0.125};
        jogo->menu.leaderboards = (Rectangle){LARGURA*0.6, (ALTURA/10)*4, LARGURA*0.3, ALTURA*0.125};
        jogo->menu.config = (Rectangle){LARGURA*0.6, (ALTURA/10)*6, LARGURA*0.3, ALTURA*0.125};
        jogo->menu.exit = (Rectangle){LARGURA*0.6, (ALTURA/10)*8, LARGURA*0.3, ALTURA*0.125};
        jogo->menu.som = LoadSound("assets/som_menu.wav");
  
}

void DrawMenu(Jogo* jogo){
    switch (jogo->menu.qual_button){
    case 0:
        DrawRectangle(jogo->menu.start.x, jogo->menu.start.y, jogo->menu.start.width+LARGURA*0.01, jogo->menu.start.height+ALTURA*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            jogo->game_state = start;
            PlaySound(jogo->menu.som);
        }
        break;
    case 1:
        DrawRectangle(jogo->menu.leaderboards.x, jogo->menu.leaderboards.y, jogo->menu.leaderboards.width+LARGURA*0.01, jogo->menu.leaderboards.height+ALTURA*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            jogo->game_state = leaderboards;
            PlaySound(jogo->menu.som);
        }
        break;
    case 2:
        DrawRectangle(jogo->menu.config.x, jogo->menu.config.y, jogo->menu.config.width+LARGURA*0.01, jogo->menu.config.height+ALTURA*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            jogo->game_state = config;
            PlaySound(jogo->menu.som);
        }
        break;
    case 3:
        DrawRectangle(jogo->menu.exit.x, jogo->menu.exit.y, jogo->menu.exit.width+LARGURA*0.01, jogo->menu.exit.height+ALTURA*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            jogo->game_state = sair;
        }
        break;
    }
    DrawTexture(jogo->menu.textura, 0, 0, WHITE);
    DrawText("Jogo da Crobinha", LARGURA*0.4, ALTURA*0.1, 40, RAYWHITE);
    DrawRectangleRec(jogo->menu.start, RAYWHITE);
    DrawText("Jogar", jogo->menu.start.x+LARGURA*0.08, jogo->menu.start.y+ALTURA*0.01, 25, BLACK);
    DrawRectangleRec(jogo->menu.leaderboards, RAYWHITE);
    DrawText("Rankings", jogo->menu.leaderboards.x+LARGURA*0.06, jogo->menu.leaderboards.y+ALTURA*0.01, 25, BLACK);
    DrawRectangleRec(jogo->menu.config, RAYWHITE);
    DrawText("Configurações", jogo->menu.config.x+LARGURA*0.03, jogo->menu.config.y+ALTURA*0.01, 25, BLACK);
    DrawRectangleRec(jogo->menu.exit, RAYWHITE);
    DrawText("Sair", jogo->menu.exit.x+LARGURA*0.1, jogo->menu.exit.y+ALTURA*0.01, 25, BLACK);
}

void AtualizaMenu(Jogo* jogo){
    if(IsKeyPressed(KEY_DOWN)){
        jogo->menu.qual_button++;
    }if(IsKeyPressed(KEY_UP)){
        jogo->menu.qual_button--;
    }
    if(jogo->menu.qual_button < 0){
        jogo->menu.qual_button = 3;
        if(jogo->menu.qual_button > 3){
            jogo->menu.qual_button = 0;
        }
    }
}

//CONFIG--------------------------------------------------------------------------------------------------/
void InicializaConfig(Jogo *jogo){
    jogo->config.res660 = (Rectangle){LARGURA*0.60, ALTURA*0.15, LARGURA*0.35, ALTURA*0.2};
    jogo->config.res858 = (Rectangle){LARGURA*0.60, ALTURA*0.45, LARGURA*0.35, ALTURA*0.2};
    jogo->config.voltar = (Rectangle){LARGURA*0.60, ALTURA*0.75, LARGURA*0.35, ALTURA*0.2};
}

void DrawConfig(Jogo *jogo){
    switch (jogo->config.qual_button){
    case 0:
        DrawRectangle(jogo->config.res660.x, jogo->config.res660.y, jogo->config.res660.width+LARGURA*0.01, jogo->config.res660.height+ALTURA*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            PlaySound(jogo->menu.som);
        }
        break;
    case 1:
        DrawRectangle(jogo->config.res858.x, jogo->config.res858.y, jogo->config.res858.width+LARGURA*0.01, jogo->config.res858.height+ALTURA*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            PlaySound(jogo->menu.som);
        }
        break;
    case 2:
        DrawRectangle(jogo->config.voltar.x, jogo->config.voltar.y, jogo->config.voltar.width+LARGURA*0.01, jogo->config.voltar.height+ALTURA*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            PlaySound(jogo->menu.som);
            jogo->game_state = menu_prin;
        }
        break;

    }
    DrawText("Configurações", LARGURA*0.1, ALTURA*0.1, 35, WHITE);
    DrawRectangleRec(jogo->config.res660, WHITE);
    DrawText("660x660", jogo->config.res660.x, jogo->config.res660.y+ALTURA*0.01, 25, BLACK);
    DrawRectangleRec(jogo->config.res858, WHITE);
    DrawText("858x858", jogo->config.res858.x, jogo->config.res858.y+ALTURA*0.01, 25, BLACK);
    DrawRectangleRec(jogo->config.voltar, WHITE);
    DrawText("Voltar", jogo->config.voltar.x, jogo->config.voltar.y+ALTURA*0.01, 25, BLACK);
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
    jogo->leaderboard.voltar = (Rectangle){LARGURA*0.60, ALTURA*0.75, LARGURA*0.35, ALTURA*0.2};
    jogo->leaderboard.qual_button = 0;
}

void DrawLeaderboard(Jogo *jogo){
    switch (jogo->leaderboard.qual_button){
    case 0:
        DrawRectangle(jogo->leaderboard.voltar.x, jogo->leaderboard.voltar.y, jogo->leaderboard.voltar.width+LARGURA*0.01, jogo->leaderboard.voltar.height+ALTURA*0.01, YELLOW);
        if(IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)){
            PlaySound(jogo->menu.som);
            jogo->game_state = menu_prin;
        }
        break;
    }
    DrawText("Leaderboard:", LARGURA*0.1, ALTURA*0.1, 35, WHITE);
    DrawRectangleRec(jogo->leaderboard.voltar, WHITE);
    DrawText("Voltar", jogo->leaderboard.voltar.x, jogo->leaderboard.voltar.y+ALTURA*0.01, 25, BLACK);
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
