/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#ifndef CENTER_LIST_H
#define CENTER_LIST_H

#include "types.h"
#include "party_list.h"
#include <stdbool.h>

#define MAX 10 // Representa el número máximo de centros en la lista
#define NULLC -1

// Se va usar una implementación estática de manera ordenada


typedef int tPosC;
typedef struct {
    tCenterName centerName;
    tNumVotes totalVoters;
    tNumVotes validVotes;
    tNumVotes nullVotes;
    tList partyList;
}tItemC;

typedef struct {
    tItemC data[MAX];
    tPosC lastPos;
}tListC;

void createEmptyListC(tListC* L);
/*
 * Objetivo: Crear una lista vacía
 * Entrada: Una lista tipo tList
 * Salida: La lista inicializada
 * Postcondición: La lista inicializada no presenta elementos
*/
bool insertItemC(tItemC d, tListC* L);
/*
 * Objetivo: Insertar un elemento de forma ordenada en la lista en función del campo centerName
 * Entrada:
 *    tItemC d: Contenido del elemento principal a insertar
 *    tListC *L: Lista donde escribimos el elemento
 * Salida: La lista tListC *L tras haber insertado el elemento.
 * A su vez se devuelve un booleano que verifica si se ha insertado correctamente el elemento
 * Precondición: Que la lista haya sido inicializada
 * Postcondición: La posición de los elementos de la lista puede haberse modificado
*/
bool copyListC(tListC L1, tListC* L2);
/*
 * Objetivo: Copiar el contenido de una lista en otra
 * Entrada:
 *    tList L1: Lista que vamos a copiar
 *    tList L2*: Lista donde se hará la copia
 * Salida:
 *    tList L2*: Copia de la lista L1
 *    Booleano que devuelva si se ha podido copiar la lista
 * Precondición: Ambas listas han de ser inicializadas. La lista L2* puede o no estar vacía.
*/
void updateListC(tList P, tPosC p, tListC* L);
void updateValidVotesC(tNumVotes a, tPosC p, tListC* L);
/*
 * Objetivo: Modifica el número de votos válidos del elmento situado en la posición dada
 * Entradas:
 *    tNumVotes a: Valor de los votos que se quieran añadir a los correspondientes del partido
 *    tPosC p: Posición deseada donde se encuentra el elemento a ser modificado
 *    tListC *L: Lista pasada para ser modificada
 * Salida: La lista tListC *L tras haber modificado los votos del elemento correspondiente
 * Precondición: La lista ha de estar inicializada. La posición tPosC ha de ser válida en la lista
 * Postcondición: El orden de los elementos no se verá afectado
*/
void updateNullVotes(tNumVotes a, tPosC p, tListC* L);
void deleteAtPositionC(tPosC p, tListC* L);
/*
 * Objetivo: Elimina de la lista un elemento dado una posición
 * Entradas:
 *    tPosL p: Posición del elemento a ser eliminado
 *    tList *L: Lista a ser modificada
 * Salida: La lista tras haber sido modificada
 * Precondición: tPosL p es una posición válida de la lista
 * Postcondición: Las posiciones de los elementos de la lista pueden haber variado
*/
void deleteListC(tListC* L);
/*
 * Objetivo: Elimina todos los elementos de la lista
 * Entrada: tList *L a ser borrada
 * Salida: La lista vacía
 * Precondición: Lista inicializada
*/
tPosC findItemC(tCenterName name, tListC L);
/*
 * Objetivo: Devuelve la posición del primer elemento de la lista cuyo nombre de partido sea igual al indicado
 * Entrada:
 *    tPartyName name: Nombre del partido a ser buscado
 *    tList L: Lista donde se buscará el partido
 * Salida: Una posición, si se diese encontrado el partido se devuelve la posición en la lista.
 * En caso contrario se devuelve LNULL.
 * Precondición: La lista tList L ha de ser inicializada
*/
bool isEmptyListC(tListC L);
/*
 * Objetivo: Determinar si la lista está vacía
 * Entrada: Una lista L de tipo tList
 * Salida: Booleano determinando el objetivo
 * Precondición: La lista ha de estar previamente inicializada
*/
tItemC getItemC(tPosC p, tListC L);
/*
 * Objetivo: Devuelve el contenido de un elemento de la lista
 * Entradas:
 *    tPosL p: Posición del elemento a ser encontrado
 *    tList L: Lista donde encontrar el elemento
 * Salida: Se devolverá un tItemL procedente de la lista asociado a la posición aaportada
 * Precondición: La posición del elemento a ser buscado siempre será una válida en la lista,
 * y la lista ha de estar inicializada
*/
tPosC firstC(tListC L);
/*
 * Objetivo: Devolver la primera posición de la lista
 * Entrada: Una lista L de tipo tList
 * Salida: La posición de tipo tPosL del primer elemento de la lista
 * Precondición: La lista no puede estar vacía y debe haber sido inicializada previamente
*/
tPosC lastC(tListC L);
/*
 * Objetivo: Devuelve la posición del último elemento de la lista
 * Entrada: Una lista L de tipo tList
 * Salida: La posición tPosL del último elemento de la lista
 * Precondición: La lista ha de estar inicializada y no puede estar vacía
*/
tPosC previousC(tPosC p, tListC L);
/*
 * Objetivo: Devuelve la posición del elemento correspondiente a el de la posición dada
 * Entradas:
 *    tPosL p: Posición del elemento actual
 *    tList L: Lista en donde encontrar el elemento previo
 * Salida: La posición del elemento previo o nulo si tPosL p es el primer elemento de la lista
 * Precondición: tPosL p es una posición válida de la lista y la lista está inicializada
*/
tPosC nextC(tPosC p, tListC L);
/*
 * Objetivo: Devuelve la posición del elemento siguiente a el de la posición dada
 * Entradas:
 *    tPosL p: Posición del elemento actual
 *    tList L: Lista en donde encontrar el elemento siguiente
 * Salida: La posición del elemento siguiente o nulo si tPosL p es el último elemento de la lista
 * Precondición: tPosL p es una posición válida de la lista, y la lista ha de estar inicializada
*/

#endif
