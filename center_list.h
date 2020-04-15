/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Picado Liñares, David LOGIN 1: david.picado
 * AUTHOR 2: Otero Agraso, Samuel LOGIN 2: s.agraso
 * GROUP: 1.5
 * DATE: ** / ** / **
 */

#ifndef CENTER_LIST_H
#define CENTER_LIST_H

#include "types.h"
#include "party_list.h"
#include <stdbool.h>

#define MAX 10 // Representa el número máximo de centros en la lista
#define NULLC -1


// Declaración de los tipos usados

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

// Declaración de los prototipos de las funciones, así como su especificación

void createEmptyListC(tListC* L);
/*
 * Objetivo: Crear una lista vacía
 * Entrada: Una lista tipo tListC
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
 *    tListC L1: Lista que vamos a copiar
 *    tListC L2*: Lista donde se hará la copia
 * Salida:
 *    tListC L2*: Copia de la lista L1
 *    Booleano que devuelva si se ha podido copiar la lista
 * Precondición: Ambas listas han de ser inicializadas. La lista L2* puede o no estar vacía.
*/
void updateListC(tList P, tPosC p, tListC* L);
/*
 * Objetivo: Modifica la lista de partidos que se encuentra en la posición dada en la lista principal
 * Entrada:
 *    tList P: Lista de partidos a introducir en la lista principal de centros
 *    tPosC p: Posición válida de la lista principal donde incluir la lista P
 *    tListC *L: Lista principal de centros electorales
 * Salidas:
 *    tListC *L: Lista principal modificada tras la inserción de la lista de partidos
 * Precondición: Ambas listas han de estar inicializadas, y la posición ha de ser válida en la lista
*/
void updateValidVotesC(tNumVotes a, tPosC p, tListC* L);
/*
 * Objetivo: Modifica el número de votos válidos del elmento situado en la posición dada
 * Entradas:
 *    tNumVotes a: Valor de los votos válidos dados al determinado centro
 *    tPosC p: Posición deseada donde se encuentra el elemento a ser modificado
 *    tListC *L: Lista pasada para ser modificada
 * Salida: La lista tListC *L tras haber modificado los votos válidos del elemento correspondiente
 * Precondición: La lista ha de estar inicializada. La posición tPosC ha de ser válida en la lista
*/
void updateNullVotes(tNumVotes a, tPosC p, tListC* L);
/*
 * Objetivo: Modifica el número de votos nulos del elemento situado en la posición dada
 * Entradas:
 *    tNumVotes a: Valor de los votos nulos dados al determinado centro
 *    tPosC p: Posición del ítem o elemento en la lista principal
 *    tListC *L: Lista principal de centros donde se modificará su contenido
 * Salidas:
 *    tListC *L: Lista principal modificada
 * Precondición: La lista principal ha de ser inicializada previamente
*/
void deleteAtPositionC(tPosC p, tListC* L);
/*
 * Objetivo: Elimina de la lista un elemento dado una posición
 * Entradas:
 *    tPosC p: Posición del elemento a ser eliminado
 *    tListC *L: Lista a ser modificada
 * Salida: La lista tras haber sido modificada
 * Precondición: tPosC p es una posición válida de la lista
 * Postcondición: Las posiciones de los elementos de la lista pueden haber variado
*/
void deleteListC(tListC* L);
/*
 * Objetivo: Elimina todos los elementos de la lista
 * Entrada: tListC *L a ser borrada
 * Salida: La lista vacía
 * Precondición: Lista inicializada
*/
tPosC findItemC(tCenterName name, tListC L);
/*
 * Objetivo: Devuelve la posición del primer elemento de la lista cuyo nombre del centro sea igual al indicado
 * Entrada:
 *    tCenterName name: Nombre del centro electoral a ser buscado
 *    tListC L: Lista donde se buscará el centro
 * Salida: Una posición, si se diese encontrado el centro se devuelve la posición en la lista.
 * En caso contrario se devuelve NULLC.
 * Precondición: La lista tListC L ha de ser inicializada
*/
bool isEmptyListC(tListC L);
/*
 * Objetivo: Determinar si la lista está vacía
 * Entrada: Una lista L de tipo tListC
 * Salida: Booleano determinando el objetivo
 * Precondición: La lista ha de estar previamente inicializada
*/
tItemC getItemC(tPosC p, tListC L);
/*
 * Objetivo: Devuelve el contenido de un elemento de la lista
 * Entradas:
 *    tPosC p: Posición del elemento a ser obtenido
 *    tListC L: Lista donde obtener el elemento
 * Salida: Se devolverá un tItemC procedente de la lista asociado a la posición aportada
 * Precondición: La posición del elemento a ser obtenido siempre será una válida en la lista,
 * y la lista ha de estar inicializada
*/
tPosC firstC(tListC L);
/*
 * Objetivo: Devolver la primera posición de la lista
 * Entrada: Una lista L de tipo tListC
 * Salida: La posición de tipo tPosC del primer elemento de la lista
 * Precondición: La lista no puede estar vacía y debe haber sido inicializada previamente
*/
tPosC lastC(tListC L);
/*
 * Objetivo: Devuelve la posición del último elemento de la lista
 * Entrada: Una lista L de tipo tListC
 * Salida: La posición tPosC del último elemento de la lista
 * Precondición: La lista ha de estar inicializada
*/
tPosC previousC(tPosC p, tListC L);
/*
 * Objetivo: Devuelve la posición del elemento correspondiente a el de la posición dada
 * Entradas:
 *    tPosC p: Posición del elemento actual
 *    tListC L: Lista en donde encontrar el elemento previo
 * Salida: La posición del elemento previo o NULLC si tPosC p es el primer elemento de la lista
 * Precondición: tPosC p es una posición válida de la lista, y la lista está inicializada
*/
tPosC nextC(tPosC p, tListC L);
/*
 * Objetivo: Devuelve la posición del elemento siguiente a el de la posición dada
 * Entradas:
 *    tPosC p: Posición del elemento actual
 *    tListC L: Lista en donde encontrar el elemento siguiente
 * Salida: La posición del elemento siguiente o NULLC si tPosC p es el último elemento de la lista
 * Precondición: tPosC p es una posición válida de la lista, y la lista ha de estar inicializada
*/

#endif
