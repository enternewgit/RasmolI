#include <stdio.h>
#include "PDB.h"

void lpdbInfoPrint(FILE *fpt, PDB *pdb, int mode) {
    if (mode & 1) { // center
        fprintf(fpt, "center: %.2f %.2f %.2f\n", pdb->Center.x, pdb->Center.y, pdb->Center.z);
    }
    if (mode & 2) { // maxRadius
        fprintf(fpt, "maxRadius: %.2f\n", pdb->maxRadius);
    }
    if (mode & 4) { // min
        fprintf(fpt, "min: %.2f %.2f %.2f\n", pdb->min.x, pdb->min.y, pdb->min.z);
    }
    if (mode & 8) { // max
        fprintf(fpt, "max: %.2f %.2f %.2f\n", pdb->max.x, pdb->max.y, pdb->max.z);
    }
}
