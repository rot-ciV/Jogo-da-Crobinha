#ifndef FRUTINHA_H
#define FRUTINHA_H

#include "snake.h"

typedef struct{
    Rectangle posicao;
    Color cor;
    bool existe;
    int pontuacao;
}Fruta;

void IniciaFrutinha(Fruta* fruta);
void DesenhaFrutinha(Fruta* fruta, ListaCobra* Cobra);
void AtualizaPosFrutinha(Fruta* fruta, ListaCobra* Cobra);


#endif