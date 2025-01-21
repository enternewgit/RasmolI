#include "PDB.h"
#include <string.h>
#include <stdio.h>

int lpdbElementCount(PDB* pdb) {
    if (pdb == NULL || pdb->top == NULL) {
        return 0; // PDBデータが無効の場合は0を返す
    }

    // 元素数カウント用の配列を初期化
    for (int i = 0; i < 6; i++) {
        pdb->elementCount[i] = 0;
    }

    recordPDB* current = pdb->top;

    // 原子リストを順に処理
    while (current != NULL) {
        Atom atom = current->atom;
        char element[3] = {'\0', '\0', '\0'};

        // 元素情報を取得
        if (strncmp(atom.element, "  ", 2) != 0) {
            // element フィールドがあるとき
            strncpy(element, atom.element, 2);
        } else {
            // element フィールドが空の時、atomName の最初の2文字を使用
            strncpy(element, atom.atomName, 2);
        }
        // デバッグ: elementの内容を確認
        printf("Element: '%s'\n", element);  // 各元素が正しく取得されているか確認

	// 元素の種類を判定してカウント
        if (strncmp(element, " C", 2) == 0) { // 2文字比較
            pdb->elementCount[0]++;
        } else if (strncmp(&element[0], " H", 2) == 0) {
            pdb->elementCount[1]++;
        } else if (strncmp(&element[0], " N", 2) == 0) {
            pdb->elementCount[2]++;
        } else if (strncmp(&element[0], " O", 2) == 0) {
            pdb->elementCount[3]++;
        } else if (strncmp(&element[0], " P", 2) == 0) {
            pdb->elementCount[4]++;
        } else {
            pdb->elementCount[5]++; // その他の元素はXとして扱う
        }

        // 次の原子に進む
        current = current->nextAtom;
    }

    // 最も多い元素の数を求める
    int maxCount = 0;
    for (int i = 0; i < 6; i++) {
        if (pdb->elementCount[i] > maxCount) {
            maxCount = pdb->elementCount[i];
        }
    }

    return maxCount; // 最も多い元素の数を返す
}

