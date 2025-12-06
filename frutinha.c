#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "frutinha.h"
#include "jogo.h"

void IniciaFrutinha(Fruta* frutinha){
    frutinha->cor = RED;
    frutinha->existe = false;
    frutinha->posicao.height = (STD_SIZE_Y*frutinha->resize_var);
    frutinha->posicao.width = (STD_SIZE_X*frutinha->resize_var);

    //carregar o som
    frutinha->come_frutinha = LoadSound("assets/menu_sound_effect_fx.wav");
    SetSoundVolume(frutinha->come_frutinha, 10.0f);

    //carrega a imagem
    frutinha->foto = LoadImage("assets/moranguinho.png");
    ImageResize(&frutinha->foto, 20*frutinha->resize_var, 20*frutinha->resize_var);
    frutinha->textura = LoadTextureFromImage(frutinha->foto);
    
}

void DesenhaFrutinha(Fruta* frutinha, ListaCobra* Cobra){
    if(frutinha->existe == false){
        PlaySound(frutinha->come_frutinha);
        AtualizaPosFrutinha(frutinha, Cobra);
        DrawTexture(frutinha->textura, frutinha->posicao.x, frutinha->posicao.y, WHITE);

    }else if(frutinha->existe == true){
        DrawTexture(frutinha->textura, frutinha->posicao.x, frutinha->posicao.y, WHITE);
    }
}

void AtualizaPosFrutinha(Fruta* frutinha, ListaCobra* Cobra){

    TipoApontador testadouro = Cobra->Cabeca;
    if(frutinha->pontuacao < 2 || frutinha->pontuacao > 4){
        frutinha->posicao.x = 10*frutinha->resize_var+(STD_SIZE_X*frutinha->resize_var)*(rand()%((int)((LARGURA*frutinha->resize_var)/(STD_SIZE_X*frutinha->resize_var))-1));
        frutinha->posicao.y = 10*frutinha->resize_var+(STD_SIZE_Y*frutinha->resize_var)*(rand()%((int)((ALTURA*frutinha->resize_var)/(STD_SIZE_Y*frutinha->resize_var))-1));
    }else{
        frutinha->posicao.x = (STD_SIZE_X*frutinha->resize_var)*(rand()%((int)((LARGURA*frutinha->resize_var)/(STD_SIZE_X*frutinha->resize_var))-1));
        frutinha->posicao.y = (STD_SIZE_Y*frutinha->resize_var)*(rand()%((int)((ALTURA*frutinha->resize_var)/(STD_SIZE_Y*frutinha->resize_var))-1));
    }
    frutinha->existe = true;

    while(testadouro != NULL){

        if(CheckCollisionRecs(testadouro->posicao, frutinha->posicao)){
            
            frutinha->posicao.x = 10*frutinha->resize_var+(20*(rand()%(int)(30*frutinha->resize_var))*frutinha->resize_var);
            frutinha->posicao.y = 10*frutinha->resize_var+(20*(rand()%(int)(30*frutinha->resize_var))*frutinha->resize_var);
            testadouro = Cobra->Cabeca;
            continue;
        }

        testadouro = testadouro->Prox;
    } 
}