#ifndef PDB_H
#define PDB_H

#include <stdio.h>
#include <stdlib.h>
#include "./myGLUT.h"

typedef struct Atom Atom;
struct Atom
{
    float x;          // X座標
    float y;          // Y座標
    float z;          // Z座標
    char resName[4];  // 残基名
    int resNumber;    // 残基番号
    float tempFactor; // 温度因子を格納
    float occupancy;  // 占有度を格納
    char atomName[5]; // 原子名
    char element[3];  // 元素番号
};

typedef struct Line Line;
struct Line
{
    Atom start;
    Atom end;
};

typedef struct arrayPDB arrayPDB;
struct arrayPDB
{
    int numAtom;
    int numCAAtom;
    Atom *CA;
};

typedef struct recordPDB recordPDB;
struct recordPDB
{
    Atom atom;           /* 原子の座標 */
    recordPDB *nextAtom; /* 次の ATOM へのポインタ */
    recordPDB *nextCA;   /* 次の CA へのポインタ */
};

typedef struct PDB PDB;
struct PDB
{
    int numAtom;          // 原子の個数
    int numCA;            // CAの個数
    recordPDB *top;       // 先頭の原子
    recordPDB *topCA;     // 先頭の CA
    recordPDB *current;   // 現在の原子
    recordPDB *currentCA; // 現在の CA 原子
    Atom Center;          // 分子中心の座標を挿入
    float maxRadius;      // 中心から最も遠い原子までの距離を格納
    Atom min;             // x,y,zのうち、それぞれの座標の最小値
    Atom max;             // x,y,zのうち、それぞれの座標の最大値
    int resCount[21];     // 残基数を格納（三文字表記）
    int elementCount[6];  // 元素数を格納（元素名のアルファベット順)
};

extern void psStart(FILE *fpt);
extern void psEnd(FILE *fpt);
extern void lineDraw(FILE *fpt, float startx, float starty, float endx, float endy);
extern void lineDraw2(FILE *fpt, Line l);
extern int arrayPDBRead(FILE *fpt, arrayPDB *pdb);
extern void lineCADraw(FILE *fpt, arrayPDB pdb);
extern int pdbRead(FILE *fpt, PDB *pdb);
extern void lineCADraw2(FILE *fpt, PDB *pdb);
extern void lpdbCenterCalc(PDB *pdb);
extern void lpdbSizeCalc(PDB *pdb);
extern void lpdbMinCalc(PDB *pdb);
extern void lpdbMaxCalc(PDB *pdb);
extern void lpdbInfoPrint(FILE *fpt, PDB *pdb, int mode);
extern int lpdbResCount(PDB *pdb);
extern int lpdbElementCount(PDB *pdb);
extern void lpdbFree(PDB *pdb);

#define WIN_WIDTH  (400)
#define WIN_HEIGHT (400)
#define WIN_POSX   (100)
#define WIN_POSY   (100)
#define WIN_NAME   "myTest"
#endif // PDB_H
