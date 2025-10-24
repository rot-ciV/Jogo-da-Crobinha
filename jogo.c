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


void IniciaJogo(Jogo *jogo){
    
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

    DesenhaBordas(jogo);
    DesenhaCobra(&jogo->cobra);
    DesenhaFrutinha(&jogo->frutinha, &jogo->cobra);
}

int AtualizaRodada(Jogo* jogo, float* tempo_s){
    
    AtualizaDirecao(&jogo->cobra);
    
    if(GetTime() - jogo->tempo >= 0.2){
        
        jogo->tempo = GetTime();
        AtualizaPosCobra(&jogo->cobra);
        jogo->cobra.cooldown = 0.2;
        *tempo_s += 0.2;
        CobraGulosa(jogo);
    }
    
    MostraTempo(jogo, tempo_s);
    return MataCobra(&jogo->cobra, jogo->borda);
}


void LiberaEspaco(Jogo* jogo){

    LiberaEspacoCobra(&jogo->cobra);
}

void MostraTempo(Jogo* jogo, float* tempo_s){
    int minutos, segundos;
    minutos = *tempo_s/60;
    segundos = (int)*tempo_s%60;
    DrawText(TextFormat("%d:%02d", minutos, segundos), 500, 50, 30, RAYWHITE);
}

void CobraGulosa(Jogo* jogo){

    if(CheckCollisionRecs(jogo->cobra.Cabeca->posicao, jogo->frutinha.posicao)){
        
        AumentaCobra(&jogo->cobra);
        jogo->frutinha.existe = false;
    }
}