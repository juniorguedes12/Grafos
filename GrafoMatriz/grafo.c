#include "grafo.h"
#include "fila.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int matriz[MAX][MAX];
int numVertice = 0;
int orientado;
int ponderado;

#define inicial 1
#define esperando 2
#define visitado 3

void GerarGrafoVazio(int n, int o, int p){
  int i, j;
  numVertice = n;
  orientado = o;
  ponderado = p;
  for (i = 0; i < n; i++){
    for (j = 0; j < n; j++){
      matriz[i][j] = 0;
    }
  }
}

void GerarGrafoAleatorio(int n, int pMax, int o){
  int i, j;
  numVertice = n;
  orientado = o;
  if (pMax == 1)
  ponderado = 0;
  else
  ponderado = 1;
  if (!orientado){
    for (i = 0; i < n; i++){
      for (j = 0; j < i+1; j++){
        if (i != j)
        matriz[i][j] = matriz[j][i] = rand() % (pMax+1);
      }
    }
  }
  else{
    for (i = 0; i < n; i++){
      for (j = 0; j < n; j++){
        if (i != j)
        matriz[i][j] = rand() % (pMax+1);
      }
    }
  }
}

void InserirNovoNo(){
  int i;
  numVertice += 1;
  for (i = 0; i < numVertice; i++){
    matriz[i][numVertice-1] = matriz[numVertice-1][i] = 0;
  }
}


void InserirNovaAresta(int v1, int v2){
  if (v1 > numVertice || v2 > numVertice){
    printf("\nInsira vertices validas!\n");
  }
  else{
    int peso;
    if (orientado){
      if (ponderado){
        printf("\nDigite o peso da nova aresta: ");
        scanf("%d",&peso);
        matriz[v1-1][v2-1] = peso;
      }
      else{
        matriz[v1-1][v2-1] = 1;
      }
    }
    else{
      if (ponderado){
        printf("\nDigite o peso da nova aresta: ");
        scanf("%d",&peso);
        matriz[v1-1][v2-1] = matriz[v2-1][v1-1] = peso;
      }
      else{
        matriz[v1-1][v2-1] = matriz[v2-1][v1-1] = 1;
      }
    }
  }
}

int RetornaAresta(int v1, int v2){
  if (v1 > numVertice || v2 > numVertice){
    return -1;
  }
  else{
    return matriz[v1-1][v2-1];
  }
}

int VerificarAdjacencia(int v1, int v2){
  if (v1 > numVertice || v2 > numVertice){
    return -1;
  }
  else{
    if (matriz[v1-1][v2-1] == 0){
      return 0;
    }
    else{
      return 1;
    }
  }
}

void ListarAdjacencias(int v1){
  int i;
  if (v1 > numVertice){
    printf("\nInsira uma vertice valida!\n");
  }
  else{
    if (orientado){
      for(i = 0; i < numVertice-1; i++){
        if (matriz[v1-1][i] > 0)
        printf("\nNo adjacente: %d\n",i+1);
      }
      for(i = 0; i < numVertice; i++){
        if (matriz[i][v1-1] > 0)
        printf("\nNo adjacente: %d\n",i+1);
      }
    }
    else{
      for(i = 0; i < numVertice; i++){
        if (matriz[v1-1][i] > 0)
        printf("\nNo adjacente: %d\n",i+1);
      }
    }
  }
}

int RetiraAresta(int v1, int v2){
  if (v1 > numVertice || v2 > numVertice){
    return -1;
  }
  else{
    int x = matriz[v1-1][v2-1];
    if (orientado){
      matriz[v1-1][v2-1] = 0;
    }
    else{
      matriz[v1-1][v2-1] = matriz[v2-1][v1-1] = 0;
    }
    return x;
  }
}

int RetiraMenor(){
  int i, j, x, y, menor = INT_MAX;
  for (i = 0; i < numVertice; i++){
    for (j = 0; j < numVertice; j++){
      if (matriz[i][j] < menor && matriz[i][j] != 0){
        menor = matriz[i][j];
        x = i;
        y = j;
      }
    }
  }
  matriz[x][y] = 0;
  return menor;
}

int RetiraMaior(){
  int i, j, x, y, maior = INT_MIN;
  for (i = 0; i < numVertice; i++){
    for (j = 0; j < numVertice; j++){
      if (matriz[i][j] > maior && matriz[i][j] != 0){
        maior = matriz[i][j];
        x = i;
        y = j;
      }
    }
  }
  matriz[x][y] = 0;
  return maior;
}

