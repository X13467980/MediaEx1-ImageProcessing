//=====================================================================//
//                                                                     //
//  ファイル名 : ImageFilter.h                                         //
//  内      容 : PPM(Portable PixMap) または PGM(Portable GrayMap)形式 //
//               のデータを画像処理する関数の定義                      //
//  更  新  日 : 2004. 2. 14 木村 彰徳 (Computer Graphics Lab.)        //
//               2003. 3. 21 駒井 教平 (Computer Vision & Games Lab.)  //
//                                                                     //
//=====================================================================//
#ifndef _IMAGEFILTER_H_
#define _IMAGEFILTER_H_

//---------------------------------------------------------------------//
// 例１）                                                              //
// void  NegativeImage(void)                                           //
//  内      容 : PPM形式の入力データをネガ画像に変換                   //
//  更  新  日 : 2004. 2. 11 木村 彰徳 (Computer Graphics Lab.)        //
//---------------------------------------------------------------------//
void NegativeImage(void);
void GrayscaleImage(void);
void BrightnessHistogram(void);
void BlackWhiteImage();


//---------------------------------------------------------------------//
// 例２）                                                              //
// void DrawLines(void)                                                //
//  内      容 : PGM形式の入力データに線を描く　　                     //
//  更  新  日 : 2004. 2. 12 木村 彰徳 (Computer Graphics Lab.)        //
//---------------------------------------------------------------------//
//void DrawLines(void);

#endif

