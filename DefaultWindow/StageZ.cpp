#include "stdafx.h"
#include "StageZ.h"
#include "Define.h"
#include "PlayerZ.h"
#include "ObjMgr.h"
#include "MonsterZ1.h"
#include "Status.h"
#include "MyButton.h"
#include "keyMgr.h"
#include "SceneMgr.h"

#include <ctime>


CStageZ::CStageZ() : m_dwGenTime(NULL), m_bRegenNow(true), m_dwTime(NULL), m_fDifficulty(0), m_dwDifTime(NULL)
{
}

CStageZ::~CStageZ()
{
	Release();
}

void CStageZ::Initialize()
{
	CObjMgr::Get_Instance()->Reset_Player();
	
	CObj* pPlayer = new CPlayerZ;
	pPlayer->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
	m_dwGenTime = GetTickCount();
	m_dwTime = GetTickCount();
	m_dwDifTime = GetTickCount();
	srand(unsigned(time(NULL)));
}

int CStageZ::Update()
{
	
	if (m_bDead)
	{
		CObjMgr::Get_Instance()->Update();
		return OBJ_DEAD;
	}

	if (m_bRegenNow)
	{
		if (m_dwGenTime + 3000.f - m_fDifficulty <= GetTickCount())
		{
			int iPosX = rand() % 501 + 150;
			CObj* pBox = new CMonsterZ1(iPosX, 120.f);
			pBox->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBox);
			m_dwGenTime = GetTickCount();
		}

		if (m_dwDifTime + 1500.f <= GetTickCount())
		{
			if (m_fDifficulty <= 1200)
			{
				m_fDifficulty += 100.f;
				m_dwDifTime = GetTickCount();
			}
		}

	}


	CObjMgr::Get_Instance()->Update();
	return OBJ_NOEVENT;
}

void CStageZ::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();

	if (CStatus::Get_Instance()->Get_Hp() <= 0 && !m_bDead)
	{
		m_bRegenNow = false;
		m_bDead = true;

		auto pButton = new CMyButton;
		pButton->Initialize();
		pButton->Set_vPos({ WINCX / 2, WINCY / 2, 0.f });
		pButton->Set_StageID(SC_MENU);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);
	}
}

void CStageZ::Render(HDC _hDC)
{
	MoveToEx(_hDC, -100, WINCY, nullptr);
	LineTo(_hDC, 100, 150);	//400 , 1125
	LineTo(_hDC, 700, 150);
	LineTo(_hDC, WINCX + 100 , WINCY);

	MoveToEx(_hDC, WINCX + 100, WINCY - 40, nullptr);
	LineTo(_hDC, 700, 110);
	LineTo(_hDC, 700, 150);
	MoveToEx(_hDC, 700, 110, nullptr);
	LineTo(_hDC, 800, 110);

	MoveToEx(_hDC, -100, WINCY - 40, nullptr);
	LineTo(_hDC, 100, 110);
	LineTo(_hDC, 100, 150);
	MoveToEx(_hDC, 100, 110, nullptr);
	LineTo(_hDC, 0, 110);

	CObjMgr::Get_Instance()->Render(_hDC);
}

void CStageZ::Release()
{
	CObjMgr::Get_Instance()->SetDead_ID(OBJ_BUTTON);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
}