#include "stdafx.h"
#include "MainGame.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"


CMainGame::CMainGame() : m_BackDC(nullptr) , m_hDC(nullptr)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	m_BackDC = ::CreateCompatibleDC(m_hDC);
	m_bmpBack = ::CreateCompatibleBitmap(m_hDC, 800, 600);
	HBITMAP prev = (HBITMAP)::SelectObject(m_BackDC, m_bmpBack);
	::DeleteObject(prev);

	CSceneMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	Rectangle(m_BackDC, 0, 0, WINCX, WINCY);
	CSceneMgr::Get_Instance()->Render(m_BackDC);
	::BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_BackDC, 0, 0, SRCCOPY); 
	
}

void CMainGame::Release()
{
	CSceneMgr::Destroy();
	CKeyMgr::Destroy();
	ReleaseDC(g_hWnd, m_hDC);
	//ReleaseDC(g_hWnd, m_BackDC);
}
