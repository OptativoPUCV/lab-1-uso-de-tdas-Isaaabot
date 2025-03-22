#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "arraylist.h"
#include "stack.h"

//#include "exercises.h"

//Funciones auxiliares que puedes utilizar para debuggear tus ejercicios
//NO MODIFICAR
void imprime_lista(List *L) {
   int *dato;
   dato = (int*)first(L);
   printf("[");
   while(dato != NULL) {
      printf("%d ", *dato);
      dato = (int*)next(L);
   }
   printf("]\n");

}

//Ojo que la pila se vacía al imprimir y se imprime en orden inverso
//NO MODIFICAR
void imprime_y_vacia_pila(Stack *P) {
   void *dato;
   printf("[");
   while((dato = pop(P)) != NULL) {
      printf("%d ", *(int*)dato);
   }
   printf("]\n");
}

/* 
Ejercicio 1.
Crea una Lista y agrega punteros a elementos del 1 al 10.
Recuerda que la lista almacena punteros, por lo que
debes reservar memoria para cada elemento que agregues.
Al finalizar retorna la lista creada.
*/
List* crea_lista() 
{
   List* L = create_list() ;                     // Se crea la lista "L"
   
   for (int k = 0 ; k < 10 ; k++)
   {
      int *elemento = malloc(sizeof(int)) ;      // Se reserva memoria para cada puntero

      if (elemento == NULL)                      // Flag por si hay un error en la asignación de memoria
         exit(EXIT_FAILURE) ;                    // Significa que algo salió mal :(

      *elemento = k + 1 ;                        // Asigna valores del 1-10, "*" para agregar el valor en la direccion de memoria
      pushBack(L, elemento) ;             
   }
   return L ;                                    // Se retorna la lista "L"
}

/*
Ejercicio 2.
Crea una función que reciba una lista de enteros (int*) y 
retorne la suma de sus elementos.
*/
int sumaLista(List *L) 
{
   int suma = 0 ;                                // Se crea variable "suma" para poder sumar todos los elementos
   int *elemento = first(L) ;

   while (elemento != NULL)
   {
      suma += *elemento ;                        // Se va sumando cada elemento a la variable "suma"
      elemento = next(L) ;
   }
   return suma ;                                 // Se retorna la suma :)
}

/*
Ejercicio 3.
Crea una función que reciba una lista de punteros a int (int*) y
un entero elem. La función debe eliminar todos los elementos 
de la lista que sean iguales a elem.
Asume que popCurrent luego de eliminar un elemento se
posiciona en el elemento anterior.
*/
void eliminaElementos(List* L, int elem)
{
   /*
   int *elemento = first(L) ;

   while (elemento != NULL)
   {
      if (elemento == elem)  
         popCurrent() ;
      
      elemento = next(L) ;
   }
   */
   /*
   for (int k = 0; k < 10; k++)
   {
      int **L ;
      if (*(L[k]) == elem)
         popCurrent(*L[k]) ;
   }
   */
}

/*
Ejercicio 4.
La función copia los punteros de la pila P1 en la pila P2.
El orden de ambas pilas se debe mantener.
Puedes usar una pila auxiliar.
*/

void copia_pila(Stack* P1, Stack* P2) 
{
   //Stack* aux = create_stack() ;
   int *elemento = first(P1) ;
   int talla = get_size(P1) ;

   while (talla != NULL)
   {
      pushBack(P2, elemento) ;
      elemento = next(P1) ;

      talla-- ;
   }
}

/*
Ejercicio 5.
La función verifica si la cadena de entrada tiene sus 
paraéntesis balanceados. Retorna 1 si están balanceados,
0 en caso contrario.
*/

int parentesisBalanceados(char *cadena) 
{


   return 0 ;
}

