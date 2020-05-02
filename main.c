/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Picado Liñares, David LOGIN 1: david.picado
 * AUTHOR 2: Otero Agraso, Samuel LOGIN 2: s.agraso
 * GROUP: 1.5
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include "types.h"
#include "center_list.h"
#include <stdbool.h>

#define CODE_LENGTH 2

int devolverParam(char param[NAME_LENGTH_LIMIT+1]) {  // Función usada para convertir un string en un entero
    const char * str = param;
    int x;
    sscanf(param, "%d", &x);
    return x;
}

void freePartyList(tListC *L, tPosC p) { // Función para el borrado de la lista de partidos de memoria de la lista de centros dada una posición
    tItemC item;
    createEmptyList(&item.partyList);
    item = getItemC(p, *L);
    while (!isEmptyList(item.partyList)) {
        deleteAtPosition(first(item.partyList), &item.partyList);
    }
    updateListC(item.partyList, p, L);
}

void freeListC(tListC *L) { // Borrado completo de la lista principal incluyendo la de los partidos de los centros
    tItemC item;
    createEmptyList(&item.partyList);
    while (!isEmptyListC(*L)) {
        freePartyList(L, firstC(*L));
        deleteAtPositionC(firstC(*L), L);
    }
}

void createCenter(tListC *list, tCenterName name, char param[NAME_LENGTH_LIMIT+1]) {
    // Declaración del nuevo ítem a añadir a la lista
    tItemC newCenter;
    newCenter.totalVoters = devolverParam(param);
    strcpy(newCenter.centerName, name);
    newCenter.validVotes = newCenter.nullVotes = 0;

    tItemC item; // Variable auxiliar que nos permitirá manejar con los campos de tItemC

    bool check;

    if (findItemC(name, *list) == NULLC) { // Centro desconocido en la lista
        check = insertItemC(newCenter, list); // Comprobamos si se ha insertado bien
        item = getItemC(findItemC(name, *list), *list); // Obtendremos el valor del item correspondiente a ese centro
        createEmptyList(&item.partyList); // Creamos la lista de partidos en el item
        updateListC(item.partyList, findItemC(name, *list), list); // Modificamos la lista principal añadiendo la lista de partidos del item
        if (check == true) {
            printf("* Create: center %s totalvoters %s\n", getItemC(findItemC(name, *list), *list).centerName, param);
        }
        else {
            printf("+ Error: Create not possible\n");
        }
    }
    else { // El centro ya está en la lista
        printf("+ Error: Create not possible\n");
    }

}
void newParty(tListC *list, tCenterName center, tPartyName party) {
    // Declaración del ítem del nuevo partido a añadir
    tItemL Party;
    Party.numVotes = 0;
    strcpy(Party.partyName, party);

    tItemC item; // Item auxiliar para manejar los centros de la lista

    bool check; // Variable booleana para comprobar la función de insertItem

    tPosC p; // Posición del centro en la lista
    p = findItemC(center, *list);

    if (p == NULLC) { // Centro electoral no creado en la lista
        printf("+ Error: New not possible\n");
    }
    else { // El centro si está en la lista
        item = getItemC(p, *list);
        if (findItem(party, item.partyList) == LNULL) { // El partido no está en la lista del centro electoral
            check = insertItem(Party, &item.partyList); // Comprobamos si la inserción ha sido satisfactoria
            updateListC(item.partyList, p, list); // Modificamos la lista principal añadiendo la lista de partidos del item
            if (check == true) {
                printf("* New: center %s party %s\n", item.centerName, getItem(findItem(party, item.partyList), getItemC(p, *list).partyList).partyName);
            }
            else {
                printf("+ Error: New not possible\n");
            }
        }
        else { // Ya tenemos el partido en la lista
            printf("+ Error: New not possible\n");
        }
    }
}
void voteParty(tListC *list, tCenterName center, tPartyName party) {
    tPosC p; // Para encontrar la posición del centro
    tPosL r; // Para encontrar la posición del partido
    tItemC mainItem; // Item para manejar los campos de la lista
    int Null = 0;
    int Valid = 0;
    int PartyVotes = 0;
    p = findItemC(center, *list);

    if (p == NULLC) {
        printf("+ Error: Vote not possible\n"); // El centro no se encuentra en la lista
    }
    else {
        mainItem = getItemC(p, *list);
        if (findItem(party, mainItem.partyList) == LNULL) { // El partido no se encuentra en la lista de centros electorales
            Null = mainItem.nullVotes;
            Null++;
            updateNullVotes(Null, p, list); // Votos nulos actualizados del centro
            printf("+ Error: Vote not possible. Party %s not found in center %s. NULLVOTE\n", party, mainItem.centerName);
        }
        else { // El partido si se encuentra en la lista
            r = findItem(party, mainItem.partyList); // Posición del partido
            Valid = mainItem.validVotes;
            Valid++;
            updateValidVotesC(Valid, p, list); // Aumentamos los votos válidos del centro
            PartyVotes = getItem(r, mainItem.partyList).numVotes;
            PartyVotes++;
            updateVotes(PartyVotes, r, &mainItem.partyList); // Aumentamos +1 los votos de los partidos
            printf("* Vote: center %s party %s numvotes %d\n", mainItem.centerName, party, getItem(r, mainItem.partyList).numVotes);
        }
    }
}
void print_list_Stats(tListC list) {
    tPosC pos; // Iterar la lista de centros
    tItemC item;
    tPosL posL; // Iterar la lista de partidos dentro de la lista de centros
    tItemL itemL;

    if (!isEmptyListC(list)) {
        pos = firstC(list);
        while (pos != NULLC) { // Hasta que no se llegue al final de la lista
            item = getItemC(pos, list);
            printf("Center %s\n", item.centerName);
            if (!isEmptyList(item.partyList)) {
                posL = first(item.partyList);
                while (posL != LNULL) {
                    itemL = getItem(posL, item.partyList);
                    if (item.validVotes == 0) { // Evitar la posibilidad de tener: x/0 = NaN
                        printf("Party %s numvotes %d (0.00%%)\n", itemL.partyName, itemL.numVotes);
                    }
                    else {
                        printf("Party %s numvotes %d (%.2f%%)\n", itemL.partyName, itemL.numVotes, ((float)itemL.numVotes/item.validVotes)*100);
                    }
                    posL = next(posL, item.partyList);
                }
            }
            printf("Null votes %d\n", item.nullVotes);
            printf("Participation: %d votes from %d voters (%.2f%%)\n", item.validVotes + item.nullVotes, item.totalVoters, (((float)item.validVotes + item.nullVotes)/item.totalVoters)*100);
            pos = nextC(pos, list);
        }
    }
    else {
        printf("Empty list\n");
    }
}
void removeCenter(tListC *list) {
    int check = 0; // Variable que indica si hay centros para eliminar o no
    tPosC pos; // Iterar en la lista de centros manejando posiciones
    bool act = false; // Control de borrado

    if (!isEmptyListC(*list)) { // Recorremos la lista principal
        pos = firstC(*list);
        while (pos != NULLC) {
            if (getItemC(pos, *list).validVotes == 0) { // Borrado de aquellos centros cuyos votos válidos sean 0
                printf("* Remove: center %s\n", getItemC(pos, *list).centerName);
                freePartyList(list, pos); // Borrado de la lista de partidos de los centros antes del borrado del centro
                deleteAtPositionC(pos, list); // Borrado final total del centro (habrá que tener cuidado con el desplazamiento de los elementos)
                if (!isEmptyListC(*list)) { // Lista no vacía tras el borrado
                    act = true; // Activamos el control de borrado
                }
                else { // Lista completamente vacía tras el borrado
                    pos = NULLC;
                }
                check++; // Activamos el check, hay centros a eliminar
            }
            if (pos != NULLC) { // Comprobamos posible lista vacía tras un posible borrado
                if (act == false) { // Iteración donde no se ha encontrado ningún borrado de centro
                    pos = nextC(pos, *list); // Avanzamos en la lista con toda normalidad
                }
                if (act == true) { // Detectamos un borrado
                    pos = firstC(*list); // Volvemos al principio de la lista
                }
            }
            act = false; // Reiniciamos el control de borrado para la siguiente iteración
        }
    }
    if (check == 0) { // Ningún centro será eliminado
        printf("* Remove: no centers removed\n");
    }
}

