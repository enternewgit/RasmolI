#include<math.h>
#include "./myGLUT.h"

// マウスイベントのコールバック関数間でやりとりするための変数
// ファイルに関する静的変数なので、このファイルの中だけで有効
static int startx = 0;
static int starty = 0;
static int endx = 0;
static int endy = 0;
static int pressedButton = -1;

void
myMouse(int button, int state, int x, int y)
{
#ifdef MOUSE_FUNCTION
	switch(state) {
		case  GLUT_DOWN: {  // マウスボタンが押された
			pressedButton = button;
			startx = x;
			starty = y;
			switch(button) {
				case GLUT_LEFT_BUTTON: {
					myCameraRotateY(1.0/M_PI);
					break;
				}	
				case GLUT_MIDDLE_BUTTON: {
					myCameraRotateX(1.0/M_PI);
					break;
				}	
				case GLUT_RIGHT_BUTTON: {
					myCameraRotateZ(1.0/M_PI);
					break;
				}	
			}
			break;
		}
		case GLUT_UP: { // マウスボタンが離された
			endx = x;
			endy = y;
			pressedButton = -1;
			switch(button) {
				case GLUT_LEFT_BUTTON: {
					break;
				}	
				case GLUT_MIDDLE_BUTTON: {
					break;
				}	
				case GLUT_RIGHT_BUTTON: {
					break;
				}	
			}
			break;
		}
	}	
#endif	
	// 再描画イベント
	glutPostRedisplay();
}


void
myMouseMotion(int x, int y)
{
#ifdef MOTION_FUNCTION
	int delx, dely;

	delx = x - startx;
	dely = y - starty; // デバイス座標系のy軸の関係

	switch(pressedButton) {
		case GLUT_MIDDLE_BUTTON: {		
			//myCameraTranslateX(delx/5.0);	
			startx =  x;
			starty =  y;
			break;
		}
		case GLUT_RIGHT_BUTTON: {		
			//myCameraRotateY(delx/M_PI/20);	
			//myCameraRotateX(dely/M_PI/20);	
			startx =  x;
			starty =  y;
			break;
		}
	}
#endif
	// 再描画イベント
	glutPostRedisplay();
}


void
myMousePassiveMotion(int x, int y)
{
#ifdef PASSIVEMOTION_FUNCTION
#endif
	// 再描画イベント
	glutPostRedisplay();
}


