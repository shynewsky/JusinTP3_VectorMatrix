#pragma once

extern	HWND		g_hWnd;

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0

#define			OBJ_NOEVENT		0
#define			OBJ_DEAD		1

#define			VK_MAX		0xff

enum OBJID { OBJ_PLAYER, OBJ_MONSTER, OBJ_OBSTACLE, OBJ_FLAG, OBJ_BULLET, OBJ_BUTTON, OBJ_MOUSE, OBJ_END };
enum UIID	{ UI_HEART, UI_SCORE, UI_END};
enum SCENEID { SC_NONE, SC_MENU, SC_X, SC_Y, SC_Z, SC_END };


typedef struct tagInfo
{
	
	D3DXVECTOR3 vPos;	//위치
	D3DXVECTOR3 vDir;	//방향
	D3DXVECTOR3 vLook;	

	float fRadius;		//반지름 값

	D3DXMATRIX	matWorld;	//월드 행렬

}INFO;

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

template<typename T>
void Safe_Delete_Array(T& Temp)
{
	if (Temp)
	{
		delete[] Temp;
		Temp = nullptr;
	}
}

