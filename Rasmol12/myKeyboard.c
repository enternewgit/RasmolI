#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./myGLUT.h"

// キーボードイベントに関するマウスの位置
static int keyx = 0;
static int keyy = 0;
static int animationFlag = 0;  // アニメーションのON/OFF状態
static int displayFlag = 1;	   // 表示モード（1または2）
static int projectionMode = 0; // 0: 透視投影, 1: 平行投影（display関数の実装後に変更）
static int shadingMode = 0;	   // 0: スムーズシェーディング, 1: フラットシェーディングdisplay関数の実装後に変更）


void myKeyboard(unsigned char key, /* キーボードから打ち込まれた文字 */
				int x,			   /* キーボードが打ち込まれたときのマウスの位置 */
				int y)

{
#ifdef KEYBOARD_FUNCTION
	keyx = x;
	keyy = y;
	key(key, x, y);
#endif
	/*
	 再描画イベントを起こすための関数
		glutDisplayFuncで登録された関数がコールバックされる
	*/
	glutPostRedisplay();
}

void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	{ // qが押された場合、終了
		exit(EXIT_FAILURE);
		break;
	}
	case 'Q':
	{ // Qが押された場合、終了
		exit(EXIT_FAILURE);
		break;
	}
	case 's':
	{ // アニメーション：停止とロッキングの切替
		animationFlag = 1 - animationFlag;
		break;
	}
	case '1':
	{					 // 原子を球で表示
		displayFlag = 1; // 1に設定
		break;
	}
	case '2':
	{					 // α炭素を線で結んだ表示
		displayFlag = 2; // 2に設定
		break;
	}
	case 'p':
	{ // 投影方法の切り替え
		// ここで投影方法を切り替える関数に変更（display関数の実装後に変更）
		projectionMode = 1 - projectionMode; // トグルスイッチ
		break;
	}
	case 'S':
	{ // スムーズ／フラットシェーディングを切り替え
		// ここでシェーディングモードを切り替える関数を呼び出す（display関数の実装後に変更）
		shadingMode = 1 - shadingMode; // トグルスイッチ
		break;
	}
	case 'x':
	{ // x軸を中心に回転
		myCameraRotateX(1.0 / M_PI);
		operationModeSet(xrotation);
		break;
	}
	case 'y':
	{ // y軸を中心に回転
		myCameraRotateY(1.0 / M_PI);
		operationModeSet(yrotation);
		break;
	}
	case 'z':
	{ // z軸を中心に回転
		myCameraRotateZ(1.0 / M_PI);
		operationModeSet(zrotation);
		break;
	}
	case 'c':
	{					 // アミノ酸毎に⾊を変えて表示 (色の選択)
		displayFlag = 3; // 3に設定（display関数の実装後に変更）
		break;
	}
	case 'h':
	{ // キーボード操作説明
		printf("＊キーボードの操作説明＊\n");
		printf("'q'or'Q':終了\n");
		printf("'s':アニメーション-停止とロッキングの切替\n");
		printf("'1':すべての原子を球で表示\n");
		printf("'2':α炭素を線で結んだ表示\n");
		printf("'p':投影方法-を透視投影と平⾏投影を切替\n");
		printf("'S':投影方法-スムーズ／フラットシェーディングの切替\n");
		printf("'x':x軸を中心に回転\n");
		printf("'y':y軸を中心に回転\n");
		printf("'z':z軸を中心に回転\n");
		printf("'c':それぞれのアミノ酸の色を変更\n");
		break;
	}
	default:
	{ // 定義されていないキーが入力された時(なにもしない)
		fprintf(stderr, "Unknown key: %c\n", key);
		break;
	}
	}
	glutPostRedisplay(); // 画面の再描画を要求
}

void myKeyUp(unsigned char key, int x, int y)
{
	fprintf(stdout, "key Up start\n");
}

void mySpecialUp(int key, int x, int y)
{
	fprintf(stdout, "special key Up start\n");
}

void mySpecial(int key, int x, int y)
{
	fprintf(stdout, "special_key() start\n");
	switch (key)
	{
	case GLUT_KEY_LEFT: // 左キー
		fprintf(stdout, "Left DOWN\n");
		break;
	case GLUT_KEY_RIGHT: // 右キー
		fprintf(stdout, "Right DOWN\n");
		break;
	default:
	{
		fprintf(stdout, "Other special key DOWN\n");
		break;
	}
	}
	fprintf(stdout, "at %d %d\n", x, y);
	glutPostRedisplay();
}
