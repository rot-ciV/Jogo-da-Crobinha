#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "jogo.h"
#include "mapa.h"

void IniciaMapa(Mapa* mapa, int nivel){

    IniciaFundo(mapa, nivel);
    IniciaBorda(mapa, nivel);
    IniciaTunel(mapa, nivel);
    IniciaObstaculos(mapa, nivel);
}

void DesenhaMapa(Mapa* mapa){

    DesenhaFundo(mapa);
    DesenhaBordas(mapa);
    DesenhaTunel(mapa);
    DesenhaObstaculos(mapa);
}

void DescarregaMapa(Mapa* mapa){

    DescarregaFundo(mapa);
    mapa->numBorda = 0;
    mapa->numTunel = 0;
    mapa->numObstaculos = 0;
}

void IniciaFundo(Mapa* mapa, int nivel){

    Image aux;

    if(nivel == 1){

        Image aux = LoadImage("assets/fundo01.png");
        ImageResize(&aux, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var);
        mapa->texFundo = LoadTextureFromImage(aux);
        SetTextureWrap(mapa->texFundo, TEXTURE_WRAP_REPEAT);
        UnloadImage(aux);
    }

    else if(nivel == 2){

        Image aux = LoadImage("assets/fundo02.png");
        ImageResize(&aux, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var);
        mapa->texFundo = LoadTextureFromImage(aux);
        SetTextureWrap(mapa->texFundo, TEXTURE_WRAP_REPEAT);
        UnloadImage(aux);;

    }

    else if(nivel == 3){
        Image aux = LoadImage("assets/fundo03.png");
        ImageResize(&aux, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var);
        mapa->texFundo = LoadTextureFromImage(aux);
        SetTextureWrap(mapa->texFundo, TEXTURE_WRAP_REPEAT);
        UnloadImage(aux);;

    }
}

void DesenhaFundo(Mapa* mapa){
    
        Rectangle aux = {0, 0, LARGURA*mapa->resize_var, ALTURA*mapa->resize_var};
        Rectangle moldura = {0, 0, LARGURA*mapa->resize_var, ALTURA*mapa->resize_var};
        Vector2 orientacao = {0, 0};
        
        DrawTexturePro(mapa->texFundo, moldura, aux, orientacao, 0.0f, WHITE);
}

void DescarregaFundo(Mapa* mapa){

    UnloadTexture(mapa->texFundo);
}

void IniciaBorda(Mapa* mapa, int nivel){

    if(nivel == 1){
    
        mapa->numBorda = 4;
        //Borda de cima
        mapa->borda[0] = (Rectangle) {0, 0, (LARGURA*mapa->resize_var), 20*mapa->resize_var};
        //Borda da direita
        mapa->borda[1] = (Rectangle) {(LARGURA*mapa->resize_var) - 20*mapa->resize_var, 0, 20*mapa->resize_var, (ALTURA*mapa->resize_var)};
        //Borda de baixo
        mapa->borda[2] = (Rectangle) {0, (ALTURA*mapa->resize_var) - 20*mapa->resize_var, (LARGURA*mapa->resize_var), 20*mapa->resize_var};
        //Borda da esquerda
        mapa->borda[3] = (Rectangle) {0, 0, 20*mapa->resize_var, (ALTURA*mapa->resize_var)};
        
        Image aux = LoadImage("assets/borda01.png");
        ImageResize(&aux, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var);
        mapa->texBorda = LoadTextureFromImage(aux);
        SetTextureWrap(mapa->texBorda, TEXTURE_WRAP_REPEAT);
        UnloadImage(aux);
    }

    else if(nivel == 2){
        mapa->numBorda = 0;
    }

    else if(nivel == 3){
        mapa->numBorda = 0;

    }
}

