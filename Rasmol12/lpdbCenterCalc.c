#include <stdio.h>
#include "PDB.h"

void lpdbCenterCalc(PDB *pdb) {
    if (pdb->numAtom == 0) {
        pdb->Center.x = 0.0f;
        pdb->Center.y = 0.0f;
        pdb->Center.z = 0.0f;
        return;
    }

    float sumX = 0.0f, sumY = 0.0f, sumZ = 0.0f;
    recordPDB *current = pdb->top;

    while (current != NULL) {
        sumX += current->atom.x;
        sumY += current->atom.y;
        sumZ += current->atom.z;
        current = current->nextAtom;
    }

    pdb->Center.x = sumX / pdb->numAtom;
    pdb->Center.y = sumY / pdb->numAtom;
    pdb->Center.z = sumZ / pdb->numAtom;
}
