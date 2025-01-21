#include <stdio.h>
#include <math.h>
#include "PDB.h"

void lpdbSizeCalc(PDB *pdb) {
    if (pdb->numAtom == 0) {
        pdb->maxRadius = 0.0f;
        return;
    }

    float maxDistance = 0.0f;
    recordPDB *current = pdb->top;

    while (current != NULL) {
        float dx = current->atom.x - pdb->Center.x;
        float dy = current->atom.y - pdb->Center.y;
        float dz = current->atom.z - pdb->Center.z;
        float distance = sqrt(dx * dx + dy * dy + dz * dz);

        if (distance > maxDistance) {
            maxDistance = distance;
        }

        current = current->nextAtom;
    }

    pdb->maxRadius = maxDistance;
}
