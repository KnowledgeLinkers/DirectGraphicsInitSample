#include "DirectGraphics.h"
#include <d3d9.h>
#include <d3dx9.h>
// https://www.microsoft.com/en-us/download/details.aspx?id=6812
//https://yttm-work.jp/directx/directx_0004.html
// �ÓI���C�u����
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// �O���[�o���ϐ�
static LPDIRECT3D9 g_pD3DInterface;		// DirectGraphics�C���^�[�t�F�[�X
static LPDIRECT3DDEVICE9 g_pD3DDevice;	// DirectGraphics�f�o�C�X

bool InitDirectGraphics(HWND window_handle)
{
	D3DPRESENT_PARAMETERS present_param;

	// �C���^�[�t�F�[�X�쐬
	g_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3DInterface == NULL)
	{
		// �쐬���s
		return false;
	}

	ZeroMemory(&present_param, sizeof(D3DPRESENT_PARAMETERS));

	// �o�b�N�o�b�t�@�̐� => 1
	present_param.BackBufferCount = 1;
	// �o�b�N�o�b�t�@�̃t�H�[�}�b�g => D3DFMT_UNKNOWN(�t�H�[�}�b�g��m��܂���)
	present_param.BackBufferFormat = D3DFMT_UNKNOWN;
	// �E�B���h�E���[�h�ݒ� => �萔�Ő؂�ւ�
	present_param.Windowed = true;

	// �X���b�v�G�t�F�N�g => �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�ւ̐؂�ւ����@
	present_param.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// DirectDevice�̍쐬
	if (FAILED(g_pD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		&present_param,
		&g_pD3DDevice)))
	{
		return false;
	}

	// �r���[�|�[�g�p�����[�^
	D3DVIEWPORT9 view_port;

	// �r���[�|�[�g�̍�����W
	view_port.X = 0;
	view_port.Y = 0;
	// �r���[�|�[�g�̕�
	view_port.Width = present_param.BackBufferWidth;
	// �r���[�|�[�g�̍���
	view_port.Height = present_param.BackBufferHeight;
	// �r���[�|�[�g�[�x�ݒ�
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 5.0f;

	// �r���[�|�[�g�ݒ�
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
	// �P�D�V�[���N���A
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);

	//�f�[�^�\�z
	LPDIRECT3DVERTEXBUFFER9 pVBuffer = nullptr;
	// ���_�f�[�^�쐬�@
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

	// �Q�D�V�[���`��J�n
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
	// �R�D�V�[���`��I��
	g_pD3DDevice->EndScene();
	// �S�D�o�b�t�@�]��
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}