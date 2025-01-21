#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include "./myGLUT.h"

// マウスイベントのコールバック関数間でやりとりするための変数
// ファイルに関する静的変数なので、このファイルの中だけで有効
static int startx = 0;
static int starty = 0;
static int drag_mouse_l = 0;   // 左ボタンを押下中かどうか（0:非ドラッグ,1:ドラッグ）(カメラの回転)
static int drag_mouse_m = 0;   // 中ボタンを押下中かどうか（0:非ドラッグ,1:ドラッグ）(平行移動)
static int drag_mouse_ls = 0;  // 左ボタン+シフトボタンを押下中かどうか（0:非ドラッグ,1:ドラッグ）(ズーム)
static int drag_mouse_rs = 0;  // 右ボタン+シフトボタンを押下中かどうか（0:非ドラッグ,1:ドラッグ）(Z軸回転)
static int pressedButton = -1; // 現在押されているボタンを記録
cameraInfo *camera;

static int endx = 0;
static int endy = 0;

void myMouse(int button, int state, int x, int y)
{
// マウスボタンが押されたり離されたりしたときに呼び出される関数
#ifdef MOUSE_FUNCTION

	// Shiftキーが押されているかどうかを確認
	int isShiftKeyPressed = glutGetModifiers() & GLUT_ACTIVE_SHIFT;

	switch (state)
	{
	case GLUT_DOWN: // マウスボタンが押された場合
		pressedButton = button;
		startx = x;
		starty = y;
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			if (isShiftKeyPressed)
			{
				drag_mouse_ls = 1; // Shift+左ボタンが押された
			}
			else
			{
				drag_mouse_l = 1; // 左ボタンが押された
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (isShiftKeyPressed)
			{
				drag_mouse_rs = 1; // Shift+右ボタンが押された
			}
			break;
		case GLUT_MIDDLE_BUTTON:
			drag_mouse_m = 1; // 中ボタンが押された
			break;
		}
		break;

	case GLUT_UP: // マウスボタンが離された場合
		endx = x;
		endy = y;
		pressedButton = -1;
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			drag_mouse_ls = 0; // Shift+左ボタンフラグをリセット
			drag_mouse_l = 0;  // 左ボタンフラグをリセット
			break;
		case GLUT_RIGHT_BUTTON:
			drag_mouse_rs = 0; // Shift+右ボタンフラグをリセット
			break;
		case GLUT_MIDDLE_BUTTON:
			drag_mouse_m = 0; // 中ボタンフラグをリセット
			break;
		}
		break;
	}

	// 画面の再描画を要求
	glutPostRedisplay();

#endif
}

void myMouseMotion(int x, int y)
{ // マウスが動いているときに継続的に呼び出される
#ifdef MOTION_FUNCTION
    int delx = x - startx;
    int dely = y - starty;


	switch (pressedButton)
	{
	case GLUT_LEFT_BUTTON:
		if (drag_mouse_l == 1)
		{
			// 左ドラッグ（X,Y回転）
			myCameraRotateY(-delx / M_PI / 20);
			myCameraRotateX(-dely / M_PI / 20);
		}
		else if (drag_mouse_ls == 1)
		{
			// シフト＋左ボタン（ズーム）
			myCameraTranslateZ(dely / 500.0);
		}
		break;

	case GLUT_MIDDLE_BUTTON:
		if (drag_mouse_m == 1)
		{
			// 中ボタンドラッグ（平⾏移動）
			myCameraTranslateX(delx / 20.0);
			myCameraTranslateY(dely / 20.0);
		}
		break;

	case GLUT_RIGHT_BUTTON:
		if (drag_mouse_rs == 1)
		{
			// シフト＋右ドラッグ（Z軸周りの回転）
			myCameraRotateZ(delx / M_PI / 20);
		}
		break;
	}

	startx = x;
	starty = y;

	glutPostRedisplay(); // 再描画イベント
#endif
}
void myMousePassiveMotion(int x, int y)
{
#ifdef PASSIVEMOTION_FUNCTION
#endif
	glutPostRedisplay(); // 再描画イベント
}
