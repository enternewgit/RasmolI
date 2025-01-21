/*lpdbResCount.c*/
#include "PDB.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define AMINO_ACID_COUNT 20
#define TOTAL_RESIDUE_TYPES 21  // 20種類のアミノ酸 + その他(OTH)

int lpdbResCount(PDB *pdb)
{
    // アミノ酸の名前を配列で定義
    static const char *amino_acids[TOTAL_RESIDUE_TYPES] = {
        "ALA", "ARG", "ASN", "ASP", "CYS", "GLN", "GLU", "GLY", "HIS", "ILE",
        "LEU", "LYS", "MET", "PHE", "PRO", "SER", "THR", "TRP", "TYR", "VAL",
        "OTH"
    };

    // カウンターを0に初期化
    for (int i = 0; i < TOTAL_RESIDUE_TYPES; i++) {
        pdb->resCount[i] = 0;
    }

    // 各α炭素について残基をカウント
    for (pdb->currentCA = pdb->topCA; pdb->currentCA != NULL; pdb->currentCA = pdb->currentCA->nextCA) {
        int found = 0;
        // 20種類のアミノ酸と比較
        for (int i = 0; i < AMINO_ACID_COUNT; i++) {
            if (strcmp(pdb->currentCA->atom.resName, amino_acids[i]) == 0) {
                pdb->resCount[i]++;
                found = 1;
                break;
            }
        }
        // 20種類に該当しない場合はOTHとしてカウント
        if (!found) {
            pdb->resCount[TOTAL_RESIDUE_TYPES - 1]++;
        }
    }

    // 最大のカウント数を見つける
    int max_count = 0;
    for (int i = 0; i < TOTAL_RESIDUE_TYPES; i++) {
        if (pdb->resCount[i] > max_count) {
            max_count = pdb->resCount[i];
        }
    }

    return max_count;
}

void lpdbFree(PDB *pdb) {
    recordPDB *current = pdb->top;
    recordPDB *next;

    // 原子リストのメモリを解放
    while (current != NULL) {
        next = current->nextAtom;
        //printf("Freeing memory at %p\n", current); // デバッグ出力
        free(current);
        current = next;
    }
    pdb->top = NULL; // 二重解放を防ぐためにポインタをNULLに設定

    current = pdb->topCA;
    // CAリストのメモリを解放
    while (current != NULL) {
        next = current->nextCA;
        current->nextCA = NULL; // CAリストのリンクを解除
        //printf("Freeing CA memory at %p\n", current); // デバッグ出力
        free(current);
        current = next;
    }
    pdb->topCA = NULL; // 二重解放を防ぐためにポインタをNULLに設定
}
