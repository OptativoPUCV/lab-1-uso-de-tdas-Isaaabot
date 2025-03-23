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
   List* L = create_list() ;                                   // Se crea la lista "L"
   
   for (int k = 0 ; k < 10 ; k++)
   {
      int *elemento = malloc(sizeof(int)) ;                    // Se reserva memoria para cada puntero

      if (elemento == NULL)                                    // Flag por si hay un error en la asignación de memoria
         exit(EXIT_FAILURE) ;                                  // Significa que algo salió mal :(

      *elemento = k + 1 ;                                      // Asigna valores del 1-10, "*" para agregar el valor en la direccion de memoria
      pushBack(L, elemento) ;                                  // Utilizo "pushBack" para ir traspasando los elementos a "L"
   }
   return L ;                                                  // Se retorna la lista "L"
}

/*
Ejercicio 2.
Crea una función que reciba una lista de enteros (int*) y 
retorne la suma de sus elementos.
*/
int sumaLista(List *L) 
{
   int suma = 0 ;                                              // Se crea variable "suma" para poder sumar todos los elementos
   int *elemento = first(L) ;                                  // Se asigna primer valor de la lista a "elemento"

   while (elemento != NULL)
   {
      suma += *elemento ;                                      // Se va sumando cada elemento a la variable "suma"
      elemento = next(L) ;                                     // Pasa al siguiente elemento
   }
   return suma ;                                               // Se retorna la suma :)
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
   int *elemento = first(L) ;                                  // Se asigna primer valor de la lista a "elemento"

   while (elemento != NULL)
   {
      if (*elemento == elem)                                   // Se compara si el valor de elemento es igual a "elem"  
         popCurrent(L) ;                                       // Se elimina en caso de que se cumpla la condición 
      
      elemento = next(L) ;                                     // Pasa al siguiente elemento
   }
}

/*
Ejercicio 4.
La función copia los punteros de la pila P1 en la pila P2.
El orden de ambas pilas se debe mantener.
Puedes usar una pila auxiliar.
*/
void copia_pila(Stack* P1, Stack* P2) 
{
   int *elemento = first(P1) ;                                 // Le doy a elemento la primera posicion de "P1"
   int talla = get_size(P1) ;                                  // Obtengo la talla de la pila

   while (talla > -1)                    
   {                                      
      pushBack(P2, elemento) ;                                 // Utilizo "pushBack" para ir traspasando los elementos a "P2"
      elemento = next(P1) ;                                    // Pasa al siguiente elemento de P1

      talla-- ;                                                // La talla disminuye en 1
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
   Stack *pila_apertura = create_stack() ;                     // Se crea "pila_apertura"
   Stack *pila_cierre = create_stack() ;                       // Se crea "pila_cierre"
   int talla = 0 ;

   for (int k = 0; cadena[k] ; k++)
   {
      char *caracter = (char *) malloc(sizeof(char)) ;         // Reservo memoria con malloc para el caracter
      
      if (caracter == NULL)                                    // Flag por si hay un error en la asignación de memoria   
         exit(EXIT_FAILURE) ;                                  // Significa que algo salió mal :(
      
      *caracter = cadena[k] ;                                  // Le doy el valor de "cadena[k]" a "caracter"
      push(pila_apertura, caracter) ;                          // Utilizo "push" para ir traspasando los elementos a "pila_apertura"
      talla++ ;                                                // Aumento en 1 la talla
   }

   if (talla % 2 != 0)                                         // Si la talla es impar quiere decir que no está balanceado
   {  
      free(pila_apertura) ;                                    // Libero la memoria de la pila_apertura
      return 0 ;                                               // Retorno no balanceado
   }

   for (int k = 0 ; k < (talla / 2) ; k++)                     // Quiero utilizar solo la mitad de la cadena
   {
      char *elemento = top(pila_apertura) ;                    // Con "top" se le asigna el valor a "elemento"
      push(pila_cierre, elemento) ;                            // Utilizo "push" para ir traspasando los elementos a "pila_cierre"
      pop(pila_apertura) ;                                     // Con "pop" borro aquel elemento de pila_apertura
   } 

   for (int k = 0 ; k < (talla / 2) ; k++)                     // Quiero utilizar solo la mitad de la cadena
   {
      char *apertura_a = top(pila_apertura) ;                  // Con "top" se le asigna el valor a "apertura_a"
      char *apertura_c = top(pila_cierre) ;                    // Con "top" se le asigna el valor a "apertura_c"
      pop(pila_apertura) ;                                     // Con "pop" borro aquel elemento de pila_apertura
      pop(pila_cierre) ;                                       // Con "pop" borro aquel elemento de pila_cierre

      if (((*apertura_a) == '(' && (*apertura_c) != ')') || 
         ((*apertura_a) == '[' && (*apertura_c) != ']') || 
         ((*apertura_a) == '{' && (*apertura_c) != '}'))       // Condición por si no son balanceados
      { 
         free(pila_apertura) ;                                 // Libero la memoria de la pila_apertura
         free(pila_cierre) ;                                   // Libero la memoria de la pila_cierre
         return 0 ;                                            // Retorno no balanceado
      }
   }
   free(pila_apertura) ;                                       // Libero la memoria de la pila_apertura
   free(pila_cierre) ;                                         // Libero la memoria de la pila_cierre
   return 1 ;                                                  // Retorno balanceado
}
// Disculpen, se me enredaban las ideas y lo comenté casi todo para no perderme, espero que se entienda :(