void LimparGrafo(){
  int i, j;
  for (i = 0; i < numVertice; i++){
    for (j = 0; j < numVertice; j++){
      matriz[i][j] = 0;
    }
  }
  numVertice = 0;
}

void Imprime(){
  int i, j;
  printf("V\t");
  for (i = 0; i < numVertice; i++){
    printf("%d\t",i+1);
  }
  for (i = 0; i < numVertice; i++){
    printf("\n%d\t",i+1);
    for (j = 0; j < numVertice; j++){
      printf("%d\t",matriz[i][j]);
    }
  }
  printf("\n");
}

void Desenha(){
  FILE *f;
  int i, j;
  f = fopen("grafo.txt", "w");
  if (orientado)
  fprintf(f, "digraph G {\n");
  else
  fprintf(f, "graph G {\n");
  fclose(f);
  f = fopen("grafo.txt", "a");

  if (orientado){
    for (i = 0; i < numVertice; i++){
      for (j = 0; j < numVertice; j++){
        if (ponderado){
          if (matriz[i][j] != 0)
          fprintf(f, "%d -> %d[label=\"%d\",weight=\"%d\"];\n",i+1,j+1,matriz[i][j],matriz[i][j]);
        }
        else{
          if (matriz[i][j] != 0)
          fprintf(f, "%d -> %d;\n",i+1,j+1);
        }
      }
    }
  }
  else{
    for (i = 0; i < numVertice; i++){
      for (j = 0; j < i+1; j++){
        if (ponderado){
          if (matriz[i][j] != 0)
          fprintf(f, "%d -- %d[label=\"%d\",weight=\"%d\"];\n",i+1,j+1,matriz[i][j],matriz[i][j]);
        }
        else{
          if (matriz[i][j] != 0)
          fprintf(f, "%d -- %d;\n",i+1,j+1);
        }
      }
    }
  }


  fprintf(f, "}");
  fclose(f);
  system("C:\\PROGRA~2\\Graphviz2.38\\bin\\dot.exe grafo.txt -Tpng > grafo.png");
  system("grafo.png");
}

int DFS(int i, int *visitados, int x){
  int j;
  printf("\n%d", i+1);
  visitados[i] = 1;
  if (i == x){
    return 1;
  }
  for (j = 0; j < numVertice; j++){
    if (visitados[j] && matriz[i][j] != 0)
    printf("Grafo com ciclo");
    if (!visitados[j] && matriz[i][j] != 0){
      return DFS(j, visitados, x);
    }
  }
}

int getNumVertices(){
  return numVertice;
}

int BFS(int v, int *estados, int x){
  int i;
  Fila f;
  iniFila(&f);
  insere_f(&f,v);
  estados[v] = esperando;
  while(!vaziaFila(&f)){
    v = retira_f(&f);
    printf("%d ",v+1);
    if (v == x){
      return 1;
    }
    estados[v] = visitado;
    for (i = 0; i < numVertice; i++){
      if (matriz[v][i] != 0 && estados[i] == inicial){
        insere_f(&f,i);
        estados[i] = esperando;
      }
    }
  }
  printf("\n");
  return 0;
}

void dijk (int inicio){
  int custo[MAX][MAX], distancia[MAX], ant[MAX], visitados[MAX], count, distMin, proxNo, i, j;

  for (i = 0; i < numVertice; i++){
    for (j = 0; j < numVertice; j++){
      if (matriz[i][j] == 0)
      custo[i][j] = INT_MAX;
      else
      custo[i][j] = matriz[i][j];
    }
  }

  for (i = 0; i < numVertice; i++){
    distancia[i] = custo[inicio][i];
    ant[i] = inicio;
    visitados[i] = 0;
  }

  distancia[inicio] = 0;
  visitados[inicio] = 1;

  for (count = 1; count < numVertice-1; count++){
    distMin = INT_MAX;

    for (i = 0; i < numVertice; i++){
      if ((distancia[i] < distMin) && (!visitados[i])){
        distMin = distancia[i];
        proxNo = i;
      }
    }

    visitados[proxNo] = 1;

    for (i = 0; i < numVertice; i++){
      if (!visitados[i])
      if (distMin + custo[proxNo][i] < distancia[i]){
        distancia[i] = distMin + custo[proxNo][i];
        ant[i] = proxNo;
      }
    }

  }

  for (i = 0; i < numVertice; i++){
    if (i != inicio){
      printf("\nDistancia do no %d = %d",i,distancia[i]);
      printf("\nCaminho = %d",i);

      j=i;
      do{
        j = ant[j];
        printf(" <- %d",j);
      }while (j != inicio);
      printf("\n");
    }
  }

}
