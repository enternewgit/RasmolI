#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include "./PDB.h" //後で作成する
#include "./myGLUT.h" //後で作成する
/*
読み込むファイル名は、起動時に、コマンドの第⼀引数として記述し、main関数内部で、Ｐ
ＤＢのファイルの情報を読み込み、これまで開発してきたPDB型の変数に格納する。
起動⽅法：
$ コマンド名（各グループ設定） ＰＤＢファイル名 
*/
int main(int argc, char* argv[]){
	if (argc !=2){
		printf("引数の数が違います\n");
		return 1;
	}

	FILE *fp;
	PDB pdbStruct;
	PDB *pdb = &pdbStruct; //PDB構造体をスタック上に確保 

	// ファイルを開く
	const char *pdbfilename = argv[1];
    if ((fp = fopen(pdbfilename, "r")) == NULL) {
        fprintf(stderr, "Error: Unable to open file %s\n", pdbfilename);
        return 1;
    }	

    // PDBデータを読み込む
    int numCA = pdbRead(fp, pdb);//pdbRead関数を後で実装
    if (numCA < 0) {
        fprintf(stderr, "Error reading PDB file\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

	/*77~78が元素の種類を示し、18~20までが残基（コドン）*/


// GLUTを用いる上で必須の環境設定  
	/* GLUT Liraryの初期化： GLUTライブラリで使用されるオプション・引数の取り扱い */ 	
	glutInit(&argc, argv); 
	/* GLUTライブラリを使った表示モードの設定 */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
		/* 
		GLUT_SINGLE :  シングルバファモード。GLUT_DOUBLEは、ダブルバッファモード 	
		GLUT_RGBA   :  色の指定はRGBAモード設定する(default)。 GLUT_INDEXは、インデックスモード(上書き)
		GLUT_DEPTH  :  z-bufferモードの指定	
		GLUT_ALPHA  :  アルファバッファを確保する。GLUT_RGBAではアルファバッファは用意されない.
		GLUT_ACCUM  :  アキュミュレーションバッファを確保する。
		GLUT_STENCIL:  ステンシルバッファを確保する。
		GLUT_STEREO :  ステレオウィンドウを確保する。
		*/

	/* 最初に開くウィンドウの大きさを指定 */
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);  
	/* 最初に開くウィンドウの位置を指定 */
	glutInitWindowPosition(WIN_POSX, WIN_POSY); 
	/* ウィンドウを作成する。引数はウィンドウの名前 */
	glutCreateWindow(WIN_NAME);

// このアプリケーション専用の環境設定
	/* このプログラム専用の環境設定: 自作 */
	myInit();

// コールバック関数の登録(registeration)
	glutIdleFunc(myIdle);         /* 何もイベントが起きていないときに呼び出す関数 */
  // キーボードに関係したコールバック関数の登録
	glutKeyboardFunc(myKeyboard); /* キーボードが押されたときに呼び出される関数を指定する。*/
	glutSpecialFunc(mySpecial); /* 特殊キーボードが押されたときに呼び出される関数を指定する。*/
	glutKeyboardUpFunc(myKeyUp); /* キーボードが押されたときに呼び出される関数を指定する。*/
	glutSpecialUpFunc(mySpecialUp); /* 特殊キーボードが押されたときに呼び出される関数を指定する。*/

  // マウスイベントに関係したコールバック関数の登録
	glutMouseFunc(myMouse);       /* マウスが押されたときに呼び出される関数を指定する。*/
	glutMotionFunc(myMouseMotion);/* マウスを押したまま, マウスが移動するときに呼び出される関数を指定する。*/
	glutPassiveMotionFunc(myMousePassiveMotion);  /* マウスが押されていないとき、マウスが移動するときに呼び出される関数を指定する。*/
  // 画面の表示に関係したコールバック関数の登録
	glutDisplayFunc(myDisplay);   /* 絵を書くときに呼び出される関数を指定する。 */
	glutReshapeFunc(myReshape);   /* ウィンドウの大きさなどが変更したときに呼び出される関数(call back function)を指定する。*/

// GLUTによるメインループ
	glutMainLoop();  // 無限ループ： 上記の4つのイベントがおこった時に、指定された関数をコールバックする。 
			 // どの順番でイベントが起きるかを想定できない。
			 // おこったイベントに応じてコールバックされる関数が変わる。
			 // このような制御法を イベント駆動型(event-driven) とよぶ。
	return 0;  /* ここへは一度もやってこない */
}