void processCommand(char commandNumber[CODE_LENGTH+1], char command, char param1[NAME_LENGTH_LIMIT+1], char param2[NAME_LENGTH_LIMIT+1], tListC *L) {


    switch(command) {
        case 'C': { // Crear un centro electoral en la lista
            printf("********************\n");
            printf("%s %c: center %s totalvoters %s\n", commandNumber, command, param1, param2);
            printf("\n");
            createCenter(L, param1, param2);
            break;
        }
        case 'N': { // Crear partido en la lista de partidos del centro electoral
            printf("********************\n");
            printf("%s %c: center %s party %s\n", commandNumber, command, param1, param2);
            printf("\n");
            newParty(L, param1, param2);
            break;
        }
        case 'V': { // Votar a un partido
            printf("********************\n");
            printf("%s %c: center %s party %s\n", commandNumber, command, param1, param2);
            printf("\n");
            voteParty(L, param1, param2);
            break;
        }
        case 'R': { // Borrar de la lista aquellos centros con cero votos válidos
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            printf("\n");
            removeCenter(L);
            break;
        }
        case 'S': { // Mostrar la lista principal, así como sus estadísticas
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            printf("\n");
            print_list_Stats(*L);
            break;
        }

        default: {
            printf("FATAL ERROR: Command not found!\n");
            break;
        }
    }
}

void readTasks(char *filename, tListC *L) {
    FILE *df;
    char commandNumber[CODE_LENGTH+1], command, param1[NAME_LENGTH_LIMIT+1], param2[NAME_LENGTH_LIMIT+1];

    df = fopen(filename, "r");
    if (df != NULL) {
        while (!feof(df)) {
            char format[16];
            sprintf(format, "%%%is %%c ", CODE_LENGTH);
            fscanf(df, format, commandNumber, &command);
            if (command == 'S' || command == 'R') {
                param1[0] = '\0';
                param2[0] = '\0';
            } else {
                sprintf(format, "%%%is %%%is", NAME_LENGTH_LIMIT, NAME_LENGTH_LIMIT);
                fscanf(df, format, param1, param2);
            }
            processCommand(commandNumber, command, param1, param2, L);
        }
        fclose(df);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args) {
    // Creación e inicialización de la lista principal de centros
    tListC L;
    createEmptyListC(&L);

    char *filename = "new.txt";

    if (nargs > 1) {
        filename = args[1];
    } else {
        #ifdef INPUT_FILE
        filename = INPUT_FILE;
        #endif
    }

    readTasks(filename, &L); // Pasamos la lista como parámetro a través de las funciones
    freeListC(&L); // Liberamos de memoria la lista principal

    return 0;
}
