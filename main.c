//=====================================================================//
//                                                                     //
//  ファイル名 : main.c                                                //
//  内      容 : 画像処理プログラムのメインプログラム                  //
//  更  新  日 : 2004. 2. 17 木村 彰徳 (Computer Graphics Lab.)        //
//               2003. 3. 21 駒井 教平 (Computer Vision & Games Lab.)  //
//                                                                     //
//=====================================================================//
#include <stdio.h>

#include "ImageFilter.h"

int main(void) {

    // 画像処理を行う関数の呼び出し
    // 例１）PPM形式の入力データをネガ画像に変換
    NegativeImage();

    GrayscaleImage();

    int threshold = 128; // 仮のしきい値

    // ヒストグラムの生成
    BrightnessHistogram();

    // 2値化画像の生成
    BlackWhiteImage(threshold);

     // 例２）PGM形式のデータに線を描く
    // DrawLines();

    // 正常終了
    return 0;
}
