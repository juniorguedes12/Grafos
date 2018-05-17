#include <stdio.h>
#include <stdlib.h>
#define ERROFILACHEIA -1
#define ERROFILAVAZIA -2
#define MAXSIZE 50

typedef struct{
  int item[MAXSIZE];
  int ini;
  int fim;
  int cont;
}Fila;

void iniFila(Fila *f);
int vaziaFila(Fila *f);
int cheiaFila(Fila *f);
int insere_f(Fila *f, int x);
int retira_f(Fila *f);
int exibe(Fila *f);

void iniFila(Fila *f){
  f->ini = 0;
  f->fim = 0;
  f->cont = 0;
}

int vaziaFila(Fila *f){
  if (f->cont == 0){
    return(1);
  }
  else {
    return(0);
  }
}

int cheiaFila(Fila *f){
  if (f->cont == MAXSIZE){
    return(1);
  }
  else {
    return(0);
  }
}

int insere_f(Fila *f, int x){
  if (cheiaFila(f)){
    return(ERROFILACHEIA);
  }
  else{
    f->item[f->fim] = x;
    f->cont++;
    if (f->fim == MAXSIZE -1){
      f->fim = 0;
    }
    else{
      f->fim++;
    }
    return(f->fim);
  }
}

int retira_f(Fila *f){
  int x;
  if (vaziaFila(f)){
    return(ERROFILAVAZIA);
  }
  else{
    x = f->item[f->ini];
    if(f->ini != MAXSIZE-1){
      f->ini++;
    }
    else{
      f->ini =0;
    }
    f->cont--;
    return x;
  }
}

int exibe(Fila *f){
  int i, j=f->ini;;
  if(vaziaFila(f)){
    return(ERROFILAVAZIA);
  }
  else{
    printf("\n");
    for(i=0;i<f->cont;i++){
      printf("%d\n",f->item[j]);
      if(j==MAXSIZE-1){
        j=0;
      }
      else{
        j++;
      }
    }
    printf("\n");
  }
}
