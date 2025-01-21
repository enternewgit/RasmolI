#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./myGLUT.h"

#define POINTNUM (6)

static GLuint    displayList1          = 1;
static GLuint    displayList2          = 2;
static GLboolean needDisplayListMaking = GL_TRUE;

static Coord __points[POINTNUM] = {
{ -1,  0,  0}, 
{  1,  0,  0}, 
{  1,  2,  0}, 
{  0, -2,  0}, 
{  0, -2,  3},
{  0,  0,  -3}};


static GLfloat materialColor[4];
static GLfloat materialSpecular[4] = {0.2, 0.2, 0.2, 1.0 } ;
static GLfloat materialAmbient[4] = {0.1, 0.1, 0.1, 1.0 } ;

/*
	色の設定のための関数: indexがminからmaxに変化するにつれて、赤から青に変化する。
	青から赤に変化させるためには、プログラムの変更が必要である
	もしくは、
	index/max/minの使い方の工夫が必要である
*/
void
__getColorRGB(GLfloat color[3], GLdouble index, GLdouble min, GLdouble max)
{
	GLdouble half = (max+min)/2.0;

	if(index<half) {
		color[0] = (half  - index)/(half-min);
		color[1] = (index - min  )/(half-min);
		color[2] = 0;
	} else {
		color[0] = 0;
		color[1] = (max   - index)/(max - half);
		color[2] = (index - half )/(max - half);
	}
}

/*
	多数のプリミティブの集合をひとつの命令で実行できるようにする。
	高速化のために必須。	
*/

void
myDisplayListMake1(void)
{
	int i;
	GLfloat color[3]; 		/* 使用する色の指定 */
	GLdouble radius=0.5;	        /* 作成する球面の半径 */	
	GLint    slices=10;             /* 球面を分割するためのパラメータ */
	GLint    stacks=10;

	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular); /* 物質の鏡面反射の色の設定 */
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);     /* 物質の拡散光の色の設定  */
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);             /* 物質の鏡面指数 */
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);   /* 物質の環境光の色の設定 */
	materialColor[3] = 1.0;

	glNewList(displayList1, GL_COMPILE);
		for(i=0; i<POINTNUM; i++) {
			/* 色の設定 */
			__getColorRGB(color, i, 0, POINTNUM-1);
			glColor3f(color[0], color[1], color[2]);              /* 照明がないときのための色 */
			materialColor[0] = color[0];	materialColor[1] = color[1];	materialColor[2] = color[2];	
			materialColor[3] = 1.0;
			glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular); /* 物質の鏡面反射の色の設定 */
			glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);     /* 物質の拡散光の色の設定  */
			glMaterialf(GL_FRONT, GL_SHININESS, 10.0);             /* 物質の鏡面指数 */
			glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);   /* 物質の環境光の色の設定 */
	
			/* 球面の創出 */
			glPushMatrix();
				//glScalef (1.0, 1.0, 1.0);                /* x, y, z軸に沿って、拡大縮小 */ 
				//glRotatef(0.0, 0.0, 0.0, 1.0);           /* z軸の回りに回転 */
				glTranslatef(__points[i].x, __points[i].y, __points[i].z); /* 移動 */
				glutSolidSphere(radius, slices, stacks); 
				/* 位置(0,0,0)に半径radiusで球面を作成。刻幅slices/stacks 
					その後、上記のMatrixを使って、変換する。
				*/
			glPopMatrix();
		}
	glEndList();
}

void
myDisplayListMake2(void)
{
	int i;
	GLfloat color[3]; /* 使用する色の指定 */

	materialColor[3] = 1.0;

	glNewList(displayList2, GL_COMPILE);

	glPushMatrix();
	glBegin(GL_LINE_STRIP);
		/*  プリミティブ(初歩的な図形) を描き始める。
			GL_POINTS		個々の独立した点
			GL_LINES		個々の独立した線
			GL_POLYGON		単純な凸多角形の境界線
			GL_TRIANGLES 		個々の独立した三角形
			GL_QUADS		個々の独立した四角形
			GL_LINE_STRIP 		連結した線分
			GL_LINE_LOOP		GL_LINE_STRIP + 最初と最後の点を閉じる
			GL_TRIANGLE_STRIP	連結した三角形
			GL_TRIANGLE_FAN		扇型に連結した三角形
			GL_QUAD_STRIP		連結した四角形
		*/
		i = 0;
		// 色の設定
		__getColorRGB(color, i, 0, POINTNUM-1);
		glColor3f(color[0], color[1], color[2]); /* 照明を考えないときの色 */	
		// 頂点の設定
		glVertex3f(__points[i].x, __points[i].y, __points[i].z);
		for(i=1; i<POINTNUM-1; i++) {
			__getColorRGB(color, i-0.5, 0, POINTNUM-1); 
			glColor3f(color[0], color[1], color[2]);	
			glVertex3f((__points[i].x + __points[i-1].x)/2.0,
				   (__points[i].y + __points[i-1].y)/2.0,
				   (__points[i].z + __points[i-1].z)/2.0);

			__getColorRGB(color, i, 0, POINTNUM-1);
			glColor3f(color[0], color[1], color[2]);	
			glVertex3f(__points[i].x,
				   __points[i].y,
				   __points[i].z);
		}
		__getColorRGB(color, i, 0, POINTNUM-1);
		glColor3f(color[0], color[1], color[2]);	
		glVertex3f((__points[i].x + __points[i-1].x)/2.0,
			   (__points[i].y + __points[i-1].y)/2.0,
			   (__points[i].z + __points[i-1].z)/2.0);
		glVertex3f(__points[i].x,
			   __points[i].y,
			   __points[i].z);

	glEnd();
	glPopMatrix();
	glEndList();

}

