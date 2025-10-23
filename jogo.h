#ifndef JOGO_H
#define JOGO_H

#define LARGURA 660
#define ALTURA 660
#define STD_SIZE_X 20
#define STD_SIZE_Y 20

#include "snake.h"


typedef struct{

    Rectangle borda[4];
    ListaCobra cobra;
    double tempo;
}Jogo;

typedef struct{
    Rectangle quadrado;
    Color cor;
    bool existe;
}Fruta;


void IniciaBordas(Jogo* jogo);
void IniciaJogo(Jogo* jogo);
void DesenhaJogo(Jogo* jogo);
void DesenhaBordas(Jogo* jogo);
int AtualizaRodada(Jogo* jogo, float* tempo_s, Fruta* fruta);
void MostraTempo(Jogo* jogo, float* tempo_s);

void LiberaEspaco(Jogo* jogo);

//funções frutinha
void DesenhaFrutinha(Jogo* jogo, Fruta* fruta);
void IniciaFruta(Fruta* fruta);

#endif