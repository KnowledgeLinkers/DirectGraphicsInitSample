#ifndef DIRECT_GRAPHICS_H_
#define DIRECT_GRAPHICS_H_

#include <Windows.h>

/*
	DirectGraphics�̏�����
		�߂�l�F
			�����������F
				true
			���������s�F
				false

		�����F
			HWND window_handle�F
				DirectGraphics�ŕ`�悷��ΏۂƂȂ�E�B���h�E�̃n���h��

		���e�F
			DirectX�̏��������s��
			�K���Q�[�����[�v�̑O��1�x�������s���邱��
			�������DirectGraphics�̂ݏ��������Ă�
*/
bool InitDirectGraphics(HWND window_handle);

/*
	DirectGraphics�̏I��
		�߂�l�F
			�Ȃ�

		�����F
			�Ȃ�

		���e�F
			DirectX���I��������
			�Q�[�����[�v�𔲂�����K���P�x�������s���邱��
*/
void ReleaseDirectGraphics();

/*
	�`��J�n
		�߂�l�F
			true�F�J�n�\
			false�F�J�n�s��

		�����F
			�Ȃ�

		���e�F
			�`����J�n�ʒm
*/
bool DrawStart();

/*
	�`��I��
		�߂�l�F
			�Ȃ�

		�����F
			�Ȃ�

		���e�F
			�`��I���ʒm
*/
void DrawEnd();

#endif
