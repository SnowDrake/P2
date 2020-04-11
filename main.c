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

#define CODE_LENGTH 2

int devolverParam(char param[NAME_LENGTH_LIMIT+1]) {  // Función usada para convertir un string en un entero
    const char * str = param;
    int x;
    sscanf(param, "%d", &x);
    return x;
}

void createCenter(tListC *list, tCenterName name, char param[NAME_LENGTH_LIMIT+1]) {
    tItemC newCenter;
    newCenter.totalVoters = devolverParam(param);
    strcpy(newCenter.centerName, name);
    newCenter.validVotes = newCenter.nullVotes = 0;

    tItemC item; // Variable auxiliar que nos permitirá manejar con los campos de tItemC

    bool check;

    if (findItemC(name, *list) == NULLC) { // Centro desconocido en la lista
        check = insertItemC(newCenter, list); // Comprobamos si se ja insertado bien
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
    tItemL Party;
    Party.numVotes = 0;
    strcpy(Party.partyName, party);

    tItemC item;

    bool check;

    tPosC p;
    p = findItemC(center, *list);
    item = getItemC(p, *list);
    if (p == NULLC) { // Centro electoral no creado en la lista
        printf("+ Error: New not possible\n");
    }
    else { // El centro si está en la lista
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
    tPosC p;
    tPosL r;
    tItemC mainItem; // Item para manejar los campos de la lista
    int Null = 0;
    int Valid = 0;
    int PartyVotes = 0;
    p = findItemC(center, *list);
    mainItem = getItemC(p, *list);

    if (p == NULLC) {
        printf("+ Error: Vote not possible\n"); // El centro no se encuentra en la lista
    }
    else {
        if (findItem(party, mainItem.partyList) == LNULL) { // El partido no se encuentra en la lista de centros electorales
            if (mainItem.validVotes + mainItem.nullVotes < mainItem.totalVoters) {
                Null = mainItem.nullVotes;
                Null++;
                updateNullVotes(Null, p, list);
            }
            printf("+ Error: Vote not possible. Party %s not found in center %s. NULLVOTE\n", party, mainItem.centerName);
        }
        else { // El partido si se encuentra en la lista
            r = findItem(party, mainItem.partyList);
            if (mainItem.validVotes + mainItem.nullVotes < mainItem.totalVoters) {
                Valid = mainItem.validVotes;
                Valid++;
                updateValidVotesC(Valid, p, list);
                PartyVotes = getItem(r, mainItem.partyList).numVotes;
                PartyVotes++;
                updateVotes(PartyVotes, r, &mainItem.partyList);
            }
            printf("* Vote: center %s party %s numvotes %d\n", mainItem.centerName, party, getItem(r, mainItem.partyList).numVotes);
        }
    }
}
void print_list_Stats(tListC *list) {
    tPosC pos;
    tItemC item;
    tPosL posL;
    tItemL itemL;

    if (!isEmptyListC(*list)) {
        pos = firstC(*list);
        while (pos != NULLC) {
            item = getItemC(pos, *list);
            printf("Center %s\n", item.centerName);
            if (!isEmptyList(item.partyList)) {
                posL = first(item.partyList);
                while (posL != LNULL) {
                    itemL = getItem(posL, item.partyList);
                    if (item.validVotes == 0) {
                        printf("Party %s numvotes %d (0.00%%)\n", itemL.partyName, itemL.numVotes);
                    }
                    else {
                        printf("Party %s numvotes %d (%.2f%%)\n", itemL.partyName, itemL.numVotes, ((float)itemL.numVotes/item.validVotes)*100);
                    }
                    posL = next(posL, item.partyList);
                }
            }
            printf("Null votes %d\n", item.nullVotes);
            if (item.totalVoters == 0) {
                printf("Participation: %d votes from %d voters (0.00%%)\n", item.validVotes + item.nullVotes, item.totalVoters);
            }
            else {
                printf("Participation: %d votes from %d voters (%.2f%%)\n", item.validVotes + item.nullVotes, item.totalVoters, (((float)item.validVotes + item.nullVotes)/item.totalVoters)*100);
            }
            pos = nextC(pos, *list);
        }
    }
}
void removeCenter(tListC *list) {
    int check = 0; // Variable que indica si hay centros para eliminar o no
    tPosC pos;
    tListC LCopia; // Lista de tipo tListC para hacer una copia
    createEmptyListC(&LCopia);
    tItemC permanent; // Variable donde guardaremos aquellos items que deben quedarse en la lista
    tItemL removed; // Variable donde almacenar los items que serán eliminados de la lista

    copyListC(*list, &LCopia); // Hacemos una copia de la lista principal para manejar con ella

    while (!isEmptyListC(*list)) { // Borrado de la lista principal
        deleteAtPositionC(firstC(*list), list);
    }

    if (!isEmptyListC(LCopia)) { // Recorremos la copia
        pos = firstC(LCopia);
        while (pos != NULLC) {
            if (getItemC(pos, LCopia).validVotes != 0) { // Los centros que han de quedarse en la lista *L
                strcpy(permanent.centerName, getItemC(pos, LCopia).centerName);
                copyList(getItemC(pos, LCopia).partyList, &permanent.partyList);
                permanent.validVotes = getItemC(pos, LCopia).validVotes;
                permanent.totalVoters = getItemC(pos, LCopia).totalVoters;
                permanent.nullVotes = getItemC(pos, LCopia).nullVotes;
                insertItemC(permanent, list); // Copiamos esos centros en la lista principal
            }
            else { // Los centros que serán eliminados más adelante
                strcpy(removed.partyName, getItemC(pos, LCopia).centerName);
                removed.numVotes = 0;
                printf("* Remove: center %s\n", removed.partyName);
                check++;
            }
            pos = nextC(pos, LCopia);
        }
    }
    if (check == 0) { // Ningún centro será eliminado
        printf("* Remove: no centers removed\n");
    }
    deleteListC(&LCopia); // Por último eliminamos la lista copia de la principal
}

void processCommand(char commandNumber[CODE_LENGTH+1], char command, char param1[NAME_LENGTH_LIMIT+1], char param2[NAME_LENGTH_LIMIT+1], tListC *L) {


    switch(command) {
        case 'C': {
            printf("********************\n");
            printf("%s %c: center %s totalvoters %s\n", commandNumber, command, param1, param2);
            printf("\n");
            createCenter(L, param1, param2);
            break;
        }
        case 'N': {
            printf("********************\n");
            printf("%s %c: center %s party %s\n", commandNumber, command, param1, param2);
            printf("\n");
            newParty(L, param1, param2);
            break;
        }
        case 'V': {
            printf("********************\n");
            printf("%s %c: center %s party %s\n", commandNumber, command, param1, param2);
            printf("\n");
            voteParty(L, param1, param2);
            break;
        }
        case 'R': {
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            printf("\n");
            removeCenter(L);
            break;
        }
        case 'S': {
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            printf("\n");
            print_list_Stats(L);
            break;
        }

        default: {
            printf("+ Fatal error: Command not found\n");
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

    readTasks(filename, &L);

    return 0;
}