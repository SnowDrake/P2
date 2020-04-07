/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
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

void print_list(tListC list) {
    tPosC pos;
    tItemC item;

    printf("(");
    if (!isEmptyListC(list)) {
        pos = firstC(list);
        while (pos != NULLC) {
            item = getItemC(pos, list);
            printf(" %s totalvoters %d", item.centerName, item.totalVoters);
            pos = nextC(pos, list);
        }
    }
    printf(")\n");
}
void print_listPARTIES(tList list) {
    tPosL pos;
    tItemL item;

    printf("(");
    if (!isEmptyList(list)) {
        pos = first(list);
        while (pos != LNULL) {
            item = getItem(pos, list);
            printf(" %s totalVotes %d", item.partyName, item.numVotes);
            pos = next(pos, list);
        }
    }
    printf(")\n");
}
void print_listREMOVE(tList list) {
    tPosL pos;
    tItemL item;

    if (!isEmptyList(list)) {
        pos = first(list);
        while (pos != LNULL) {
            item = getItem(pos, list);
            printf("Remove: center %s\n", item.partyName);
            pos = next(pos, list);
        }
    }
}

void createCenter(tListC *list, tCenterName name, char param[NAME_LENGTH_LIMIT+1]) {
    tItemC newCenter;
    newCenter.totalVoters = devolverParam(param);
    strcpy(newCenter.centerName, name);
    newCenter.validVotes = newCenter.nullVotes = 0;

    bool check;
    if (findItemC(name, *list) == NULLC) {
        check = insertItemC(newCenter, list);
        createEmptyList(&list->data[findItemC(name, *list)].partyList); // Se crea la lista de partidos de determinada lista
        if (check == true) {
            printf("* Create: center %s totalvoters %s\n", getItemC(findItemC(name, *list), *list).centerName, param);
        }
        else {
            printf("+ Error: Create not possible\n");
        }
    }
    else {
        printf("+ Error: Create not possible\n");
    }

}
void newParty(tListC *list, tCenterName center, tPartyName party) {
    tItemL Party;
    Party.numVotes = 0;
    strcpy(Party.partyName, party);

    bool check;
    tPosC p;
    p = findItemC(center, *list);
    if (p == NULLC) { // Centro electoral no creado en la lista
        printf("+ Error: New not possible\n");
    }
    else { // El centro si está en la lista
        if (findItem(party, list->data[p].partyList) == LNULL) { // El partido no está en la lista del centro electoral
            check = insertItem(Party, &list->data[p].partyList);
            if (check == true) {
                printf("* New: center %s party %s\n", getItemC(findItemC(center, *list), *list).centerName, party);
            }
            else {
                printf("+ Error: New not possible\n");
            }
        }
        else {
            printf("+ Error: New not possible\n");
        }
    }
}
void voteParty(tListC *list, tCenterName center, tPartyName party) {
    tPosC p;
    tPosL r;
    int Null = 0;
    int Valid = 0;
    int PartyVotes = 0;
    p = findItemC(center, *list);

    if (p == NULLC) {
        printf("+ Error: Vote not possible\n");
    }
    else {
        if (findItem(party, list->data[p].partyList) == LNULL) { // El partido no se encuentra en la lista de centros electorales
            Null = getItemC(p, *list).nullVotes;
            Null++;
            updateNullVotes(Null, p, list);
            printf("+ Error: Vote not possible. Party %s not found in center %s. NULLVOTE\n", party, getItemC(p, *list).centerName);
        }
        else { // El partido si se encuentra en la lista
            Valid = getItemC(p, *list).validVotes;
            Valid++;
            updateValidVotesC(Valid, p, list);
            r = findItem(party, list->data[p].partyList);
            PartyVotes = getItem(r, list->data[p].partyList).numVotes;
            PartyVotes++;
            updateVotes(PartyVotes, r, &list->data[p].partyList);
            printf("* Vote: center %s party %s numvotes %d\n", getItemC(p, *list).centerName, party, getItem(r, list->data[p].partyList).numVotes);
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
            if (!isEmptyList(list->data[pos].partyList)) {
                posL = first(list->data[pos].partyList);
                while (posL != LNULL) {
                    itemL = getItem(posL, list->data[pos].partyList);
                    if (list->data[pos].validVotes == 0) {
                        printf("Party %s numvotes %d (0.00%%)\n", itemL.partyName, itemL.numVotes);
                    }
                    else {
                        printf("Party %s numvotes %d (%.2f%%)\n", itemL.partyName, itemL.numVotes, ((float)itemL.numVotes/item.validVotes)*100);
                    }
                    posL = next(posL, list->data[pos].partyList);
                }
            }
            printf("Null votes %d\n", item.nullVotes);
            if (item.validVotes == 0) {
                printf("Participation: %d votes from %d voters (0.00%%)\n", item.validVotes + item.nullVotes, item.totalVoters);
            }
            else {
                printf("Participation: %d votes from %d voters (%.2f%%)\n", item.validVotes + item.nullVotes, item.totalVoters, (((float)item.validVotes + item.nullVotes)/item.totalVoters)*100);
            }
            pos = nextC(pos, *list);
        }
    }
}

void processCommand(char commandNumber[CODE_LENGTH+1], char command, char param1[NAME_LENGTH_LIMIT+1], char param2[NAME_LENGTH_LIMIT+1], tListC *L) {

    //printf("Read from input file: %s %c %s %s\n", commandNumber, command, param1, param2);

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
        case 'R': { // Terminado al 50%, muestra los partidos a remover pero hay que arreglar la eliminación
            int check = 0;
            tPosC pos;
            tList list;
            tPosL aux;
            struct tItemL names;
            createEmptyList(&list);
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            printf("\n");

            if (!isEmptyListC(*L)) {
                pos = firstC(*L);
                while (pos != NULLC) {
                    if (L->data[pos].validVotes == 0) {
                        strcpy(names.partyName, getItemC(pos, *L).centerName);
                        names.numVotes = 0;
                        insertItem(names, &list);
                        deleteAtPositionC(findItemC(names.partyName, *L), L);
                        check++;
                    }
                    pos = nextC(pos, *L);
                }/*
                while (!isEmptyListC(*L) && isEmptyList(list)) {
                    deleteAtPositionC(findItemC(getItem(first(list), list).partyName, *L), L);
                }*/
            }
            if (check == 0) {
                printf("Remove: no centers removed\n");
            }
            else if (check > 0) {
                print_listREMOVE(list);
            }
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