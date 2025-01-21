#include <stdio.h>
#include <float.h>
#include "PDB.h"

void lpdbMaxCalc(PDB *pdb) {
    if (pdb->numAtom == 0) {
        pdb->max.x = 0.0f;
        pdb->max.y = 0.0f;
        pdb->max.z = 0.0f;
        return;
    }

    //最小値で初期化して最大値を探索
    pdb->max.x = -FLT_MAX;
    pdb->max.y = -FLT_MAX;
    pdb->max.z = -FLT_MAX;

    recordPDB *current = pdb->top;

    while (current != NULL) {
        if (current->atom.x > pdb->max.x) pdb->max.x = current->atom.x;
        if (current->atom.y > pdb->max.y) pdb->max.y = current->atom.y;
        if (current->atom.z > pdb->max.z) pdb->max.z = current->atom.z;

        current = current->nextAtom;
    }
}
