#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "grafo.h"

int main() {
  srand(time(NULL));
  int c, x, y, z, menu = 1;
  int visitados[30];
  int estados[30];
  for (;;){
    printf("\n");
    if(menu){
      printf("1. Gerar grafo vazio\n");
      printf("2. Gerar grafo aleatorio\n");
      do {
        printf("\nEntre com sua escolha:\n ");
        scanf("%d",&c);
      } while(c<1 || c>2);
    }
    else{
      printf("1. Inserir nova aresta\n");
      printf("2. Remover uma aresta\n");
      printf("3. Inserir novo no\n");
      printf("4. Retirar um no\n");
      printf("5. Verificar adjacencia de par de nos\n");
      printf("6. Listar todas as adjacencias de um no\n");
      printf("7. Retirar menor aresta\n");
      printf("8. Retirar maior aresta\n");
      printf("9. Limpar grafo\n");
      printf("10. Imprimir\n");
      printf("11. Desenhar\n");
      printf("12. DFS\n");
      printf("13. BFS\n");
      printf("14. Sair\n");
      do {
        printf("\nEntre com sua escolha:\n ");
        scanf("%d",&c);
      } while(c<1 || c>14);
      c += 2;
    }
    switch (c) {
      case 1:
      printf("\nDigite o tamanho do grafo: ");
      scanf("%d",&x);
      printf("\nDeseja que o grafo seja orientado? SIM(1) NAO(0): ");
      scanf("%d",&y);
      printf("\nDeseja que o grafo seja ponderado? SIM(1) NAO(0): ");
      scanf("%d",&z);
      GerarGrafoVazio(x,y,z);
      menu = 0;
      break;
      case 2:
      printf("\nDigite o tamanho do grafo: ");
      scanf("%d",&x);
      printf("\nDigite o limite de peso (1 para nao ponderado): ");
      scanf("%d",&y);
      printf("\nDeseja que o grafo seja orientado? SIM(1) NAO(0): ");
      scanf("%d",&z);
      GerarGrafoAleatorio(x, y, z);
      menu = 0;
      break;
      case 3:
      printf("\nDigite o vertice 1: ");
      scanf("%d",&x);
      printf("\nDigite o vertice 2: ");
      scanf("%d",&y);
      InserirNovaAresta(x, y);
      break;
      case 4:
      printf("\nDigite o vertice 1: ");
      scanf("%d",&x);
      printf("\nDigite o vertice 2: ");
      scanf("%d",&y);
      z = RetiraAresta(x,y);
      if (z != -1)
      printf("\nO peso da aresta removida era: %d\n",z);
      else
      printf("\nInsira vertices validas!\n");
      system("pause");
      break;
      case 5:
      InserirNovoNo();
      printf("\nNo inserido\n");
      system("pause");
      break;
      case 6:
      printf("\nDigite o no: ");
      scanf("%d",&x);
      RemoveNo(x);
      system("pause");
      break;
      case 7:
      printf("\nDigite o vertice 1: ");
      scanf("%d",&x);
      printf("\nDigite o vertice 2: ");
      scanf("%d",&y);
      z = VerificarAdjacencia(x, y);
      if (z == -3)
      printf("\nInsira vertices validas!\n");
      else if (z == -1 || z == -2)
      printf("\nAs vertices nao possuem adjacencia!\n");
      else
      printf("\nAs vertices possuem adjacencia!\n");
      system("pause");
      break;
      case 8:
      printf("\nDigite o vertice: ");
      scanf("%d",&x);
      ListarAdjacencias(x);
      system("pause");
      break;
      case 9:
      z = RetiraMenor();
      printf("\nMenor aresta removida: %d\n",z);
      system("pause");
      break;
      case 10:
      z = RetiraMaior();
      printf("\nMaior aresta removida: %d\n",z);
      system("pause");
      break;
      case 11:
      LimparGrafo();
      menu = 1;
      break;
      case 12:
      Imprime();
      system("pause");
      break;
      case 13:
      Desenha();
      break;
      case 14:
      printf("\nDigite o valor que deseja encontrar: ");
      scanf("%d",&x);
      y = getNumVertices();
      for (z = 0; z < y; z++){
        visitados[z] = 0;
      }
      for (z = 0; z < y; z++){
        if (visitados[z] == 0){
          if (DFS(z, visitados, x-1) == 1){
            printf("\nValor encontrado\n");
            system("pause");
            break;
          }
        }
      }
      printf("\n");
      break;
      case 15:
      printf("\nDigite o valor que deseja encontrar: ");
      scanf("%d",&x);
      y = getNumVertices();
      for (z = 0; z < y; z++){
        estados[z] = 1;
      }
      for (z = 0; z < y; z++){
        if (estados[z] == 1){
          if (BFS(z, estados, x-1) == 1){
            printf("\nValor encontrado\n");
            system("pause");
            break;
          }
        }
      }
      break;
      case 16:
      return 0;
      break;
    }
  }
}
