/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Picado Liñares, David LOGIN 1: david.picado
 * AUTHOR 2: Otero Agraso, Samuel LOGIN 2: s.agraso
 * GROUP: 1.5
 * DATE: ** / ** / **
 */

#include "party_list.h"

/* Write your code here... */

bool createNode(tPosL * p) { // Función interna a este archivo, no aparace en el archivo de cabecera
    *p = malloc(sizeof(struct tNode));
    return (*p == LNULL?false:true);
} // Nos permitirá crear los nodos para la lista
tPosL findPosition(tItemL d, tList L) { // Función auxiiar que permitirá facilitar el código de inserción
    tPosL p;
    p = L;
    while ((p->next != LNULL) && (strcmp(p->next->data.partyName, d.partyName) < 0)) { // Devoverá la posición anterior a la del valor deseado de insertar
        p = p->next;
    }
    return p;
}
void createEmptyList(tList* L) {
    *L = LNULL; // Creación de una lista vacía, donde el primer puntero de la lista apunte a ninguna dirección de memoria
}
bool insertItem(tItemL d, tList* L) {
    // Casos a tener en cuenta:
    // * No poder hacer la inserción
    // * Inserción en lista vacía
    // * Inserción al principio
    // * Inserción en el medio
    // * Inserción al final de la lista
    tPosL q, r;
    if (!createNode(&q)) { // No se puede hacer la inserción
        return false;
    }
    else {
        q->data = d;
        q->next = LNULL;
        if (*L == LNULL) { // Inserción en lista vacía
            *L = q; // Asignamos L con el nodo q
        }
        else if (strcmp(d.partyName, (*L)->data.partyName) < 0) { // Inserción al principio
            q->next = *L;
            *L = q;
        }
        else { // Inserción en el final o en el medio de la lista
            r = findPosition(d, *L);
            q->next = r->next;
            r->next = q;
        }
        return true; // En cualquiera de los casos hemos logrado insertar exitosamente en la lista
    }
}
bool copyList(tList L1, tList* L2) { // No es imprescindible que L2 sea una lista vacía
    tPosL p, q = NULL, r;
    bool retorno = true;
    createEmptyList(L2);
    if (!isEmptyList(L1)) {
        p = L1;
        while ((p != LNULL) && createNode(&r)) {
            r->data = p->data;
            r->next = LNULL;
            if (p == L1) { // cabeza de la lista
                *L2 = r; // *L2 apunta a donde r
                q = r;
            }
            else { // No en la cabeza de la lista
                q->next = r; // Unimos nodo
                q = r;
            }
            p = p->next;
        }
        if (p != LNULL) {
            retorno = false;
            deleteList(L2); // Fallamos en la creación de la lista, borramos
        }
    }
    return retorno;
}
void updateVotes(tNumVotes a, tPosL p, tList* L) {
    p->data.numVotes = a;
}
void deleteAtPosition(tPosL p, tList* L) {
    // Tenemos tres posibles situaciones
    // Que p sea la cabeza de la lista
    // Que p sea el último de la lista
    // Que p sea otro elemento de la lista
    // Al final tendremos que liberar comunmente a p
    tPosL q;
    if (p == *L) {
        *L = (*L)->next;
    }
    else if (p->next == LNULL) { // Caso de la última posición
        for (q = *L; q->next != p; q = q->next);
        q->next = LNULL;
    }
    else { // Borramos en otra posición
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q; // Luego liberamos
    }
    free(p); // Hacemos ya el free de la lista de la posición de p
}
void deleteList(tList* L) {
    tPosL p;
    while (*L != LNULL) {
        p = *L;
        *L = (*L)->next;
        free(p); // Liberamos p para cada una de las posiciones de la lista
    }
}
tPosL findMiddle(tPosL Inicio, tPosL Final) { // Función exclusiva para encontrar la mitad de la lista
    tPosL izq;
    tPosL der;
    if (Inicio == LNULL) { // Si la lista está vacía
        return LNULL;
    }
    izq = Inicio;
    der = Inicio->next;

    while (der != Final) {
        der = der->next;
        if (der != Final) {
            izq = izq->next;
            der = der->next;
        }
    }
    return izq;
}
tPosL findItem(tPartyName name, tList L) { // Vamos a usar la búsqueda binaria para encontrar la posición
    tPosL inicio = first(L); // Inicio de la lista
    tPosL final = LNULL; // Final de la lista, es decir el NULL
    tPosL medio; // Variable para declarar la mitad de la lista
    do {
        medio = findMiddle(inicio, final); // Encontramos la mitad
        if (medio == LNULL) {
            return LNULL; // De no existir, la lista está vacía
        }
        if (strcmp(medio->data.partyName, name) == 0) { // Encontramos la posición
            return medio;
        }
        else if (strcmp(medio->data.partyName, name) < 0) {
            inicio = medio->next;
        }
        else {
            final = medio;
        }
    } while (final == LNULL || final != inicio);
    return LNULL; // Ya no pudimos encontrar la posición
}
bool isEmptyList(tList L) {
    if (L == LNULL) {
        return true;
    }
    else {
        return false;
    }
}
tItemL getItem(tPosL p, tList L) {
    return p->data;
}
tPosL first(tList L) {
    return L;
}
tPosL last(tList L) {
    tPosL p;
    for (p = L; p->next != LNULL; p = p->next);
    return p;
}
tPosL previous(tPosL p, tList L) {
    tPosL q;
    if (p == L) { // En la lista solo hay un elemento
        return LNULL;
    }
    else { // Desventaja de simple enlace, debemos recorrer toda la lista hasta que el siguiente de q sea nuestro p
        for (q = L; q->next != p; q = q->next);
        return q;
    }
}
tPosL next(tPosL p, tList L) {
    return p->next;
}