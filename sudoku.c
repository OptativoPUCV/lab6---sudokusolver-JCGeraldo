#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_validFilas(Node* n){
    int array[10] = {0};
    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(n->sudo[i][j]!=0){
                if(array[n->sudo[i][j]]!=0){
                    return 0;
                }
                else{
                    array[n->sudo[i][j]]=1;
                }
            }
        }
        memset(array, 0, sizeof(array));
    }
    return 1;
}

int is_validColumnas(Node* n){
    int array[10]={0};
    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(n->sudo[j][i]!=0){
                if(array[n->sudo[j][i]]!=0)
                    return 0;
                else
                    array[n->sudo[j][i]]=1;
            }
        }
        memset(array, 0, sizeof(array));
    }
    return 1;
}

int is_validSubmatrices(Node* n){
    int array[10]={0};
    int i,j;
    for(int fila =0; fila<9; fila+=3){
        for(int col =0; col<9; col+=3){
            memset(array, 0, sizeof(array));
            for(i=fila;i<fila+3;i++){
                for(j=col;j<col+3;j++){
                    if(n->sudo[i][j]!=0){
                        if(array[n->sudo[i][j]]!=0)
                            return 0;
                        else
                            array[n->sudo[i][j]]=1;
                    }
                }
            }
        }
    }
    return 1;
}

int is_valid(Node* n){
    return is_validFilas(n) && is_validColumnas(n) && is_validSubmatrices(n);
}


List* get_adj_nodes(Node* n){
    List* list=createList();
   //Buscar primer 0 en la matriz
   int i0=-1,j0=-1;
   for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
         if(n->sudo[i][j] == 0){
            i0 = i;
            j0 = j;
            break;
         }
      }
      if (i0 != -1 && j0 != -1) {
         break;
   }
   }
   //Recorrer los 9 posibles valores para el 0
   if(i0!=-1&&j0!=-1){
      for(int k = 1; k <= 9; k++){
         Node* adj = copy(n);
         adj->sudo[i0][j0] = k;
         if(is_valid(adj))
            pushBack(list, adj);
      }
   }
   return list;
}


int is_final(Node* n){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(n->sudo[i][j] == 0)
                return 0;
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
    Stack* S = createStack();
    push(S, initial);
    while(get_size(S)!=0){
        (*cont)++;
        Node* n = top(S);
        pop(S);
        if(is_final(n))
            return n;
        List* list = get_adj_nodes(n);
        Node* aux = first(list);
        while(aux){
            push(S, aux);
            aux = next(list);
        }
        free(list);
        free(n);
    }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/