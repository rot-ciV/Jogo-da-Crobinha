#ifndef FRUTINHA_H
#define FRUTINHA_H



typedef struct{
    Rectangle posicao;
    Color cor;
    bool existe;
}Fruta;

void IniciaFrutinha(Fruta* fruta);
void DesenhaFrutinha(Fruta* fruta);


#endif