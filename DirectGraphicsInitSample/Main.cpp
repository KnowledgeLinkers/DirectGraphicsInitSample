#include <Windows.h>
#include "Window.h"
#include "DirectGraphics.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmpLine,
	INT       nCmdShow)
{
	HWND window_handle = MakeWindow(hInstance, 800, 600);

	// DirectXの初期化
	InitDirectGraphics(window_handle);

	while (true)
	{
		bool message_ret = false;
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else 
		{
			// 描画開始
			if (DrawStart() == true)
			{
				// 描画終了
				DrawEnd();
			}
		}
	}

	ReleaseDirectGraphics();
}
