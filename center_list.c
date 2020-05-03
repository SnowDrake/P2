/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Picado Liñares, David LOGIN 1: david.picado
 * AUTHOR 2: Otero Agraso, Samuel LOGIN 2: s.agraso
 * GROUP: 1.5
 * DATE: 03 / 05 / 2020
 */

#include "types.h"
#include "party_list.h"
#include "center_list.h"


void createEmptyListC(tListC *L) {
    L->lastPos = NULLC;
}
bool isEmptyListC(tListC L) {
    return (L.lastPos == NULLC);
}
tPosC firstC(tListC L) {
    return 0;
}
tPosC lastC(tListC L) {
    return L.lastPos;
}
tPosC nextC(tPosC p, tListC L) {
    if (p == L.lastPos) {
        return NULLC;
    }
    else {
        return ++p;
    }
}
tPosC previousC(tPosC p, tListC L) {
    return --p;
}
bool insertItemC(tItemC d,  tListC *L) {
    // Casos a tener en cuenta:
    // * No poder hacer la inserción
    // * Inserción en la lista vacía
    // * Inserción al principio
    // * Inserción en el medio
    // * Inserción al final de la lista
    tPosC i;

    if (L->lastPos == MAX - 1) { // Lista completa
        return false;
    }
    else {
        if (isEmptyListC(*L) || strcmp(d.centerName, L->data[L->lastPos].centerName) > 0) { // Lista vacía o al final
            L->lastPos++;
            L->data[L->lastPos] = d;
        }
        else {
            L->lastPos++;
            for (i = L->lastPos; i > 0 && strcmp(d.centerName, L->data[i - 1].centerName) < 0; i-- ) {
                L->data[i] = L->data[i - 1]; // Desplazamiento
            }
            L->data[i] = d;
        }
        return true; // La inserción ha sido satisfactoria en cualquiera de los dos casos
    }
}
void deleteAtPositionC(tPosC p, tListC *L) {
    tPosC i;
    L->lastPos--;
    for (i = p;i <= L->lastPos; ++i) {
        L->data[i] = L->data[i+1];
    }
}
tItemC getItemC(tPosC p, tListC L) {
    return L.data[p];
}
tPosC findItemC(tCenterName name, tListC L) {
    tPosC p;
    if (L.lastPos == NULLC) {
        return NULLC;
    } else if ((strcmp(name, L.data[0].centerName)) < 0 || (strcmp(name, L.data[L.lastPos].centerName)) > 0) {
        // Si name es menor o mayor que todos los elementos de la lista, es decir se sale del primer y del último elemnento
        return NULLC; // No se puede dar este caso
    } else {
        for (p = 0; ((p < L.lastPos) && (strcmp(L.data[p].centerName, name)) < 0); p++);
        if (strcmp(name, L.data[p].centerName) == 0) {
            return p;
        } else {
            return NULLC;
        }
    }
}
void updateListC(tList P, tPosC p, tListC* L) {
    L->data[p].partyList = P;
}
void updateNullVotes(tNumVotes a, tPosC p, tListC* L) {
    L->data[p].nullVotes = a;
}
void updateValidVotesC(tNumVotes a, tPosC p, tListC* L) {
    L->data[p].validVotes = a;
}

