#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PDB.h"

#define MAX_LINE_LENGTH 81
#define ATOM_PREFIX "ATOM  "
#define CA_ATOM " CA "

int pdbRead(FILE *fpt, PDB *pdb)
{
    char line[MAX_LINE_LENGTH];
    recordPDB *newRecord, *newCARecord, *lastAtom = NULL, *lastCA = NULL;

    // PDB構造体の初期化
    pdb->numAtom = 0;
    pdb->numCA = 0;
    pdb->top = NULL;
    pdb->topCA = NULL;
    pdb->current = NULL;
    pdb->currentCA = NULL;

    // ファイルを1行ずつ読み込む
    while (fgets(line, sizeof(line), fpt) != NULL)
    {
        // 行がATOMで始まるかチェック
        if (strncmp(line, ATOM_PREFIX, 6) == 0)
        {
            // 新しいrecordPDBのメモリを割り当て
            newRecord = (recordPDB *)malloc(sizeof(recordPDB));
            if (newRecord == NULL)
            {
                printf("Memory allocation failed\n");
                return -1;
            }

            // 原子の座標と追加情報を読み込む
            newRecord->atom.x = atof(line + 30);
            newRecord->atom.y = atof(line + 38);
            newRecord->atom.z = atof(line + 46);
            strncpy(newRecord->atom.atomName, line + 12, 4);
            newRecord->atom.atomName[4] = '\0';
            strncpy(newRecord->atom.resName, line + 17, 3);
            newRecord->atom.resName[3] = '\0';
            newRecord->atom.resNumber = atoi(line + 22);
            newRecord->atom.occupancy = atof(line + 54);
            newRecord->atom.tempFactor = atof(line + 60);
            strncpy(newRecord->atom.element, line + 76, 2);
            newRecord->atom.element[2] = '\0';
            newRecord->nextAtom = NULL;
            newRecord->nextCA = NULL;

            // 原子リストにリンク
            if (lastAtom == NULL)
            {
                pdb->top = newRecord; // 最初の原子
                pdb->current = newRecord;
            }
            else
            {
                lastAtom->nextAtom = newRecord; // 前の原子にリンク
            }
            lastAtom = newRecord;
            pdb->current = newRecord;
            pdb->numAtom++;

            // CA原子かどうかチェック
            if (strncmp(line + 12, CA_ATOM, 4) == 0)
            {
                // 新しいCAリストのノードを割り当て
                newCARecord = (recordPDB *)malloc(sizeof(recordPDB));
                if (newCARecord == NULL)
                {
                    printf("Memory allocation failed\n");
                    return -1;
                }

                // CAノードにデータをコピー
                *newCARecord = *newRecord;
                newCARecord->nextCA = NULL;

                if (lastCA == NULL)
                {
                    pdb->topCA = newCARecord; // 最初のCA原子
                    pdb->currentCA = newCARecord;
                }
                else
                {
                    lastCA->nextCA = newCARecord; // 前のCA原子にリンク
                }
                lastCA = newCARecord;
                pdb->currentCA = newCARecord;
                pdb->numCA++;
            }
        }
    }

    return pdb->numCA; // 読み込んだCA原子の数を返す
}
