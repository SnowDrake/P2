/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Picado Liñares, David LOGIN 1: david.picado
 * AUTHOR 2: Otero Agraso, Samuel LOGIN 2: s.agraso
 * GROUP: 1.5
 * DATE: ** / ** / **
 */

#ifndef TYPES_H
#define TYPES_H

#define NAME_LENGTH_LIMIT 32

typedef char tPartyName[NAME_LENGTH_LIMIT];
typedef char tCenterName[NAME_LENGTH_LIMIT];
typedef int tNumVotes;

typedef struct tItemL {
    tPartyName partyName;
    tNumVotes numVotes;
} tItemL;

#endif //TYPES_H