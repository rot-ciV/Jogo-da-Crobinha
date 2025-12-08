#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "jogo.h"
#include "snake.h"


int main(){
    //carrega dispositivos de áudio
    InitAudioDevice();
    
    Jogo jogo = {0};

    jogo.jogos = 0;

    int gameOver = 0;
    srand(time(NULL));

    InitWindow(LARGURA, ALTURA, "Snake Game");
    SetTargetFPS(30);
    jogo.resize_var = 1;
    IniciaJogo(&jogo);
    jogo.frutinha.pontuacao = 0;

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(BLACK);
        if(jogo.game_state == menu_prin){
            DrawMenu(&jogo);
            AtualizaMenu(&jogo);
        }else if(jogo.game_state == leaderboards){
            DrawLeaderboard(&jogo);
            AtualizaLeaderboard(&jogo);
        }else if(jogo.game_state == config){
            DrawConfig(&jogo);
            AtualizaConfig(&jogo);
        }else if(jogo.game_state == sair){
            EndDrawing();
            LiberaEspaco(&jogo);
            UnloadMusicStream(jogo.music_game);
            CloseAudioDevice();
            CloseWindow();
            return 0;
        }
        if(!gameOver && jogo.game_state == start){
            gameOver = AtualizaRodada(&jogo);
            DesenhaJogo(&jogo);
        }else if(gameOver && jogo.game_state == start){

            FimdeJogotxt(&jogo);
            
            if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)){
                LiberaEspaco(&jogo);
                UnloadMusicStream(jogo.music_game);
                IniciaJogo(&jogo);
                jogo.frutinha.pontuacao = 0;
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