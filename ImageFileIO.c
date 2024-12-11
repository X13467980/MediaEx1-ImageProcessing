//=====================================================================//
//                                                                     //
//  ファイル名 : ImageFileIO.c                                         //
//  内      容 : ppm (Portable PixMap), pgm (Portable GrayMap)ファイル //
//               から入力データの読み込みおよび出力データを書き出しを  //
//               行う．                                                //
//  更  新  日 : 2004. 2. 15 木村 彰徳 (Computer Graphics Lab.)        //
//               2003. 3. 21 駒井 教平 (Computer Vision & Games Lab.)  //
//                                                                     //
//=====================================================================//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ImageFileIO.h"

void SkipCommentLine(FILE * fp);

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
void GetAxisFromIndex(int iWidth, int iIndex, int * iX, int * iY) {
    *iX = iIndex%iWidth;
    *iY = iIndex/iWidth;
}

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
void GetIndexFromAxis(int iWidth, int iX, int iY, int * iIndex) {
    *iIndex = iWidth*iY + iX;
}

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
struct RGB * ReadPpm(int * iWidth, int * iHeight, int * iMaxValue) {

    FILE *fp;                    // ファイルポインタ
    enum PPM {P3, P6};           // テキスト形式 or バイナリ形式
    int iPPMType;                // P3 or P6
    char chFileName[80];         // ファイルネーム
    const int MAXCHARS = 100;    // １行の最大文字数
    char chLine[MAXCHARS];       // ファイル形式の認識用変数
    struct RGB * pRGBInputData;  // 入力データを格納する変数
    unsigned char * pucData;     // 入力データを格納する変数
    struct RGB sRGBcolor;        // 輝度値
    int iNumPixels;              // 画素数
    int iIndex;                  // インデックス
    int w, h;                    // ループカウンタ
    
    // ファイル名の入力
    printf("Input INPUT PPM file name[*.ppm]? > ");
    scanf("%s", chFileName);

    // 入力されたファイルのオープン
    // オープンに失敗の場合は、エラー文を出力し、返り値として１を返す．
    if((fp = fopen(chFileName, "r")) == NULL){
        fprintf(stderr, "Cannot open file [%s].\n", chFileName);
        exit(1);
    }

    // ヘッダの読み込み
    fgets(chLine, MAXCHARS, fp);

    // PPM形式(P3)ではない場合、エラー文を出力し、返り値として１を返す
    if (strncmp(chLine, "P3", 2) == 0){
	iPPMType = P3;
    } else if (strncmp(chLine, "P6", 2) == 0){
	iPPMType = P6;
	fclose(fp);
	fp = fopen(chFileName, "rb");
	fgets(chLine, MAXCHARS, fp);
    } else {
	fprintf(stderr, "[%s] is not PPM file.\n", chFileName);
        exit(1);
    }

    // コメント行を読み飛ばす
    SkipCommentLine(fp);

    // 画像データから、画像の幅・高さを読み込む
    fgets(chLine, MAXCHARS, fp);
    sscanf(chLine, "%d %d", iWidth, iHeight);

    // コメント行を読み飛ばす
    SkipCommentLine(fp);

    // 画像データから、解像度を読み込む
    fgets(chLine, MAXCHARS, fp);
    sscanf(chLine, "%d", iMaxValue);
    iNumPixels = (*iWidth)*(*iHeight);

    // 入力画像データのメモリ領域の確保
    // psInputData[iWidth*iHeight]
    pRGBInputData = (struct RGB *)malloc(iNumPixels*sizeof(struct RGB));

    // 画素値の読み込み
    if(iPPMType == P6) {
	pucData = (unsigned char *)malloc(iNumPixels*sizeof(unsigned char[3]));
	fread(pucData, sizeof(unsigned char), iNumPixels*3, fp);
    }
    for(h = 0; h < *iHeight; h++) {
	for(w = 0; w < *iWidth; w++) {
	    if(iPPMType == P3) {
		if(feof(fp)) {
		    fprintf(stderr, "Error: [%s] is not a correct PPM file.\n",
			    chFileName);
		    exit(-1);
		}

		// １画素のRGBデータの読み込み
		fscanf(fp, "%d %d %d ",
		       &sRGBcolor.iRed, &sRGBcolor.iGreen, &sRGBcolor.iBlue);
		// RGBデータの格納
		GetIndexFromAxis(*iWidth, w, h, &iIndex);
		pRGBInputData[iIndex].iRed   = sRGBcolor.iRed;
		pRGBInputData[iIndex].iGreen = sRGBcolor.iGreen;
		pRGBInputData[iIndex].iBlue  = sRGBcolor.iBlue;
	    } else { // P6
		GetIndexFromAxis(*iWidth, w, h, &iIndex);
		pRGBInputData[iIndex].iRed   = pucData[3*iIndex];
		pRGBInputData[iIndex].iGreen = pucData[3*iIndex+1];
		pRGBInputData[iIndex].iBlue  = pucData[3*iIndex+2];
	    }


        }
    }

