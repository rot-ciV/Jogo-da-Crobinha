#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "jogo.h"
#include "snake.h"


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
}

int AtualizaRodada(Jogo* jogo){
    
    AtualizaDirecao(&jogo->cobra);

    if(GetTime() - jogo->tempo >= 0.2){
        
        jogo->tempo = GetTime();
        AtualizaPosCobra(&jogo->cobra);
        jogo->cobra.cooldown = 0.2;
    }

    return MataCobra(&jogo->cobra, jogo->borda);
}


void LiberaEspaco(Jogo* jogo){

    LiberaEspacoCobra(&jogo->cobra);
}


