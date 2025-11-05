#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "jogo.h"
#include "snake.h"


int main(){
    //carrega dispositivos de áudio
    InitAudioDevice();
    
    Jogo jogo;

    int gameOver = 0;
    srand(time(NULL));

    InitWindow(LARGURA, ALTURA, "Snake Game");
    SetTargetFPS(30);
    IniciaJogo(&jogo);

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(BLACK);

        if(!gameOver){
            
            gameOver = AtualizaRodada(&jogo);
            DesenhaJogo(&jogo);
        }else{

            FimdeJogotxt(&jogo);
            
            if(IsKeyPressed(KEY_ENTER)){
                IniciaJogo(&jogo);
                gameOver = 0;
                jogo.sessao = 0;
            }
        }

        EndDrawing();
    }

    LiberaEspaco(&jogo);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}