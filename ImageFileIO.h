//=====================================================================//
//                                                                     //
//  ファイル名 : ImageFileIO.h                                         //
//  内      容 : ppm (Portable PixMap), pgm (Portable GrayMap)ファイル //
//               から入力データの読み込みおよび出力データを書き出しを  //
//               行う．                                                //
//  更  新  日 : 2004. 2. 11 木村 彰徳 (Computer Graphics Lab.)        //
//               2003. 3. 21 駒井 教平 (Computer Vision & Games Lab.)  //
//                                                                     //
//=====================================================================//
#ifndef _IMAGEFILEIO_H_
#define _IMAGEFILEIO_H_ 1

// 構造体 RGB型
struct RGB {
    int iRed;
    int iGreen;
    int iBlue;
};

// RGB パラメータ
#define RED   0
#define GREEN 1
#define BLUE  2

//---------------------------------------------------------------------//
// void GetAxisFromIndex(int iWidth, int iIndex, int * iX, int * iY)   //
// 内      容 : １次元のインデックスから２次元座標を取得               //
// 更  新  日 : 2004. 2. 15 木村 彰徳 (Computer Graphics Lab.)         //
//                                                                     //
// [引数]                                                              //
// iWidth       : （入力）画像の幅（画素数）                           //
// iX           : （入力）横方向の座標（画素数）                       //
// iY           : （入力）縦方向の座標（画素数）                       //
// iIndex       : （出力）インデックス                                 //
//---------------------------------------------------------------------//
void GetAxisFromIndex(int iWidth, int iIndex, int * iX, int * iY);

//---------------------------------------------------------------------//
// void GetIndexFromAxis(int iWidth, int iX, int iY, int * iIndex)     //
// 内      容 : ２次元座標から１次元のインデックスを取得               //
// 更  新  日 : 2004. 2. 15 木村 彰徳 (Computer Graphics Lab.)         //
//                                                                     //
// [引数]                                                              //
// iWidth       : （入力）画像の幅（画素数）                           //
// iIndex       : （入力）インデックス                                 //
// iX           : （出力）横方向の座標（画素数）                       //
// iY           : （出力）縦方向の座標（画素数）                       //
//---------------------------------------------------------------------//
void GetIndexFromAxis(int iWidth, int iX, int iY, int * iIndex);

//---------------------------------------------------------------------//
// struct RGB * ReadPpm(int * iWidth, int * iHeight, int * iMaxValue)  //
// 内      容 : PPMファイルの読み込み                                  //
// 更  新  日 : 2004. 2. 15 木村 彰徳 (Computer Graphics Lab.)         //
//                                                                     //
// [戻り値]                                                            //
//              : ２次元([画素数][RGB])のPPM形式のデータ               //
//                画素数=iWidth * iHeight                              //
// [引数]                                                              //
// iWidth       : 画像の幅（画素数）                                   //
// iHeight      : 画像の高さ（画素数）                                 //
// iMaxValue    : 画像の各画素のRGBの最大値                            //
//---------------------------------------------------------------------//
struct RGB * ReadPpm(int * iWidth, int * iHeight, int * iMaxValue);

//--------------------------------------------------------------------//
// void FreePpm(struct RGB * pRGBOutputData)                          //
// 内      容 : PPM形式の画像データを保存しているメモリ領域の開放     //
// 更  新  日 : 2004. 2. 15 木村 彰徳 (Computer Graphics Lab.)        //
//                                                                    //
// [引数]                                                             //
// pRGBOutputData : ２次元([画素数][RGB])のPPM形式のデータ            //
//--------------------------------------------------------------------//
void FreePpm(struct RGB * pRGBOutputData);

//--------------------------------------------------------------------//
// void WritePpm(struct RGB * pRGBOutputData, int iWidth,             //
//               int iHeight, int iMaxValue)                          //
// 内      容 : PPMファイルへ書き出し                                 //
// 更  新  日 : 2004. 2. 15 木村 彰徳 (Computer Graphics Lab.)        //
//                                                                    //
// [引数]                                                             //
// piRGBOutputData : ２次元([画素数][RGB])のPPM形式のデータ           //
//                画素数=iWidth * iHeight                             //
// iWidth       : 画像の幅（画素数）                                  //
// iHeight      : 画像の高さ（画素数）                                //
// iMaxValue    : 画像の各画素のRGBの最大値                           //
//--------------------------------------------------------------------//
void WritePpm(struct RGB * pRGBOutputData, int iWidth, int iHeight, int iMaxValue);

//--------------------------------------------------------------------//
// int * ReadPgm(int * iWidth, int * iHeight, int * iMaxValue)　　    //
// 内      容 : PGMファイルの読み込み                                 //
// 更  新  日 : 2004. 2. 15 木村 彰徳 (Computer Graphics Lab.)        //
//                                                                    //
// [戻り値]                                                           //
//              : １次元([画素数])のPGM形式のデータ                   //
//                画素数=iWidth * iHeight                             //
// [引数]                                                             //
// iWidth       : 画像の幅（画素数）                                  //
// iHeight      : 画像の高さ（画素数）                                //
// iMaxValue    : 画像の画素値の最大値                                //
//--------------------------------------------------------------------//
int * ReadPgm(int * iWidth, int * iHeight, int * iMaxValue);

//---------------------------------------------------------------------//
// void FreePgm(int * piOutputData)                                    //
// 内      容 : PGM形式の画像データを保存しているメモリ領域の開放      //
// 更  新  日 : 2004. 2. 15 木村 彰徳 (Computer Graphics Lab.)         //
//                                                                     //
// [引数]                                                              //
// piOutputData : ２次元([画素数][RGB])のPGM形式のデータ               //
//---------------------------------------------------------------------//
void FreePgm(int * piOutputData);

//---------------------------------------------------------------------//
// void WritePgm(int * piOutputData, int iWidth,                       //
//               int iHeight, int iMaxValue)                           //
// 内      容 : PGMファイルへ書き出し                                  //
// 更  新  日 : 2004. 2. 15 木村 彰徳 (Computer Graphics Lab.)         //
//                                                                     //
// [引数]                                                              //
// piInputData  : １次元([画素数])のPGM形式のデータ                    //
//                画素数=iWidth * iHeight                              //
// iWidth       : 画像の幅（画素数）                                   //
// iHeight      : 画像の高さ（画素数）                                 //
// iMaxValue    : 画像の画素値の最大値                                 //
//---------------------------------------------------------------------//
void WritePgm(int * piOutputData, int iWidth, int iHeight, int iMaxValue);

//---------------------------------------------------------------------//
// void WritePgm(int * piOutputData, int iWidth,                       //
//               int iHeight, int iResolution)                         //
// 内      容 : PGMファイルへ書き出し                                  //
// 更  新  日 : 2004. 2. 15 木村 彰徳 (Computer Graphics Lab.)         //
//                                                                     //
// [引数]                                                              //
// piInputData  : １次元([画素数])のPGM形式のデータ                    //
//                画素数=iWidth * iHeight                              //
// iWidth       : 画像の幅（画素数）                                   //
// iHeight      : 画像の高さ（画素数）                                 //
// iResolution  : 画像の解像度                                         //
//---------------------------------------------------------------------//
void WritePgm(int * piOutputData, int iWidth, int iHeight, int iResolution);

#endif
