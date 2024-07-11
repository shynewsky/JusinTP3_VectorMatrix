#include "stdafx.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "StageX.h"
#include "StageY.h"
#include "StageZ.h"
#include "UIHeart.h"
#include "Status.h"
#include "MyMenu.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr() : m_pScene(nullptr), m_ePreScene(SC_NONE), m_eCurScene(SC_MENU)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	//CObjMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);
	m_eCurScene = eID;


	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_NONE:
			CObjMgr::Get_Instance()->Set_UI_Render(false);
			break;

		case SC_MENU:
			m_pScene = new CMyMenu;
			CObjMgr::Get_Instance()->Set_UI_Render(false);
			break;

		case SC_X:
			m_pScene = new CStageX;
			CObjMgr::Get_Instance()->Set_UI_Render(true);
			break;

		case SC_Y:
			m_pScene = new CStageY;
			CObjMgr::Get_Instance()->Set_UI_Render(true);
			break;

		case SC_Z:
			m_pScene = new CStageZ;
			CObjMgr::Get_Instance()->Set_UI_Render(true);
			break;
		}

		CStatus::Get_Instance()->Reset_Score(m_eCurScene);
		for (int i = 0; i < CStatus::Get_Instance()->Get_Hp(); ++i)
		{
			CObjMgr::Get_Instance()->Less_UI(UI_HEART);
		}
		Initialize();
		m_pScene->Initialize();
		m_dwScoreTime = GetTickCount();
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Initialize()
{
	CStatus::Get_Instance()->Reset_Hp();
	CObj* UIObj;
	for (int i = 0; i < CStatus::Get_Instance()->Get_Hp(); ++i)
	{
		UIObj = new CUIHeart(18 + 32 * (i) , 550);
		UIObj->Initialize();
		CObjMgr::Get_Instance()->Add_UI(UI_HEART, UIObj);
	}
	
}

void CSceneMgr::Update()
{
	int iResult(0);
	iResult = m_pScene->Update();

	if (iResult == OBJ_NOEVENT)
	{
		if (m_dwScoreTime + 100.f <= GetTickCount())
		{
			CStatus::Get_Instance()->Add_Score(m_eCurScene, 1);
			m_dwScoreTime = GetTickCount();
		}
		
	}
	else if (iResult == OBJ_DEAD)
	{
		CStatus::Get_Instance()->Calc_HighScore(m_eCurScene);
	}


}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC _hDC)
{
	m_pScene->Render(_hDC);
	if (m_eCurScene != SC_MENU)
	{
		TCHAR	szBuff[32] = L"";
		swprintf_s(szBuff, L"SCORE : %d", CStatus::Get_Instance()->Get_Score(m_eCurScene));
		TextOut(_hDC, (WINCX)-135, 20, szBuff, lstrlen(szBuff));
	}
}

void CSceneMgr::Release()
{
	Safe_Delete<CStage*>(m_pScene);
	CObjMgr::Destroy();
	CStatus::Destroy();
}
