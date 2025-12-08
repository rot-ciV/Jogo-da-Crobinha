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
    UnloadImage(frutinha->foto);
    
}

void DesenhaFrutinha(Fruta* frutinha, ListaCobra* Cobra){
    if(frutinha->existe == false){
        
        PlaySound(frutinha->come_frutinha);
        DrawTexture(frutinha->textura, frutinha->posicao.x, frutinha->posicao.y, WHITE);

    }else if(frutinha->existe == true){
        DrawTexture(frutinha->textura, frutinha->posicao.x, frutinha->posicao.y, WHITE);
    }
}

void DescarregaFrutinha(Fruta* frutinha){
    
    UnloadSound(frutinha->come_frutinha);
    UnloadTexture(frutinha->textura);
}
