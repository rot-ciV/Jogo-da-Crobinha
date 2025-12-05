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
        aux = LoadImage("assets/fundo01.png");

        mapa->fundo = LoadTextureFromImage(aux);
        UnloadImage(aux);
    }

    else if(nivel == 2){
        aux = LoadImage("assets/fundo02.png");

        mapa->fundo = LoadTextureFromImage(aux);
        UnloadImage(aux);

    }

    else if(nivel == 3){
        aux = LoadImage("assets/fundo01.png");

        mapa->fundo = LoadTextureFromImage(aux);
        UnloadImage(aux);

    }
}

void DesenhaFundo(Mapa* mapa){
    
    DrawTexture(mapa->fundo, 10, 10, WHITE);
}

void DescarregaFundo(Mapa* mapa){

    UnloadTexture(mapa->fundo);
}

void IniciaBorda(Mapa* mapa, int nivel){

    if(nivel == 1){
    
        mapa->numBorda = 4;
        //Borda de cima
        mapa->borda[0] = (Rectangle) {0, 0, LARGURA, 10};
        //Borda da direita
        mapa->borda[1] = (Rectangle) {LARGURA - 10, 0, 10, ALTURA};
        //Borda de baixo
        mapa->borda[2] = (Rectangle) {0, ALTURA - 10, LARGURA, 10};
        //Borda da esquerda
        mapa->borda[3] = (Rectangle) {0, 0, 10, ALTURA};   
    }

    else if(nivel == 2){
        mapa->numBorda = 0;
    }

    else if(nivel == 3){

        mapa->numBorda = 4;
        //Borda de cima
        mapa->borda[0] = (Rectangle) {0, 0, LARGURA, 10};
        //Borda da direita
        mapa->borda[1] = (Rectangle) {LARGURA - 10, 0, 10, ALTURA};
        //Borda de baixo
        mapa->borda[2] = (Rectangle) {0, ALTURA - 10, LARGURA, 10};
        //Borda da esquerda
        mapa->borda[3] = (Rectangle) {0, 0, 10, ALTURA};
    }
}

void DesenhaBordas(Mapa* mapa){

    for(int i = 0; i < mapa->numBorda; i++){

        DrawRectangleRec(mapa->borda[i], GRAY);
    }
}

void IniciaTunel(Mapa* mapa, int nivel){

    if(nivel == 1){
        
        mapa->numTunel = 0;
    }

    else if(nivel == 2){

        mapa->numTunel =  2;

        mapa->tunel[0] = (Rectangle) {20, 20, STD_SIZE_X, STD_SIZE_Y};
        mapa->tunel[1] = (Rectangle) {100, 100, STD_SIZE_X, STD_SIZE_Y};
    }

    else if(nivel == 3){

        mapa->numTunel =  2;

        mapa->tunel[0] = (Rectangle) {100, 100, STD_SIZE_X, STD_SIZE_Y};
        mapa->tunel[1] = (Rectangle) {200, 200, STD_SIZE_X, STD_SIZE_Y};
    }
}

void DesenhaTunel(Mapa* mapa){

    for(int i = 0; i<mapa->numTunel; i++){

        DrawRectangleRec(mapa->tunel[i], BROWN);
    }
}

void IniciaObstaculos(Mapa* mapa, int nivel){

     if(nivel == 1){
        
        mapa->numObstaculos = 0;
    }

    else if(nivel == 2){

        mapa->numObstaculos =  2;

        mapa->obstaculos[0] = (Rectangle) {160, 160, STD_SIZE_X, STD_SIZE_Y};
        mapa->obstaculos[1] = (Rectangle) {300, 300, STD_SIZE_X, STD_SIZE_Y};
    }

    else if(nivel == 3){

        mapa->numObstaculos =  2;

        mapa->obstaculos[0] = (Rectangle) {80, 80, STD_SIZE_X, STD_SIZE_Y};
        mapa->obstaculos[1] = (Rectangle) {180, 180, STD_SIZE_X, STD_SIZE_Y};
    }
}

void DesenhaObstaculos(Mapa* mapa){

    for(int i = 0; i < mapa->numObstaculos; i++){

        DrawRectangleRec(mapa->tunel[i], RED);
    }
}

    