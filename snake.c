#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "snake.h"
#include "jogo.h"


void FLVCobra(ListaCobra* Cobra){ 

    Cobra->Rabo = NULL;
    Cobra->Cabeca = NULL;
    Cobra->tamanho = 0;
    Cobra->morte = LoadSound("assets/BOOM.mp3");
}

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

    int tamanhoBloco_X = STD_SIZE_X * Cobra->resize_var;
    int tamanhoBloco_Y = STD_SIZE_Y * Cobra->resize_var;
    int pos_inicial_X = 320 * Cobra->resize_var;
    int pos_inicial_Y = 580 * Cobra->resize_var;

    Cobra->Cabeca->posicao = (Rectangle) {
        pos_inicial_X, 
        pos_inicial_Y, 
        tamanhoBloco_X, 
        tamanhoBloco_Y
    };

    Aux->posicao = (Rectangle) {
        pos_inicial_X, 
        pos_inicial_Y + tamanhoBloco_Y, 
        tamanhoBloco_X, 
        tamanhoBloco_Y
    };

    Cobra->Rabo->posicao = (Rectangle) {
        pos_inicial_X, 
        pos_inicial_Y + (2*tamanhoBloco_Y), 
        tamanhoBloco_X, 
        tamanhoBloco_Y
    };
    
    /*A linha acima implementa a struct "Rectangle". Em ordem: 
      Rectangle.x = 660/2 - 20, 
      Rectangle.y = 660 - 20 - 50, 
      Rectangle.width ((largura*Cobra->resize_var)) = 20, 
      Rectangle.height ((altura*Cobra->resize_var)) =( 20"

    *Cobra->resize_var)  O "Rectangle" é uma struct que cotem 4 dados: (Altura*Cobra->resize_var), ((Largura*Co*Cobra->resize_var)bra->resize_var), x e y, sendo esses últimos as coordenadas do canto superior esquerdo do retângulo
      Assim, o retangulo cresce para a direita com o valor da (largura*Cobra->resize_var) e para baixo com base no valor da (altura*Cobra->resize_var)*/

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

        case 0: Nova_Posicao.y -= (STD_SIZE_Y*Cobra->resize_var); break;
        case 1: Nova_Posicao.x += (STD_SIZE_X*Cobra->resize_var); break;
        case 2: Nova_Posicao.y += (STD_SIZE_Y*Cobra->resize_var); break;
        case 3: Nova_Posicao.x -= (STD_SIZE_X*Cobra->resize_var); break;
    }

    Cobra->Cabeca->posicao = Nova_Posicao;
        
}

void DesenhaCobra(ListaCobra* Cobra){

    TipoApontador Pintor = Cobra->Cabeca;
    int par = 2;
    while(Pintor != NULL){
        if(par %2 == 1){
            DrawRectangleRec(Pintor->posicao, BLACK);
        }else{
            DrawRectangleRec(Pintor->posicao, Pintor->cor);
        }par++;
        Pintor = Pintor->Prox;
    }
    DrawRectangle(Cobra->Cabeca->posicao.x+(3*Cobra->resize_var), Cobra->Cabeca->posicao.y+(3*Cobra->resize_var), 
                   Cobra->Cabeca->posicao.width/(5/Cobra->resize_var), Cobra->Cabeca->posicao.height/(5/Cobra->resize_var), BLACK);

    DrawRectangle(Cobra->Cabeca->posicao.x+(14*Cobra->resize_var), Cobra->Cabeca->posicao.y+(3*Cobra->resize_var), 
                   Cobra->Cabeca->posicao.width/(5/Cobra->resize_var), Cobra->Cabeca->posicao.height/(5/Cobra->resize_var), BLACK);
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

/* A função cruzaCobra muda de funcionalidade depedendo do mapa que estamos, se for mapa 1, vê se a cobra bateu 
na borda e retorna 1 para mata cobra, se for os outros mapas, apenas teleporta a cobra. 
*/
void cruzaCobra(ListaCobra* Cobra){

    if(Cobra->Cabeca->posicao.y < 0){
        Cobra->Cabeca->posicao.y =  ALTURA*Cobra->resize_var - STD_SIZE_Y*Cobra->resize_var;
    }
    else if(Cobra->Cabeca->posicao.x < 0){
        Cobra->Cabeca->posicao.x = LARGURA*Cobra->resize_var - STD_SIZE_X*Cobra->resize_var;
    }
    else if(Cobra->Cabeca->posicao.y >= ALTURA*Cobra->resize_var){
        Cobra->Cabeca->posicao.y = 0;
    }
    else if(Cobra->Cabeca->posicao.x >= LARGURA*Cobra->resize_var){
        Cobra->Cabeca->posicao.x = 0;
    }

}


void LiberaEspacoCobra(ListaCobra* Cobra){

    TipoApontador Liberador;
    TipoApontador Aux = Cobra->Cabeca;
    while(Aux != NULL){

        Liberador = Aux;
        Aux = Aux->Prox;
        free(Liberador);
    }

    UnloadSound(Cobra->morte);
    FLVCobra(Cobra);
}