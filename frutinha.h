#ifndef FRUTINHA_H
#define FRUTINHA_H

#include "snake.h"

typedef struct{
    Rectangle posicao;
    Color cor;
    bool existe;
    int pontuacao;
    Sound come_frutinha;
    Image foto;
    Texture2D textura;
    float resize_var;

}Fruta;

void IniciaFrutinha(Fruta* fruta);
void DesenhaFrutinha(Fruta* fruta, ListaCobra* Cobra);

#endif