void DesenhaBordas(Mapa* mapa){

    for(int i = 0; i < mapa->numBorda; i++){

        Rectangle aux = mapa->borda[i];
        Rectangle moldura = {0, 0, aux.width, aux.height};
        Vector2 orientacao = {0, 0};
        
        DrawTexturePro(mapa->texBorda, moldura, aux, orientacao, 0.0f, WHITE);
    }
}

void IniciaTunel(Mapa* mapa, int nivel){

    if(nivel == 1){
        
        mapa->numTunel = 0;
    }

    else if(nivel == 2){

        mapa->numTunel =  4;

        mapa->tunel[0] = (Rectangle) {2*STD_SIZE_X*mapa->resize_var, 16*STD_SIZE_Y*mapa->resize_var, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var};
        mapa->tunel[1] = (Rectangle) {2*STD_SIZE_X*mapa->resize_var, 2*STD_SIZE_Y*mapa->resize_var, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var};
        mapa->tunel[2] = (Rectangle) {30*STD_SIZE_X*mapa->resize_var, 16*STD_SIZE_Y*mapa->resize_var, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var};
        mapa->tunel[3] = (Rectangle) {30*STD_SIZE_X*mapa->resize_var, 30*STD_SIZE_Y*mapa->resize_var, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var};
        
        Image aux = LoadImage("assets/tunel02.png");
        ImageResize(&aux, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var);
        mapa->texTunel = LoadTextureFromImage(aux);
        UnloadImage(aux);
    }

    else if(nivel == 3){

        mapa->numTunel =  4;

        mapa->tunel[0] = (Rectangle) {19*STD_SIZE_X*mapa->resize_var, 25*STD_SIZE_Y*mapa->resize_var, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var};
        mapa->tunel[1] = (Rectangle) {7*STD_SIZE_X*mapa->resize_var, 19*STD_SIZE_Y*mapa->resize_var, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var};
        mapa->tunel[2] = (Rectangle) {25*STD_SIZE_X*mapa->resize_var, 13*STD_SIZE_Y*mapa->resize_var, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var};
        mapa->tunel[3] = (Rectangle) {13*STD_SIZE_X*mapa->resize_var, 7*STD_SIZE_Y*mapa->resize_var, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var};

        Image aux = LoadImage("assets/tunel03.png");
        ImageResize(&aux, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var);
        mapa->texTunel = LoadTextureFromImage(aux);
        UnloadImage(aux);
    }
}

void DesenhaTunel(Mapa* mapa){

    for(int i = 0; i<mapa->numTunel; i++){

        DrawTexture(mapa->texTunel, mapa->tunel[i].x, mapa->tunel[i].y, WHITE);
    }
}

