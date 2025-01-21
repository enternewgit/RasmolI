// lpdbElementCount.cのテスト用 pdbRead.c と 5p21-GC.pdbで実行可能
#include <stdio.h>
#include <stdlib.h>
#include "PDB.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <PDB filename>\n", argv[0]);
        return 1;
    }

    FILE *fp;
    PDB pdbStruct;
    PDB *pdb = &pdbStruct;  // PDB構造体をスタック上に確保
    char *pdbfilename = argv[1];

    // ファイルを開く
    if ((fp = fopen(pdbfilename, "r")) == NULL) {
        fprintf(stderr, "Error: Unable to open file %s\n", pdbfilename);
        return 1;
    }

    // PDBデータを読み込む
    int numCA = pdbRead(fp, pdb);
    if (numCA < 0) {
        fprintf(stderr, "Error reading PDB file\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    // 元素のカウントを実行
    int maxCount = lpdbElementCount(pdb);
    printf("Max atom count for a single element: %d\n", maxCount);

    // 元素ごとのカウントを表示
    printf("Element counts:\n");
    printf("C: %d\n", pdb->elementCount[0]);
    printf("H: %d\n", pdb->elementCount[1]);
    printf("N: %d\n", pdb->elementCount[2]);
    printf("O: %d\n", pdb->elementCount[3]);
    printf("P: %d\n", pdb->elementCount[4]);
    printf("Other: %d\n", pdb->elementCount[5]);

    return 0;
}

