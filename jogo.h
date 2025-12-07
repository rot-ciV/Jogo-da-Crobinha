#ifndef JOGO_H
#define JOGO_H

#define LARGURA 660
#define ALTURA 660
#define STD_SIZE_X 20
#define STD_SIZE_Y 20

#include "snake.h"
#include "frutinha.h"
#include "mapa.h"


typedef struct{
    Rectangle start;
    Rectangle config;
    Rectangle leaderboards;
    Rectangle exit;
    Rectangle choose;
    Texture2D textura;
    Image imagem;
    Sound som;
    int qual_button;
}Menu;


typedef struct{
    Rectangle res660;
    Rectangle res858;
    Rectangle voltar;
    int qual_button;
}Config;

typedef struct{
    Rectangle voltar;
    int qual_button;
}Leaderboard;

typedef enum{
    menu_prin, config, leaderboards, start, sair
}Game_state;

// Retirado: borda, tunel, fundo,
//Colocado: Struct Mapa e int Nivel
typedef struct{

    Mapa mapa;
    int nivel;
    ListaCobra cobra;
    Fruta frutinha;
    double tempo;
    float sessao;
    Texture2D textura;
    Menu menu;
    Config config;
    Leaderboard leaderboard;
    Game_state game_state;
    float resize_var;
    Music music_game;
}Jogo;

/*
Funções Retiradas:

- IniciaFundo
- IniciaBordas
- DesenhaBordas
- DesenhaFundo
- DefineTunel (Nome trocado para IniciaTunel em mapa)
- DesenhaTunel
*/

void IniciaJogo(Jogo* jogo);
void DesenhaJogo(Jogo* jogo);
int AtualizaRodada(Jogo* jogo);
void tocaMusica(Jogo* jogo);
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
void UsaTunel(Jogo* jogo);
void TrocaMapa(Jogo* jogo);
int MataCobra(Jogo* jogo);
void AtualizaPosFrutinha(Jogo* jogo);


#endif