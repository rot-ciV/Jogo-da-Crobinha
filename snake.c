#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "snake.h"
#include "jogo.h"


void FLVCobra(ListaCobra* Cobra){ 

    Cobra->Rabo = NULL;
    Cobra->Cabeca = NULL;
    Cobra->tamanho = 0;
    Cobra->morte = LoadSound("assets/morreu.wav");
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

    Cobra->Cabeca->posicao = (Rectangle) {(LARGURA*Cobra->resize_var)/2 - (STD_SIZE_X*Cobra->resize_var), (ALTURA*Cobra->resize_var) - ((STD_SIZE_Y*Cobra->resize_var)*Cobra->resize_var) - 50*Cobra->resize_var, (STD_SIZE_X*Cobra->resize_var), (STD_SIZE_Y*Cobra->resize_var)};
    Aux->posicao = (Rectangle) {(LARGURA*Cobra->resize_var)/2 - (STD_SIZE_X*Cobra->resize_var), (ALTURA*Cobra->resize_var) - ((STD_SIZE_Y*Cobra->resize_var)*Cobra->resize_var) - 50*Cobra->resize_var + (STD_SIZE_Y*Cobra->resize_var), (STD_SIZE_X*Cobra->resize_var), (STD_SIZE_Y*Cobra->resize_var)};
    Cobra->Rabo->posicao = (Rectangle) {(LARGURA*Cobra->resize_var)/2 - (STD_SIZE_X*Cobra->resize_var), (ALTURA*Cobra->resize_var) - ((STD_SIZE_Y*Cobra->resize_var)*Cobra->resize_var) - 50*Cobra->resize_var + 2*(STD_SIZE_Y*Cobra->resize_var), (STD_SIZE_X*Cobra->resize_var), (STD_SIZE_Y*Cobra->resize_var)};

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
            DrawRectangleRec(Pintor->posicao, GOLD);
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

int MataCobra(ListaCobra* Cobra, Rectangle borda[4], int nivel){

    TipoApontador Testadouro = Cobra->Cabeca->Prox;
    while(Testadouro != NULL){

        if(Testadouro->posicao.x == Cobra->Cabeca->posicao.x && Testadouro->posicao.y == Cobra->Cabeca->posicao.y){
            PlaySound(Cobra->morte);
            return 1;
        }

        Testadouro = Testadouro->Prox;
    }
    return cruzaCobra(Cobra, borda, nivel);
}

/* A função cruzaCobra muda de funcionalidade depedendo do mapa que estamos, se for mapa 1, vê se a cobra bateu 
na borda e retorna 1 para mata cobra, se for os outros mapas, apenas teleporta a cobra. 
*/
int cruzaCobra(ListaCobra* Cobra, Rectangle borda[4], int nivel){

    if(nivel == 1){
        if(CheckCollisionRecs(borda[0], Cobra->Cabeca->posicao)){
            PlaySound(Cobra->morte);
        return 1;
        }
        else if(CheckCollisionRecs(borda[1], Cobra->Cabeca->posicao)){
            PlaySound(Cobra->morte);
        return 1;
        }
        else if(CheckCollisionRecs(borda[2], Cobra->Cabeca->posicao)){
            PlaySound(Cobra->morte);
        return 1;
        }
        else if(CheckCollisionRecs(borda[3], Cobra->Cabeca->posicao)){
            PlaySound(Cobra->morte);
        return 1;
        }

        return 0;
    }

    if(CheckCollisionRecs(borda[0], Cobra->Cabeca->posicao)){
        Cobra->Cabeca->posicao.y = borda[2].y-(STD_SIZE_Y*Cobra->resize_var);
    }
    else if(CheckCollisionRecs(borda[1], Cobra->Cabeca->posicao)){
        Cobra->Cabeca->posicao.x = borda[3].x+(STD_SIZE_X*Cobra->resize_var);
    }
    else if(CheckCollisionRecs(borda[2], Cobra->Cabeca->posicao)){
        Cobra->Cabeca->posicao.y = borda[0].y;
    }
    else if(CheckCollisionRecs(borda[3], Cobra->Cabeca->posicao)){
        Cobra->Cabeca->posicao.x = borda[1].x;
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