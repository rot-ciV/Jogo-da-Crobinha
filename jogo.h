#ifndef JOGO_H
#define JOGO_H

#define LARGURA 660
#define ALTURA 660
#define STD_SIZE_X 20
#define STD_SIZE_Y 20

#include "snake.h"
#include "frutinha.h"

typedef struct{

    Rectangle borda[4];
    ListaCobra cobra;
    Fruta frutinha;
    double tempo;
    float sessao;
    Image fundo;
    Texture2D textura;
    
}Jogo;


void IniciaBordas(Jogo* jogo);
void IniciaJogo(Jogo* jogo);
void DesenhaJogo(Jogo* jogo);
void DesenhaBordas(Jogo* jogo);
int AtualizaRodada(Jogo* jogo);
void CobraGulosa(Jogo* jogo);
void MostraTempo(Jogo* jogo);
void FimdeJogotxt(Jogo* jogo);
void LiberaEspaco(Jogo* jogo);

//funções frutinha


#endif