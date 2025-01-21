#include <stdio.h>
#include <float.h>
#include "PDB.h"

void lpdbMinCalc(PDB *pdb) {
    if (pdb->numAtom == 0) {
        pdb->min.x = 0.0f;
        pdb->min.y = 0.0f;
        pdb->min.z = 0.0f;
        return;
    }

    //最大値で初期化して最小値を探索
    pdb->min.x = FLT_MAX;
    pdb->min.y = FLT_MAX;
    pdb->min.z = FLT_MAX;

    recordPDB *current = pdb->top;

    while (current != NULL) {
        if (current->atom.x < pdb->min.x) pdb->min.x = current->atom.x;
        if (current->atom.y < pdb->min.y) pdb->min.y = current->atom.y;
        if (current->atom.z < pdb->min.z) pdb->min.z = current->atom.z;

        current = current->nextAtom;
    }
}
