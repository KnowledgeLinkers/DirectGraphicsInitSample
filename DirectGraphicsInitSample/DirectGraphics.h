#ifndef DIRECT_GRAPHICS_H_
#define DIRECT_GRAPHICS_H_

#include <Windows.h>

/*
	DirectGraphicsの初期化
		戻り値：
			初期化成功：
				true
			初期化失敗：
				false

		引数：
			HWND window_handle：
				DirectGraphicsで描画する対象となるウィンドウのハンドル

		内容：
			DirectXの初期化を行う
			必ずゲームループの前に1度だけ実行すること
			※現状はDirectGraphicsのみ初期化してる
*/
bool InitDirectGraphics(HWND window_handle);

/*
	DirectGraphicsの終了
		戻り値：
			なし

		引数：
			なし

		内容：
			DirectXを終了させる
			ゲームループを抜けた後必ず１度だけ実行すること
*/
void ReleaseDirectGraphics();

/*
	描画開始
		戻り値：
			true：開始可能
			false：開始不可

		引数：
			なし

		内容：
			描画を開始通知
*/
bool DrawStart();

/*
	描画終了
		戻り値：
			なし

		引数：
			なし

		内容：
			描画終了通知
*/
void DrawEnd();

#endif