    // ファイルのクローズ
    fclose(fp);  

    return pRGBInputData;
}

//--------------------------------------------------------------------//
// void FreePpm(struct RGB * pRGBOutputData)                          //
// 内      容 : PPM形式の画像データを保存しているメモリ領域の開放     //
// 更  新  日 : 2004. 2. 15 木村 彰徳 (Computer Graphics Lab.)        //
//                                                                    //
// [引数]                                                             //
// pRGBOutputData : ２次元([画素数][RGB])のPPM形式のデータ            //
//--------------------------------------------------------------------//
void FreePpm(struct RGB * pRGBOutputData) {
    free(pRGBOutputData);
}

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
void WritePpm(struct RGB * pRGBOutputData, int iWidth, int iHeight, int iMaxValue) {

    FILE *fp;              // ファイルポインタ
    char chFileName[80];   // ファイルネーム
    int i;                 // ループカウンタ

    // 出力ファイル名の入力
    printf("Input OUTPUT PPM file name[*.ppm]? > ");
    scanf("%s", chFileName);

    // 出力ファイルのオープン
    // オープンに失敗の場合は、エラー文を出力し、返り値として１を返す.
    if((fp = fopen(chFileName, "w")) == NULL){
        fprintf(stderr, "Cannot open file [%s].\n", chFileName);
        exit(1);
    }

    // ヘッダ領域書き込み(画像サイズ等)
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d\n", iWidth, iHeight);
    fprintf(fp, "%d\n", iMaxValue); // 最大値

    // 各画素データ書き込み
    for(i = 0; i < iWidth*iHeight; i++){
        // 画素値をファイルの書き込み
        fprintf(fp, "%5d%5d%5d  ",
		pRGBOutputData[i].iRed,
		pRGBOutputData[i].iGreen,
		pRGBOutputData[i].iBlue);
                
        // ５画素値（RGB）ごとに改行
        if((i + 1)%5 == 0){
           fprintf(fp, "\n");
        }
    }
    fprintf(fp, "\n");
    // ファイルのクローズ
    fclose(fp);
}

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
int * ReadPgm(int * iWidth, int * iHeight, int * iMaxValue) {

    FILE *fp;                    // ファイルポインタ
    char chFileName[80];         // ファイルネーム
    enum PGM {P2, P5};           // テキスト形式 or バイナリ形式
    int iPGMType;                // P2 or P5
    const int MAXCHARS = 100;    // １行の最大文字数
    char chLine[MAXCHARS];       // ファイル形式の認識用変数
    int * piInputData;           // 入力データを格納する変数
    unsigned char * pucData;     // 入力データを格納する変数
    int iNumPixels;              // 画素数
    int iIndex;                  // インデックス
    int w, h;                    // ループカウンタ
    
    // ファイル名の入力
    printf("Input INPUT PGM file name[*.pgm]? > ");
    scanf("%s", chFileName);

    // 入力されたファイルのオープン
    // オープンに失敗の場合は、エラー文を出力し、返り値として１を返す．
    if((fp = fopen(chFileName, "r")) == NULL){
        fprintf(stderr, "Cannot open file [%s].\n", chFileName);
        exit(1);
    }

    // ヘッダ領域読み込み
    fgets(chLine, MAXCHARS, fp);

    // PPM形式(P3)ではない場合、エラー文を出力し、返り値として１を返す
    if (strncmp(chLine, "P2", 2) == 0){
	iPGMType = P2;
    } else if (strncmp(chLine, "P5", 2) == 0){
	iPGMType = P5;
	fclose(fp);
	fp = fopen(chFileName, "rb");
	fgets(chLine, MAXCHARS, fp);
    } else {
	fprintf(stderr, "[%s] is not PGM file.\n", chFileName);
        exit(1);
    }

    // コメント行を読み飛ばす
    SkipCommentLine(fp);

    // 画像データから、画像の幅・高さを読み込む
    fgets(chLine, MAXCHARS, fp);
    sscanf(chLine, "%d %d", iWidth, iHeight);

    // コメント行を読み飛ばす
    SkipCommentLine(fp);

    // 画像データから、解像度を読み込む
    fgets(chLine, MAXCHARS, fp);
    sscanf(chLine, "%d", iMaxValue);
    iNumPixels = (*iWidth)*(*iHeight);

    // 入力画像データのメモリ領域の確保
    // piInputData[iWidth*iHeight]
    piInputData = (int *)(malloc(iNumPixels*sizeof(int)));

    // コメント行の読み飛ばし
    SkipCommentLine(fp);

    // 画素値の読み込み
    if(iPGMType == P5) {
	pucData = (unsigned char *)malloc(iNumPixels*sizeof(unsigned char));
	fread(pucData, sizeof(unsigned char), iNumPixels, fp);
    }
    for(h = 0; h < *iHeight; h++) {
	for(w = 0; w < *iWidth; w++) {
	    if(iPGMType == P2) {
		if(feof(fp)) {
		    fprintf(stderr, "Error: [%s] is not a correct PGM file.\n",
			    chFileName);
		    exit(-1);
		}

		// １画素のデータの読み込み，格納
		GetIndexFromAxis(*iWidth, w, h, &iIndex);
		fscanf(fp, "%d", &piInputData[iIndex]);
	    } else { // P5
		GetIndexFromAxis(*iWidth, w, h, &iIndex);
		piInputData[iIndex] = pucData[iIndex];
	    }
        }
    }

    // ファイルのクローズ
    fclose(fp);  

    return piInputData;
}