void 
myDisplayListMake(void)
{
	myDisplayListMake1();
	myDisplayListMake2();
	needDisplayListMaking = GL_FALSE;
}

/*
	Displayコールバックにより呼び出される関数。
	実際にDisplayを行う。	
*/
void
myDisplay(void)
{
	cameraInfo* camera;

	/* カメラ位置の設定 */
	camera = getMyCamera();
   	glMatrixMode(GL_PROJECTION);              /* 内部で取り扱う行列のモードの切替え: 
                            GL_PROJECTION : 射影変換行列  
                            GL_MODELVIEW  : モデルビュー行列  */  
    glLoadIdentity();                         /* 単位行列の読み込み */  
	myLightSet();

	//　カメラの視線の指定
    gluPerspective(camera->Fovy, camera->Aspect, camera->ClipNear, camera->ClipFar);   
    gluLookAt(camera->Eye[0], camera->Eye[1], camera->Eye[2],
     		camera->Centre[0], camera->Centre[1], camera->Centre[2],
     		camera->Up[0], camera->Up[1], camera->Up[2]);
	//myLightSet();

	/* GLUを使った視線 
		対象を眺めるカメラ(目)の位置     : eyex, eyey, eyez	
		シーンの中心となる注視点   : centrex, cetrey, centrez 
		シーンの上方を表すベクトル : upx, upy, upz
	*/
    /* GLUを使った透視変換: 
       		y-z平面における視界の角度 : 0<Fovy<180.0
        	アスペクト比: Aspect = 視界幅/視界高
            クリップ面と視点の距離: ClipNear(>0), ClipFar(>0)
    */  
    // 正射影変換の場合
    // 正射影変換の定義: left, right, bottom, top, near, far */
	/* glOrtho(-length*tan(camera->Fovy/180/2.0*M_PI)*camera->Aspect,
        +length*tan(camera->Fovy/180/2.0*M_PI)*camera->Aspect,
        -length*tan(camera->Fovy/180/2.0*M_PI),
        +length*tan(camera->Fovy/180/2.0*M_PI),
        camera->ClipNear, camera->ClipFar);    */
	//
    // 透視変換の場合
    // glFrustum(-1.0, 1.0, -1.0, 1.0, 0.5, 1.0);   /* 透視変換の定義 left, right, bottom, top, near(>0), far(>0) */
    //       あるいは
    // gluPerspective(camera->Fovy, camera->Aspect, camera->ClipNear, camera->ClipFar);   
    /* GLUを使った透視変換: 
    	y-z平面における視界の角度 : 0<Fovy<180.0
        アスペクト比: Aspect = 視界幅/視界高
        クリップ面と視点の距離: ClipNear(>0), ClipFar(>0)
    */  

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();                         /* 単位行列の読み込み */  
	//myLightSet();

	// バッファ領域のクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 高速化のためにディスプレイリストを使用する。
	if(GL_TRUE == needDisplayListMaking) {
		myDisplayListMake();
	}
	glPushMatrix();

	glPushMatrix();
		//myLightSet();
		glCallList(displayList1); /* ディスプレイリスト1を取り出す */
	glPopMatrix();

	glPushMatrix();
		glDisable(GL_LIGHTING);
		glCallList(displayList2); /* ディスプレイリスト2を取り出す */
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); // ティーポットを描く
		glTranslatef(1, 1, 1); 
		//myLightSet();
		glutSolidTeapot(1.0);
		/* 移動 */
	glPopMatrix();

	glutSwapBuffers();
}

