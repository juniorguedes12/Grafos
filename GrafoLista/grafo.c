#include "grafo.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 30
#define LISTAVAZIA -1
#define NAOENCONTRADO -2
#define ERRO -3

#define inicial 1
#define esperando 2

typedef struct NoTag{
  int vizinho;
  int peso;
  struct NoTag *link;
}no;

no *grafo[MAX];
int numVertice = 0;
int orientado;
int ponderado;

int visitado[MAX];

void insereLista(int node, int vizinho, int peso){
  no *N, *P;
  N = (no *) malloc (sizeof(no));
  N->peso = peso;
  N->vizinho = vizinho;
  N->link=NULL;
  if (grafo[node] ==  NULL){
    grafo[node] = N;
  }
  else{
    P = grafo[node];
    while(P->link != NULL){
      P=P->link;
    }
    P->link = N;
  }
}

int removeLista(int no1, int no2){
  no *P, *ANT;
  int y;
  if (grafo[no1] != NULL){
    P = grafo[no1];
    while ((P != NULL) && (no2!=P->vizinho)){
      ANT = P;
      P = P->link;
    }
    if (P == NULL){
      return NAOENCONTRADO;
    }
    else{
      if (P == grafo[no1]){
        grafo[no1] = grafo[no1]->link;
        y = P->peso;
        free(P);
      }
      else{
        ANT->link = P->link;
        y = P->peso;
        free(P);
      }
      return y;
    }
  }
  else{
    return LISTAVAZIA;
  }
}

int percorreLista(int no1, int no2){
  no *P;
  int y;
  if (grafo[no1] != NULL){
    P = grafo[no1];
    while ((P != NULL) && (P->vizinho!=no2)){
      P = P->link;
    }
    if (P == NULL){
      return NAOENCONTRADO;
    }
    else{
      y=P->peso;
      return y;
    }
  }
  else{
    return LISTAVAZIA;
  }
}

void iniLista(int n){
  grafo[n] = NULL;
}

void imprimeLista(int n){
  no *P;
  P = grafo[n];
  while(P!=NULL){
    printf(" |%d, %d| ->",P->vizinho, P->peso);
    P=P->link;
  }
}

void GerarGrafoVazio(int n, int o, int p){
  int i;
  for (i = 0; i < n; i++){
    iniLista(i);
  }
  numVertice = n;
  orientado = o;
  ponderado = p;
}

void GerarGrafoAleatorio(int n, int pMax, int o){
  int i, j;
  int aux1, aux2;
  numVertice = n;
  orientado = o;
  if (pMax == 1)
  ponderado = 0;
  else
  ponderado = 1;
  for (i = 0; i < n; i++){
    iniLista(i);
  }
  if (!orientado){
    for (i = 0; i < n; i++){
      aux1 = rand()%n;
      aux2 = (rand()%pMax)+1;
      insereLista(i, aux1+1, aux2);
      if (i != aux1){
        insereLista(aux1, i+1, aux2);
      }
    }
  }
  else{
    for (i = 0; i < n; i++){
      aux1 = rand()%n;
      aux2 = (rand()%pMax)+1;
      insereLista(i, aux1+1, aux2);
    }
  }
}

void InserirNovoNo(){
  iniLista(numVertice);
  numVertice += 1;
}

void RemoveNo(int node){
  int i;
  no *aux, *aux2;
  if (node <= numVertice){
    for (i = 0; i < numVertice; i++){
      removeLista(i,node);
      aux = grafo[i];
      while(aux != NULL) {
        if (aux->vizinho > node){
          aux->vizinho -= 1;
        }
        aux = aux->link;
      }
    }
    aux = grafo[node-1];
    while(aux != NULL) {
      aux2 = aux;
      aux = aux->link;
      free(aux2);
    }
    free(grafo[node-1]);
    if (node != numVertice){
      for(i = node-1; i < numVertice; i++){
        grafo[i] = grafo[i+1];
      }
    }
    numVertice -= 1;
  }
  else{
    printf("\nInserir vertice valida!\n");
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
        insereLista(v1-1,v2,peso);
      }
      else{
        insereLista(v1-1,v2,1);
      }
    }
    else{
      if (ponderado){
        printf("\nDigite o peso da nova aresta: ");
        scanf("%d",&peso);
        insereLista(v1-1,v2,peso);
        if (v2 != v1){
          insereLista(v2-1,v1,peso);
        }
      }
      else{
        insereLista(v1-1,v2,1);
        if (v2 != v1){
          insereLista(v2-1,v1,1);
        }
      }
    }
  }
}

int RetornaAresta(int v1, int v2){
  if (v1 > numVertice || v2 > numVertice){
    return ERRO;
  }
  else{
    return percorreLista(v1-1,v2);
  }
}

int VerificarAdjacencia(int v1, int v2){
  if (v1 > numVertice || v2 > numVertice){
    return ERRO;
  }
  else{
    return percorreLista(v1-1, v2);
  }
}

