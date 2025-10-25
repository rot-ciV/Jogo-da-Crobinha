#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "frutinha.h"
#include "jogo.h"

void IniciaFrutinha(Fruta* fruta){
    fruta->cor = RED;
    fruta->existe = false;
    fruta->posicao.height = STD_SIZE_Y;
    fruta->posicao.width = STD_SIZE_X;
    fruta->pontuacao = 0;
}

void DesenhaFrutinha(Fruta* fruta, ListaCobra* Cobra){
    if(fruta->existe == false){

        AtualizaPosFrutinha(fruta, Cobra);
        DrawRectangleRec(fruta->posicao, fruta->cor);

    }else if(fruta->existe == true){

        DrawRectangleRec(fruta->posicao, fruta->cor);
    }
}

void AtualizaPosFrutinha(Fruta* frutinha, ListaCobra* Cobra){

    TipoApontador testadouro = Cobra->Cabeca;
    frutinha->posicao.x = 10+STD_SIZE_X*((int)rand()%((LARGURA/STD_SIZE_X)-1));
    frutinha->posicao.y = 10+STD_SIZE_Y*((int)rand()%((ALTURA/STD_SIZE_Y)-1));
    frutinha->existe = true;

    while(testadouro != NULL){

        if(CheckCollisionRecs(testadouro->posicao, frutinha->posicao)){

            frutinha->posicao.x = 10+20*(rand()%30);
            frutinha->posicao.y = 10+20*(rand()%30);
            testadouro = Cobra->Cabeca;
            continue;
        }

        testadouro = testadouro->Prox;
    } 
}