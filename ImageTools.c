//=====================================================================//
//                                                                     //
//  ファイル名 : ImageTools.c                                          //
//  内      容 : PGM (Portable GrayMap)形式のデータにプリミティブな    //
//               図形を描くため関数の定義                              //
//  更  新  日 : 2004. 2. 12 木村 彰徳 (Computer Graphics Lab.)        //
//                                                                     //
//=====================================================================//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ImageTools.h"

#include "ImageFileIO.h"

//-----------------------------------------------------------------------//
// void DrawStraightLine(int * piImageData,                              //
//                       int iWidth, int iHeight, int iMaxValue,         //
//                       int iStartX, int iStartY, int iEndX, int iEndY, //
//                       int iSTYLE, int iBW)                             //
//  内      容 : PGM形式のデータに直線を引く                             //
//  更  新  日 : 2004. 2. 12 木村 彰徳 (Computer Graphics Lab.)          //
//                                                                       //
// [引数]                                                                //
// piImageData :（入力）直線を描くのPGM形式のデータ                      //
// iWidth      :（入力）直線を描くのPGM形式のデータの幅（画素数）        //
// iHeight     :（入力）直線を描くのPGM形式のデータの高さ（画素数）      //
// iMaxValue   :（入力）直線を描くのPGM形式のデータの画素の最大値        //
// iStartX     :（入力）直線の始点の X 座標                              //
// iStartY     :（入力）直線の始点の Y 座標                              //
// iEndX       :（入力）直線の終点の X 座標                              //
// iEndY       :（入力）直線の終点の Y 座標                              //
// iSTYLE     :（入力）直線の色. SOLID，DASHED または DOTTED  (ただし未実装）
// iBW         :（入力）直線の色，BLACKLINE または WHITELINE             //
//-----------------------------------------------------------------------//
void DrawStraightLine(int * piImageData,
		      int iWidth, int iHeight, int iMaxValue,
		      int iStartX, int iStartY, int iEndX, int iEndY,
		      int iSTYLE, int iBW) {

    int iIndex;                         // インデックス
    float w, h;                         // 座標ループカウンタ
    const float fStep = 0.5;            // 直線を描くステップ
    const int iBLACK = 0;               // 黒
    const int iWHITE = iMaxValue;       // 白
    int iXmin, iXmax, iYmin, iYmax;     // 座標

    float fx(float x) {
	float y = (iEndY - iStartY)*(x - iStartX)/(iEndX - iStartX) + iStartY;
	return y;
    }
    float fy(float y) {
	float x = (iEndX - iStartX)*(y - iStartY)/(iEndY - iStartY) + iStartX;
	return x;
    }

    // 直線の描画

    // |tanθ| < 1 または iStartY == iEndY
    if(abs(iEndY - iStartY) < abs(iEndX - iStartX) || iStartY == iEndY) {

        if(iStartX > iEndX) {
            iXmin = iEndX;
            iXmax = iStartX;
        } else {
            iXmin = iStartX;
            iXmax = iEndX;
        }
 
	for(w = iXmin; w < iXmax; w+=fStep) {
	    h = fx(w);
	    if(h >= 0 && h < iHeight) {
	        GetIndexFromAxis(iWidth, (int)w, (int)h, &iIndex);
		if(iBW == BLACKLINE) {  // 黒
		    piImageData[iIndex] = iBLACK;
		} else {                // 白
		    piImageData[iIndex] = iWHITE;
		}
            }
        }

    // |tanθ| >= 1 または iStartX == iEndX
    } else {

        if(iStartY > iEndY) {
            iYmin = iEndY;
            iYmax = iStartY;
        } else {
            iYmin = iStartY;
            iYmax = iEndY;
        }
	
	for(h = iYmin; h < iYmax; h+=fStep) {
	    w = fy(h);
	    if(w >= 0 && w < iWidth) {
		GetIndexFromAxis(iWidth, (int)w, (int)h, &iIndex);
		if(iBW == BLACKLINE) {  // 黒
		    piImageData[iIndex] = iBLACK;
		} else {                // 白
		    piImageData[iIndex] = iWHITE;
		}
	    }
	}
    }
    
}