void IniciaObstaculos(Mapa* mapa, int nivel){

     if(nivel == 1){
        
        mapa->numObstaculos = 0;
    }

    else if(nivel == 2){

        mapa->numObstaculos =  4;

        mapa->obstaculos[0] = (Rectangle) {0*STD_SIZE_X*mapa->resize_var, 10*STD_SIZE_Y*mapa->resize_var, LARGURA*mapa->resize_var, 3*STD_SIZE_Y*mapa->resize_var};
        mapa->obstaculos[1] = (Rectangle) {0*STD_SIZE_X*mapa->resize_var, 20*STD_SIZE_Y*mapa->resize_var, LARGURA*mapa->resize_var, 3*STD_SIZE_Y*mapa->resize_var};
        mapa->obstaculos[2] = (Rectangle) {0*STD_SIZE_X*mapa->resize_var, 21*STD_SIZE_Y*mapa->resize_var, 3*STD_SIZE_X*mapa->resize_var,  12*STD_SIZE_Y*mapa->resize_var};
        mapa->obstaculos[3] = (Rectangle) {30*STD_SIZE_X*mapa->resize_var, 0*STD_SIZE_Y*mapa->resize_var, 3*STD_SIZE_X*mapa->resize_var,  12*STD_SIZE_Y*mapa->resize_var};

        Image aux = LoadImage("assets/obstaculo02.png");
        ImageResize(&aux, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var);
        mapa->texObstaculo = LoadTextureFromImage(aux);
        SetTextureWrap(mapa->texObstaculo, TEXTURE_WRAP_REPEAT);
        UnloadImage(aux);
    }

    else if(nivel == 3){

        mapa->numObstaculos = 10;

        mapa->obstaculos[0] = (Rectangle) {3*STD_SIZE_X*mapa->resize_var, 3*STD_SIZE_Y*mapa->resize_var, 3*STD_SIZE_X*mapa->resize_var, 27*STD_SIZE_Y*mapa->resize_var};
        mapa->obstaculos[1] = (Rectangle) {27*STD_SIZE_X*mapa->resize_var, 3*STD_SIZE_Y*mapa->resize_var, 3*STD_SIZE_X*mapa->resize_var, 27*STD_SIZE_Y*mapa->resize_var};
        mapa->obstaculos[2] = (Rectangle) {6*STD_SIZE_X*mapa->resize_var, 15*STD_SIZE_Y*mapa->resize_var, 6*STD_SIZE_X*mapa->resize_var, 3*STD_SIZE_Y*mapa->resize_var};
        mapa->obstaculos[3] = (Rectangle) {21*STD_SIZE_X*mapa->resize_var, 15*STD_SIZE_Y*mapa->resize_var, 6*STD_SIZE_X*mapa->resize_var, 3*STD_SIZE_Y*mapa->resize_var};
        mapa->obstaculos[4] = (Rectangle) {10*STD_SIZE_X*mapa->resize_var, 22*STD_SIZE_Y*mapa->resize_var, 2*STD_SIZE_X*mapa->resize_var, 11*STD_SIZE_Y*mapa->resize_var};
        mapa->obstaculos[5] = (Rectangle) {21*STD_SIZE_X*mapa->resize_var, 22*STD_SIZE_Y*mapa->resize_var, 2*STD_SIZE_X*mapa->resize_var, 11*STD_SIZE_Y*mapa->resize_var};
        mapa->obstaculos[6] = (Rectangle) {12*STD_SIZE_X*mapa->resize_var, 22*STD_SIZE_Y*mapa->resize_var, 9*STD_SIZE_X*mapa->resize_var, 2*STD_SIZE_Y*mapa->resize_var};
        mapa->obstaculos[7] = (Rectangle) {10*STD_SIZE_X*mapa->resize_var, 0*STD_SIZE_Y*mapa->resize_var, 2*STD_SIZE_X*mapa->resize_var, 11*STD_SIZE_Y*mapa->resize_var};
        mapa->obstaculos[8] = (Rectangle) {21*STD_SIZE_X*mapa->resize_var, 0*STD_SIZE_Y*mapa->resize_var, 2*STD_SIZE_X*mapa->resize_var, 11*STD_SIZE_Y*mapa->resize_var};
        mapa->obstaculos[9] = (Rectangle) {12*STD_SIZE_X*mapa->resize_var, 9*STD_SIZE_Y*mapa->resize_var, 9*STD_SIZE_X*mapa->resize_var, 2*STD_SIZE_Y*mapa->resize_var};

        Image aux = LoadImage("assets/obstaculo03.png");
        ImageResize(&aux, STD_SIZE_X*mapa->resize_var, STD_SIZE_Y*mapa->resize_var);
        mapa->texObstaculo = LoadTextureFromImage(aux);
        SetTextureWrap(mapa->texObstaculo, TEXTURE_WRAP_REPEAT);
        UnloadImage(aux);
    }
        
}

void DesenhaObstaculos(Mapa* mapa){

    for(int i = 0; i < mapa->numObstaculos; i++){

        Rectangle aux = mapa->obstaculos[i];
        Rectangle moldura = {0, 0, aux.width, aux.height};
        Vector2 orientacao = {0, 0};
        
        DrawTexturePro(mapa->texObstaculo, moldura, aux, orientacao, 0.0f, WHITE);
    }
}

    