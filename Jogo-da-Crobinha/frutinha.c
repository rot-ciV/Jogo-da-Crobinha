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

    //carregar o som
    fruta->come_fruta = LoadSound("assets/menu_sound_effect_fx.wav");
    SetSoundVolume(fruta->come_fruta, 10.0f);

    //carrega a imagem
    fruta->foto = LoadImage("assets/moranguinho.png");
    ImageResize(&fruta->foto, 20, 20);
    fruta->textura = LoadTextureFromImage(fruta->foto);
    
}

void DesenhaFrutinha(Fruta* fruta, ListaCobra* Cobra){
    if(fruta->existe == false){
        PlaySound(fruta->come_fruta);
        AtualizaPosFrutinha(fruta, Cobra);
        DrawTexture(fruta->textura, fruta->posicao.x, fruta->posicao.y, WHITE);

    }else if(fruta->existe == true){
        DrawTexture(fruta->textura, fruta->posicao.x, fruta->posicao.y, WHITE);
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