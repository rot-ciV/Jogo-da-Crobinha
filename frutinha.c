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
}

void DesenhaFrutinha(Fruta* fruta){
    if(fruta->existe == false){
        fruta->posicao.x = 10+20*(rand()%30);
        fruta->posicao.y = 10+20*(rand()%30);
        fruta->existe = true;
        DrawRectangleRec(fruta->posicao, fruta->cor);        
    }else if(fruta->existe == true){
        DrawRectangleRec(fruta->posicao, fruta->cor);
    }
}