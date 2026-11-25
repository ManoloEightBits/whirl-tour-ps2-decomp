#ifndef GAME_TRICKS_H
#define GAME_TRICKS_H

#include "common/types.h"
#include "game/Parser.h"

// Translation unit 0x00123CD0..: the "trickscores" and "tricklist" blocks of the tricks script
// (keywords in data_0025DC28). Names come from those keywords; the struct names are ours.

#define NUM_TRICKS 81 // the trick table at 0x0025ABC0 has 81 entries of 0x50 bytes

// Filled by a "tricklist" block (func_001240F8).
struct UnkTrickList
{
    int mUnlocked000[NUM_TRICKS];  // 0x000: 0 when the entry has lock "yes", else 1
    int mSequence144[NUM_TRICKS];  // 0x144: func_00124280 of the "sequence" string, -1 if not listed
};

void func_001240F8(UnkParser *p, UnkTrickList *list, char *name); // 0x001240F8: a "tricklist" block

#endif
