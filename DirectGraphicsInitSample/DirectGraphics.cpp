#include "DirectGraphics.h"
#include <d3d9.h>
#include <d3dx9.h>
// https://www.microsoft.com/en-us/download/details.aspx?id=6812
//https://yttm-work.jp/directx/directx_0004.html
// 静的ライブラリ
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// グローバル変数
static LPDIRECT3D9 g_pD3DInterface;		// DirectGraphicsインターフェース
static LPDIRECT3DDEVICE9 g_pD3DDevice;	// DirectGraphicsデバイス

bool InitDirectGraphics(HWND window_handle)
{
	D3DPRESENT_PARAMETERS present_param;

	// インターフェース作成
	g_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3DInterface == NULL)
	{
		// 作成失敗
		return false;
	}

	ZeroMemory(&present_param, sizeof(D3DPRESENT_PARAMETERS));

	// バックバッファの数 => 1
	present_param.BackBufferCount = 1;
	// バックバッファのフォーマット => D3DFMT_UNKNOWN(フォーマットを知りません)
	present_param.BackBufferFormat = D3DFMT_UNKNOWN;
	// ウィンドウモード設定 => 定数で切り替え
	present_param.Windowed = true;

	// スワップエフェクト => バックバッファとフロントバッファへの切り替え方法
	present_param.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// DirectDeviceの作成
	if (FAILED(g_pD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		&present_param,
		&g_pD3DDevice)))
	{
		return false;
	}

	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	// ビューポートの左上座標
	view_port.X = 0;
	view_port.Y = 0;
	// ビューポートの幅
	view_port.Width = present_param.BackBufferWidth;
	// ビューポートの高さ
	view_port.Height = present_param.BackBufferHeight;
	// ビューポート深度設定
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 5.0f;

	// ビューポート設定
	if (FAILED(g_pD3DDevice->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

void ReleaseDirectGraphics()
{
	g_pD3DDevice->Release();
	g_pD3DInterface->Release();
}

bool DrawStart()
{
	// １．シーンクリア
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);

	//データ構築
	LPDIRECT3DVERTEXBUFFER9 pVBuffer = nullptr;
	// 頂点データ作成　
	struct Vertex
	{
		FLOAT x, y, z;
		D3DCOLOR color;
	};

	Vertex VertexData[3] = {
	  { 0.0f,  0.5f, 0.0f, D3DCOLOR_ARGB(255, 0,0,255) },
	  { 0.5f, -0.5f, 0.0f,  D3DCOLOR_ARGB(255,0,255,0) },
	  { -0.5f, -0.5f, 0.0f, D3DCOLOR_ARGB(255, 255,0,0) },
	};
	g_pD3DDevice->CreateVertexBuffer(sizeof(VertexData), 0,
		D3DFVF_XYZ | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &pVBuffer, NULL);

	void* vb;
	if (SUCCEEDED(pVBuffer->Lock(0, sizeof(VertexData), &vb, 0))) {
		memcpy(vb, &VertexData, sizeof(VertexData));
		pVBuffer->Unlock();
	}

	// ２．シーン描画開始
	if (D3D_OK == g_pD3DDevice->BeginScene())
	{
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		g_pD3DDevice->SetStreamSource(0, pVBuffer, 0, sizeof(Vertex));
		g_pD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
		return true;
	}

	return false;
}

void DrawEnd()
{
	// ３．シーン描画終了
	g_pD3DDevice->EndScene();
	// ４．バッファ転送
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
