#ifndef JOGO_H
#define JOGO_H

#define LARGURA 660
#define ALTURA 660
#define STD_SIZE_X 50
#define STD_SIZE_Y 50

#include "snake.h"
#include "frutinha.h"

typedef struct{

    Rectangle borda[4];
    ListaCobra cobra;
    Fruta frutinha;
    double tempo;
}Jogo;


void IniciaBordas(Jogo* jogo);
void IniciaJogo(Jogo* jogo);
void DesenhaJogo(Jogo* jogo);
void DesenhaBordas(Jogo* jogo);
int AtualizaRodada(Jogo* jogo, float* tempo_s);
void CobraGulosa(Jogo* jogo);
void MostraTempo(Jogo* jogo, float* tempo_s);

void LiberaEspaco(Jogo* jogo);

//funções frutinha


#endif