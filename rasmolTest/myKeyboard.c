#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./myGLUT.h"

// キーボードイベントに関するマウスの位置
static int keyx = 0;
static int keyy = 0;

void
myKeyboard(unsigned char key,  /* キーボードから打ち込まれた文字 */
		int x,         /* キーボードが打ち込まれたときのマウスの位置 */ 
		int y)
	
{
#ifdef KEYBOARD_FUNCTION 
	keyx = x;
	keyy = y;	
	myKeyboard0(key, x, y);
#endif	
	/*
	 再描画イベントを起こすための関数
		glutDisplayFuncで登録された関数がコールバックされる
	*/
	glutPostRedisplay();	
}


void
myKeyboard0(unsigned char key,  /* キーボードから打ち込まれた文字 */
		int x,          /* キーボードが打ち込まれたときのマウスの位置 */ 
		int y)
	
{
	switch(key) {
		case 'q': {
			exit(EXIT_FAILURE);
			break;
		}
		case 'x': {
			myCameraRotateX(1.0/M_PI);
			operationModeSet(xrotation);			
			break;
		}
		case 'y': {
			myCameraRotateY(1.0/M_PI);
			operationModeSet(yrotation);			
			break;
		}
		case 'z': {
			myCameraRotateZ(1.0/M_PI);
			operationModeSet(zrotation);			
			break;
		}
		default: { /* 定義されていないキーが入力された時には、何もしない。 */
			break;
		}
	}	

}

void
myKeyUp(unsigned char key, int x, int y)
{
    fprintf(stdout, "key Up start\n");
}

void
mySpecialUp(int key, int x, int y)
{
    fprintf(stdout, "special key Up start\n");
}

void
mySpecial(int key, int x, int y)
{
    fprintf(stdout, "special_key() start\n");
    switch( key ) {
        case GLUT_KEY_LEFT: // 左キー
            fprintf(stdout, "Left DOWN\n");
            break;
        case GLUT_KEY_RIGHT: // 右キー
            fprintf(stdout, "Right DOWN\n");
            break;
        default: {
            fprintf(stdout, "Other special key DOWN\n");
            break;
        }
    }
    fprintf(stdout, "at %d %d\n", x, y);
    glutPostRedisplay();
}
