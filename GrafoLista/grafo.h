#ifndef GRAFO_H
#define GRAFO_H

void GerarGrafoVazio(int n, int o, int p);
void GerarGrafoAleatorio(int n, int pMax, int o);
void InserirNovoNo(); //colocar um malloc e ver no que da
void RemoveNo(int no);
void InserirNovaAresta(int v1, int v2);
int RetornaAresta(int v1, int v2);
int VerificarAdjacencia(int v1, int v2);
void ListarAdjacencias(int v1);
int RetiraAresta(int v1, int v2);
int RetiraMenor();
int RetiraMaior();
void LimparGrafo();
void Imprime();
void Desenha();
int DFS(int i, int *visitados, int x);
int getNumVertices();
int BFS(int v, int *estados, int x);

#endif
