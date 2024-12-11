//=====================================================================//
//                                                                     //
//  ファイル名 : ImageTools.h                                          //
//  内      容 : PGM (Portable GrayMap)形式のデータにプリミティブな    //
//               図形を描くため関数の定義                              //
//  更  新  日 : 2004. 2. 12 木村 彰徳 (Computer Graphics Lab.)        //
//                                                                     //
//=====================================================================//
#ifndef _IMAGETOOLS_H_
#define _IMAGETOOLS_H_

//-----------------------------------------------------------------------//
// void DrawStraightLine(int * piImageData,                              //
//                       int iWidth, int iHeight, int iMaxValue,         //
//                       int iStartX, int iStartY, int iEndX, int iEndY, //
//                       int STYLE, int iBW)                             //
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
// iSTYLE      :（入力）直線の色，SOLID，DASHED または DOTTED            //
// iBW         :（入力）直線の色，BLACKLINE または WHITELINE             //
//-----------------------------------------------------------------------//
enum lineStype {SOLID, DASHED, DOTTED};
enum lineBW {BLACKLINE, WHITELINE};
void DrawStraightLine(int * piImageData,
		      int iWidth, int iHeight, int iMaxValue,
		      int iStartX, int iStartY, int iEndX, int iEndY,
		      int iSTYLE, int iBW);

//-----------------------------------------------------------------------//
// void Histogram1D(int * piHistData, int iNumHistData,                  //
//                  int iNumBin, int iMinBin, int iMaxBin, int iGRID)    //
//                                                                       //
//  内  容 : １次元ヒストグラム                                          //
//  更新日 : 2004. 2. 13 木村 彰徳 (Computer Graphics Lab.)              //
//                                                                       //
// [引数]                                                                //
// piHistData   :（入力）ヒストグラミングするデータ                      //
// iNumHistData :（入力）ヒストグラミングするデータ数                    //
// iNumBin      :（入力）ビン数                                          //
// iMinBin      :（入力）ビンの最小値                                    //
// iMaxBin      :（入力）ビンの最大値                                    //
// iGRID         :（入力）グリッドの有無 (GRID, NOGRID, XGRID, YGRID)    //
//-----------------------------------------------------------------------//
#define NOGRID 0
#define GRID   1
#define XGRID  2
#define YGRID  3
void Histogram1D(int * piHistData, int iNumHistData,
		 int iNumBin, int iMinBin, int iMaxBin, int iGRID);


#endif
