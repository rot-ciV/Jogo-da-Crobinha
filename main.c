#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "jogo.h"
#include "snake.h"


int main(){

    Jogo jogo;

    int gameOver = 0;
    float tempo_s = 0;

    InitWindow(LARGURA, ALTURA, "Snake Game");
    SetTargetFPS(30);
    IniciaJogo(&jogo);

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(BLACK);

        if(!gameOver){
            
            gameOver = AtualizaRodada(&jogo, &tempo_s);
            DesenhaJogo(&jogo);
        }else{

            DrawText("Você Perdeu!", 225, 200, 40, WHITE);
            DrawText(TextFormat("Tempo da partida anterior: %d:%02d", (int)tempo_s/60, (int)tempo_s%60), 225, 300, 20, WHITE);
            DrawText("Pressione ENTER para tentar novamente.", 150, 400, 20, WHITE); 

            if(IsKeyPressed(KEY_ENTER)){
                IniciaJogo(&jogo);
                gameOver = 0;
                tempo_s = 0;
            }
        }

        EndDrawing();
    }

    LiberaEspaco(&jogo);
    CloseWindow();
    return 0;
}