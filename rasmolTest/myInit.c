#include <math.h>
#include "./myTest.h"
#include "./myGLUT.h"

void
myInit(void)
{
	//myLightSet();
	
	glShadeModel(GL_SMOOTH); 
		/* シェーディングモデルを設定する： 
			GL_FLAT(フラットシェーディング) 
				or 
			GL_SMOOTH(スムーズシェーディング・グローシェーディング)
		*/
	glDepthFunc(GL_LEQUAL);
		/*  デプスを計算するための比較関数の定義
			GL_LEQUAL: Less than or equal	
		*/
	glEnable(GL_DEPTH_TEST); 
		/*  デプステストを有効にする。 */


	//glEnable(GL_CULL_FACE);     	// カリングを有効にする	
	//glEnable(GL_CW);             	// 時計回りに変更 
	//glEnable(GL_BACK);			// 裏側をカリング 

	glClearColor(0.2,0.2,0.2,0.0);
		/* 背景色の設定　*/

}

