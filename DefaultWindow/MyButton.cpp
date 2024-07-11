#include "stdafx.h"
#include "MyButton.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CMyButton::CMyButton(): m_eStageID(SC_NONE)
{
	ZeroMemory(&m_tRect, sizeof(RECT));
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize()
{
	m_tInfo.fRadius = 100.f;
}

int CMyButton::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	m_tRect.left	= static_cast<long>(m_tInfo.vPos.x - (m_tInfo.fRadius * 0.5f));
	m_tRect.top		= static_cast<long>(m_tInfo.vPos.y - (m_tInfo.fRadius * 0.5f));
	m_tRect.right	= static_cast<long>(m_tInfo.vPos.x + (m_tInfo.fRadius * 0.5f));
	m_tRect.bottom	= static_cast<long>(m_tInfo.vPos.y + (m_tInfo.fRadius * 0.5f));

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			if		(m_eStageID == SC_X)
				CSceneMgr::Get_Instance()->Scene_Change(SC_X);

			else if (m_eStageID == SC_Y)
				CSceneMgr::Get_Instance()->Scene_Change(SC_Y);

			else if (m_eStageID == SC_Z)
				CSceneMgr::Get_Instance()->Scene_Change(SC_Z);

			else if (m_eStageID == SC_MENU)
				CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		}
	}

	// 0417 16:35 잠시 주석
	/*if (CSceneMgr::Get_Instance()->Get_Scene() != SC_MENU)
	{
		m_bDead = true;
	}

	if ((m_eStageID == SC_MENU) &&
		(CSceneMgr::Get_Instance()->Get_Scene() == SC_X ||
		 CSceneMgr::Get_Instance()->Get_Scene() == SC_Y	||
		 CSceneMgr::Get_Instance()->Get_Scene() == SC_Z))
	{
		m_bDead = false;
	}*/
}

void CMyButton::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	TCHAR strBuffer[64];
	int iCHeight(0);

	switch (m_eStageID)
	{
	case SC_X:
		lstrcpy(strBuffer, L"X");
		iCHeight = 50;
		break;

	case SC_Y:
		lstrcpy(strBuffer, L"Y");
		iCHeight = 50;
		break;

	case SC_Z:
		lstrcpy(strBuffer, L"Z");
		iCHeight = 50;
		break;

	case SC_MENU:
		iCHeight = 20;
		lstrcpy(strBuffer, L"메뉴로\n\n나가기");
		break;
	}

	RECT tTextBox = {
		static_cast<int>(m_tInfo.vPos.x - 30),
		static_cast<int>(m_tInfo.vPos.y - 30),
		static_cast<int>(m_tInfo.vPos.x + 30),
		static_cast<int>(m_tInfo.vPos.y + 30),
	};

	HFONT hCurFont, hOldFont;

	hCurFont = CreateFont(iCHeight, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH, TEXT("궁서"));
	hOldFont = (HFONT)SelectObject(hDC, hCurFont);

	DrawText(hDC, strBuffer, lstrlen(strBuffer), &tTextBox, DT_CENTER);

	SelectObject(hDC, hOldFont);
	DeleteObject(hCurFont);

}

void CMyButton::Release()
{
}

void CMyButton::OnCollision()
{
}
