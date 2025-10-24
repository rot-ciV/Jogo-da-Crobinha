#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "snake.h"
#include "jogo.h"


/*IMPLEMENTADO - COMPLETO*/
void FLVCobra(ListaCobra* Cobra){ 

    Cobra->Rabo = NULL;
    Cobra->Cabeca = NULL;
    Cobra->tamanho = 0;
}

/*IMPLEMENTADO - COMPLETO*/
void IniciaCobra(ListaCobra* Cobra){ 

    FLVCobra(Cobra);
    TipoApontador Aux;

    Cobra->Cabeca = malloc(sizeof(Corpo));
    Cobra->Cabeca->Ant = NULL;

    Cobra->Rabo = malloc(sizeof(Corpo));
    Cobra->Rabo->Prox = NULL;

    Aux = malloc(sizeof(Corpo));
    Cobra->Cabeca->Prox = Aux;
    Aux->Ant = Cobra->Cabeca;
    Cobra->Rabo->Ant = Aux;
    Aux->Prox = Cobra->Rabo;

    Cobra->Cabeca->cor = SNAKE_COLOR;
    Aux->cor = SNAKE_COLOR;
    Cobra->Rabo->cor = SNAKE_COLOR;

    Cobra->Cabeca->posicao = (Rectangle) {LARGURA/2 - STD_SIZE_X, ALTURA - STD_SIZE_Y -10, STD_SIZE_X, STD_SIZE_Y};
    Aux->posicao = (Rectangle) {LARGURA/2 - STD_SIZE_X, ALTURA - STD_SIZE_Y - 10 + STD_SIZE_Y, STD_SIZE_X, STD_SIZE_Y};
    Cobra->Rabo->posicao = (Rectangle) {LARGURA/2 - STD_SIZE_X, ALTURA - STD_SIZE_Y -10 + 2*STD_SIZE_Y, STD_SIZE_X, STD_SIZE_Y};

    /*A linha acima implementa a struct "Rectangle". Em ordem: 
      Rectangle.x = 660/2 - 20, 
      Rectangle.y = 660 - 20 - 10, 
      Rectangle.width (largura) = 20, 
      Rectangle.height (altura) = 20"

      O "Rectangle" é uma struct que cotem 4 dados: Altura, Largura, x e y, sendo esses últimos as coordenadas do canto superior esquerdo do retângulo
      Assim, o retangulo cresce para a direita com o valor da largura e para baixo com base no valor da altura*/

    Cobra->direcao = 0;
    Cobra->tamanho = 3;
}

void AtualizaDirecao(ListaCobra* Cobra){

    if(IsKeyPressed(KEY_UP) && Cobra->direcao != 2 && GetTime() - Cobra->cooldown > 0.2){
        Cobra->direcao = 0;
        Cobra->cooldown = GetTime();
    }
    if(IsKeyPressed(KEY_RIGHT) && Cobra->direcao != 3 && GetTime() - Cobra->cooldown > 0.2){
        Cobra->direcao = 1;
        Cobra->cooldown = GetTime();
    }
    if(IsKeyPressed(KEY_DOWN) && Cobra->direcao != 0 && GetTime() - Cobra->cooldown > 0.2){
        Cobra->direcao = 2;
        Cobra->cooldown = GetTime();
    }
    if(IsKeyPressed(KEY_LEFT) && Cobra->direcao != 1 && GetTime() - Cobra->cooldown > 0.2){
        Cobra->direcao = 3;
        Cobra->cooldown = GetTime();
    }
}

void AtualizaPosCobra(ListaCobra* Cobra){

    TipoApontador Aux;
    Aux = Cobra->Rabo;
    Cobra->Rabo = Aux->Ant;
    Cobra->Rabo->Prox = NULL;
    Aux->Prox = Cobra->Cabeca;
    Cobra->Cabeca->Ant = Aux;
    Aux->Ant = NULL;
    Cobra->Cabeca = Aux;

    Rectangle Nova_Posicao = Cobra->Cabeca->Prox->posicao;

    switch (Cobra->direcao){

        case 0: Nova_Posicao.y -= STD_SIZE_Y; break;
        case 1: Nova_Posicao.x += STD_SIZE_X; break;
        case 2: Nova_Posicao.y += STD_SIZE_Y; break;
        case 3: Nova_Posicao.x -= STD_SIZE_X; break;
    }

    Cobra->Cabeca->posicao = Nova_Posicao;
        
}

void DesenhaCobra(ListaCobra* Cobra){

    TipoApontador Pintor = Cobra->Cabeca;

    while(Pintor != NULL){

        DrawRectangleRec(Pintor->posicao, Pintor->cor);
        Pintor = Pintor->Prox;
    }
}

void AumentaCobra(ListaCobra* Cobra){

    Cobra->Rabo->Prox = malloc(sizeof(Corpo));
    Cobra->Rabo->Prox->posicao = Cobra->Rabo->posicao; 
    Cobra->Rabo->Prox->Ant = Cobra->Rabo;
    Cobra->Rabo->Prox->cor = SNAKE_COLOR;
    Cobra->Rabo = Cobra->Rabo->Prox;
    Cobra->Rabo->Prox = NULL;
    Cobra->tamanho++;
}

int MataCobra(ListaCobra* Cobra, Rectangle borda[4]){

    TipoApontador Testadouro = Cobra->Cabeca->Prox;
    while(Testadouro != NULL){

        if(Testadouro->posicao.x == Cobra->Cabeca->posicao.x && Testadouro->posicao.y == Cobra->Cabeca->posicao.y){
            return 1;
        }

        Testadouro = Testadouro->Prox;
    }

    for(int i = 0; i < 4; i++){

        if(CheckCollisionRecs(Cobra->Cabeca->posicao, borda[i])){
            return 1;
        }
    }

    return 0;
}


void LiberaEspacoCobra(ListaCobra* Cobra){

    TipoApontador Liberador;
    TipoApontador Aux = Cobra->Cabeca;
    while(Aux != NULL){

        Liberador = Aux;
        Aux = Aux->Prox;
        free(Liberador);
    }

    FLVCobra(Cobra);
}