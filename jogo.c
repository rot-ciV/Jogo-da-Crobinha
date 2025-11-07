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
    DrawRectangle(485, 45, 75, 35, (Color){0,0,0,150});
    DrawText(TextFormat("%d:%02d", minutos, segundos), 500, 50, 30, RAYWHITE);
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
