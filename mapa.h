#ifndef MAPA_H
#define MAPA_H



typedef struct{

    int numBorda;
    int numTunel;
    int numObstaculos;

    Rectangle borda[20];
    Rectangle tunel[8];
    Rectangle obstaculos[30];
    Image im_fundo;
    Texture2D fundo;
    float resize_var;
}Mapa;


void IniciaMapa(Mapa* mapa, int nivel);
void DesenhaMapa(Mapa* mapa);
void DescarregaMapa(Mapa* mapa);

void IniciaFundo(Mapa* mapa, int nivel);
void DesenhaFundo(Mapa* mapa);
void DescarregaFundo(Mapa* mapa);

void IniciaBorda(Mapa* mapa, int nivel);
void DesenhaBordas(Mapa* mapa);

void IniciaTunel(Mapa* mapa, int nivel);
void DesenhaTunel(Mapa* mapa);

void IniciaObstaculos(Mapa* mapa, int nivel);
void DesenhaObstaculos(Mapa* mapa);




#endif