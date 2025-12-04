#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_COLOR YELLOW


typedef struct corpo{
    Rectangle posicao;
    Color cor;
    struct corpo* Prox;
    struct corpo* Ant;
}Corpo;

typedef Corpo* TipoApontador;

typedef struct{
    TipoApontador Cabeca;
    TipoApontador Rabo; 
    int tamanho;
    int direcao;
    double cooldown;
}ListaCobra;


void FLVCobra(ListaCobra* Cobra);
void IniciaCobra(ListaCobra* Cobra);
void AtualizaDirecao(ListaCobra* Cobra);
void AtualizaPosCobra(ListaCobra* Cobra);
void DesenhaCobra(ListaCobra* Cobra);
void AumentaCobra(ListaCobra* Cobra);
int MataCobra(ListaCobra* Cobra, Rectangle borda[4]);
void cruzaCobra(ListaCobra* Cobra, Rectangle borda[4]);

void LiberaEspacoCobra(ListaCobra* cobra);
#endif