//---------------------------------------------------------------------//
// void FreePgm(int * piOutputData)                                    //
// 内      容 : PGM形式の画像データを保存しているメモリ領域の開放      //
// 更  新  日 : 2004. 2. 15 木村 彰徳 (Computer Graphics Lab.)         //
//                                                                     //
// [引数]                                                              //
// piOutputData : ２次元([画素数][RGB])のPGM形式のデータ               //
//---------------------------------------------------------------------//
void FreePgm(int * piOutputData) {
    free(piOutputData);
}

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
void WritePgm(int * piOutputData, int iWidth, int iHeight, int iMaxValue) {

    FILE *fp;              // ファイルポインタ
    char chFileName[80];   // ファイルネーム
    int i;                 // ループカウンタ

    // 出力ファイル名の入力
    printf("Input OUTPUT PGM file name[*.pgm]? > ");
    scanf("%s", chFileName);

    // 出力ファイルのオープン
    // オープンに失敗の場合は、エラー文を出力し、返り値として１を返す.
    if((fp = fopen(chFileName, "w")) == NULL){
        fprintf(stderr, "Cannot open file [%s].\n", chFileName);
        exit(1);
    }

    // ヘッダ領域書き込み(画像サイズ等)
    fprintf(fp, "P2\n");
    fprintf(fp, "%d %d\n", iWidth, iHeight);
    fprintf(fp, "%d\n", iMaxValue);  // 最大値

    // 各画素データ書き込み
    for(i = 0; i < iWidth*iHeight; i++){
    
        // 画素値をファイルの書き込み
        fprintf(fp, "%5d", piOutputData[i]);
                
        // 10画素値ごとに改行
        if((i + 1)%15 == 0){
           fprintf(fp, "\n");
        }
    }
    fprintf(fp, "\n");
    // ファイルのクローズ
    fclose(fp);
}

//---------------------------------------------------------------------//
// void SkipCommentLine(FILE * fp)                                     //
// 内      容 : コメント行を読み飛ばす                                 //
// 更  新  日 : 2004. 2. 15 木村 彰徳 (Computer Graphics Lab.)         //
//                                                                     //
// [引数]                                                              //
// fp     : ファイルストリームポインタ                                 //
//---------------------------------------------------------------------//
void SkipCommentLine(FILE * fp) {
    
    const int MAXCHARS = 100;
    char chLine[MAXCHARS]; 
    fpos_t current;

    while(!feof(fp)) {
	// 現在のストリーム位置の保存
	fgetpos(fp, &current);
	
	// １行取得
	fgets(chLine, MAXCHARS, fp);

	// コメント行でなければ，ストリーム位置を戻してリターン
	if(chLine[0] != '#') {
	    fsetpos(fp, &current);
	    return;
	}
    }    
}
