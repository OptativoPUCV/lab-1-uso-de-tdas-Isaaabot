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
   int *elemento = first(L) ;

   while (elemento != NULL)
   {
      if (*elemento == elem)  
         popCurrent(L) ;
      
      elemento = next(L) ;
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
   int *elemento = first(P1) ;
   int talla = get_size(P1) ;

   while (talla != -1)                    
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

**Paréntesis balanceados** se refiere a una secuencia en la que cada tipo 
de paréntesis abierto (ya sean paréntesis redondos `()`, corchetes `[]`, o 
llaves `{}`) se cierra en el orden inverso al que se abrió. Esto asegura que 
todas las aperturas tienen su correspondiente cierre en el orden correcto. 
  
Por ejemplo, la secuencia `([{}])` está balanceada porque cada paréntesis 
que se abre se cierra adecuadamente en reversa a su orden de apertura. 
  En contraste, `([)]` es un ejemplo de paréntesis desbalanceados, ya que 
aunque todos los tipos de paréntesis se abren y cierran, el orden no es el 
correcto: el corchete se cierra antes de cerrar el paréntesis que lo 
contiene inicialmente.
*/

int parentesisBalanceados(char *cadena)
{
   Stack *pila_apertura = create_stack() ;
   Stack *pila_cierre = create_stack() ;
   char caracter ;
   int talla = 0 ;

   for (int k = 0; cadena[k] ; k++)
   {
      caracter = cadena[k] ;
      push(pila_apertura, &caracter) ;
      talla++ ;
   }

   if (talla % 2 != 0)
      return 0 ;

   for (int k = 0 ; k < (talla / 2) ; k++)
   {
      char *elemento = top(pila_apertura) ;
      push(pila_cierre, elemento) ;
      pop(pila_apertura) ;
   } 

   for (int k = 0 ; k < (talla / 2) ; k++)
   {
      char *apertura_a = top(pila_apertura) ;
      char *apertura_c = top(pila_cierre) ;
      pop(pila_apertura) ;
      pop(pila_cierre) ;

      if (((*apertura_a) == '(' && (*apertura_c) != ')') || 
         ((*apertura_a) == '[' && (*apertura_c) != ']') || 
         ((*apertura_a) == '{' && (*apertura_c) != '}'))
      {
         return 0 ;
      }
   }
   return 1 ;
}

/*
int parentesisBalanceados(char *cadena)
{
   Stack *pila_apertura = create_stack() ;
   Stack *pila_cierre = create_stack() ;
   char caracter ;
   int talla = 0 ;

   for (int k = 0; cadena[k] ; k++)
   {
      caracter = cadena[k] ;

      if (caracter == '(' || caracter == '[' || caracter == '{')
         push(pila_apertura, &caracter) ;
      else if (caracter == ')' || caracter == ']' || caracter == '}')   
      {
         if (pila_apertura == NULL)
            return 0 ;

         push(pila_cierre, &caracter) ;

         char *apertura_a = top(pila_apertura) ;
         char *apertura_c = top(pila_cierre) ;
         apertura_a = pop(pila_apertura) ;
         apertura_c = pop(pila_cierre) ;

         if (((*apertura_a) == '(' && (*apertura_c) != ')') || ((*apertura_a) == '[' && (*apertura_c) != ']') || ((*apertura_a) == '{' && (*apertura_c) != '}'))
         //if ((apertura_a == '(' && apertura_c != ')') || (apertura_a == '[' && apertura_c != ']') || (apertura_a == '{' && apertura_c != '}'))
            return 0 ;
      }
      talla++ ;
   }
   if (talla % 2 != 0)
      return 0 ;
   
   return 1 ;
}
*/

/*
int parentesisBalanceados(char *cadena)
{
   Stack *pila_apertura = create_stack() ;
   Stack *pila_cierre = create_stack() ;
   char caracter ;
   int talla = 0 ;

   for (int k = 0; cadena[k] ; k++)
   {
      caracter = cadena[k] ;
      pushBack(pila_cierre, &caracter) ;
      talla++ ;
   }

   if (talla % 2 != 0)
      return 0 ;

   char *elemento = first(pila_cierre) ;

   for (int k = 0 ; k < (talla / 2) ; k++)
   {
      pushFront(pila_apertura, elemento) ;
      elemento = next(pila_cierre) ;
   } 

   for (int k = 0 ; k < (talla / 2) ; k++)
   {
      char *apertura = pop(pila_apertura) ;
      char *cierre = pop(pila_cierre) ;

      if (((*apertura) == '(' && (*cierre) != ')') || ((*apertura) == '[' && (*cierre) != ']') || ((*apertura) == '{' && (*cierre) != '}'))
         return 0 ;
   }
   return 1 ;
}
*/

/*
int parentesisBalanceados(char *cadena) 
{
   Stack *pila_apertura = create_stack() ;
   char caracter ;
   //int talla = 0 ;

   for (int k = 0; cadena[k] ; k++)
   {
      caracter = cadena[k] ;

      if (caracter == '(' || caracter == '[' || caracter == '{')
         push(pila_apertura, &caracter) ;   
      else
         if (pila_apertura == NULL)
            return 0 ;  
      
      char *apertura = pop(pila_apertura) ;

      if (((*apertura) == '(' && caracter != ')') || ((*apertura) == '[' && caracter != ']') || ((*apertura) == '{' && caracter != '}'))
      //if ((apertura == '(' && caracter != ')') || (apertura == '[' && caracter != ']') || (apertura == '{' && caracter != '}'))
         return 0 ;
   }
   return 1 ;
}
*/