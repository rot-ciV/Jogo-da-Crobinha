#ifndef JOGO_H
#define JOGO_H

#define LARGURA 660
#define ALTURA 660
#define STD_SIZE_X 20
#define STD_SIZE_Y 20

#include "snake.h"
#include "frutinha.h"


typedef struct{
    Rectangle start;
    Rectangle config;
    Rectangle leaderboards;
    Rectangle exit;
    Rectangle choose;
    Texture2D textura;
    Image imagem;
    Sound som;
    unsigned short int qual_button;
}Menu;


typedef struct{
    Rectangle res660;
    Rectangle res858;
    Rectangle voltar;
    unsigned short int qual_button;
}Config;

typedef struct{
    Rectangle voltar;
    unsigned short int qual_button;
}Leaderboard;

typedef enum{
    menu_prin, config, leaderboards, start, sair
}Game_state;

typedef struct{

    Rectangle borda[4];
    ListaCobra cobra;
    Fruta frutinha;
    double tempo;
    float sessao;
    Image fundo;
    Texture2D textura;
    Menu menu;
    Config config;
    Leaderboard leaderboard;
    Game_state game_state;
}Jogo;


void IniciaBordas(Jogo* jogo);
void IniciaJogo(Jogo* jogo);
void DesenhaJogo(Jogo* jogo);
void DesenhaFundo(Jogo* jogo);
void DesenhaBordas(Jogo* jogo);
int AtualizaRodada(Jogo* jogo);
void CobraGulosa(Jogo* jogo);
void MostraTempo(Jogo* jogo);
void FimdeJogotxt(Jogo* jogo);
void DescarregaText(Jogo* jogo);
void LiberaEspaco(Jogo* jogo);
void InicializaMenu(Jogo* jogo);
void DrawMenu(Jogo* jogo);
void AtualizaMenu(Jogo* jogo);
void InicializaConfig(Jogo* jogo);
void DrawConfig(Jogo* jogo);
void AtualizaConfig(Jogo* jogo);
void InicializaLeaderboard(Jogo* jogo);
void DrawLeaderboard(Jogo* jogo);
void AtualizaLeaderboard(Jogo* jogo);


#endif