void ListarAdjacencias(int v1){
  int i;
  no *aux;
  if (v1 > numVertice){
    printf("\nInsira uma vertice valida!\n");
  }
  else{
    printf("\n");
    printf("Vertice: %d ->",v1);
    imprimeLista(v1-1);
    printf(" NULL\n");
  }
}

int RetiraAresta(int v1, int v2){
  if (v1 > numVertice || v2 > numVertice){
    return ERRO;
  }
  else{
    int x;
    if (orientado){
      x = removeLista(v1-1,v2);
    }
    else{
      x = removeLista(v1-1,v2);
      if (v1 != v2){
        removeLista(v2-1,v1);
      }
    }
    return x;
  }
}

int RetiraMenor(){
  int i, menor = INT_MAX;
  no *aux;
  int v1, v2;
  for (i = 0; i < numVertice; i++){
    if (grafo[i] == NULL){
      continue;
    }
    else{
      aux = grafo[i];
      while(aux != NULL) {
        if (aux->peso < menor){
          v1 = i;
          v2 = aux->vizinho;
          menor = aux->peso;
        }
        aux = aux->link;
      }
    }
  }
  if (orientado){
    removeLista(v1,v2);
  }
  else{
    removeLista(v1-1,v2);
    if (v1 != v2){
      removeLista(v2-1,v1+1);
    }
  }
  return menor;
}

int RetiraMaior(){
  int i, maior = INT_MIN;
  no *aux;
  int v1, v2;
  for (i = 0; i < numVertice; i++){
    if (grafo[i] == NULL){
      continue;
    }
    else{
      aux = grafo[i];
      while(aux != NULL) {
        if (aux->peso > maior){
          v1 = i;
          v2 = aux->vizinho;
          maior = aux->peso;
        }
        aux = aux->link;
      }
    }
  }
  if (orientado){
    removeLista(v1,v2);
  }
  else{
    removeLista(v1-1,v2);
    if (v1 != v2){
      removeLista(v2-1,v1+1);
    }
  }
  return maior;
}

void LimparGrafo(){
  int i;
  no *aux1, *aux2;
  for (i = 0; i < numVertice; i++){
    if (grafo[i] == NULL){
      continue;
    }
    else{
      aux1 = grafo[i];
      while(aux1 != NULL) {
        aux2 = aux1;
        removeLista(i,aux2->vizinho);
        aux1 = aux1->link;
      }
    }
    free(grafo[i]);
  }
  numVertice = 0;
}

void Imprime(){
  int i;
  printf("\n|Aresta, Peso|\n");
  for (i = 0; i < numVertice; i++){
    printf("Vertice: %d ->",i+1);
    imprimeLista(i);
    printf(" NULL\n");
  }
  printf("\n");
}

void Desenha(){
  FILE *f;
  int i;
  no *aux;
  f = fopen("grafo.txt", "w");
  if (orientado)
  fprintf(f, "digraph G {\n");
  else
  fprintf(f, "graph G {\n");
  fclose(f);
  f = fopen("grafo.txt", "a");

  for (i = 0; i < numVertice; i++){
    aux = grafo[i];
    while (aux != NULL){
      if (ponderado){
        if (orientado)
        fprintf(f, "%d -> %d[label=\"%d\",weight=\"%d\"];\n",i+1, aux->vizinho, aux->peso, aux->peso);
        else
        fprintf(f, "%d -- %d[label=\"%d\",weight=\"%d\"];\n",i+1,aux->vizinho,aux->peso,aux->peso);
      }
      else{
        if (orientado)
        fprintf(f, "%d -> %d;\n",i+1,aux->vizinho);
        else
        fprintf(f, "%d -- %d;\n",i+1,aux->vizinho);
      }
      aux = aux->link;
    }
  }

  fprintf(f, "}");
  fclose(f);
  system("C:\\PROGRA~2\\Graphviz2.38\\bin\\dot.exe grafo.txt -Tpng > grafo.png");
  system("grafo.png");
}

int DFS(int i, int *visitados, int x){
  no *p;
  printf("\n%d", i+1);
  visitados[i] = 1;

  if (i == x){
    return 1;
  }

  for (p = grafo[i]; p != NULL ; p=p->link){
    i = p->vizinho;
    if (visitado[i-1])
      printf("Grafo tem ciclo");
    if (!visitados[i-1]){
      return DFS(i-1, visitados, x);
    }
  }
}

int getNumVertices(){
  return numVertice;
}

int BFS(int v, int *estados, int x){
  int i, aux;
  Fila f;
  no *p;
  iniFila(&f);

  insere_f(&f,v);

  estados[v] = esperando;
  while(!vaziaFila(&f)){
    v = retira_f(&f);
    printf("%d ",v+1);

    if (v == x){
      return 1;
    }

    for (p = grafo[v]; p != NULL; p=p->link){
      aux = p->vizinho;
      if (estados[aux] == inicial){
        insere_f(&f,aux);
        estados[aux] = esperando;
      }
    }

    printf("\n");
    return 0;
  }
}
