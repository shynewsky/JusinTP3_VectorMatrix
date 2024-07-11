#include "stdafx.h"
#include "StageX.h"
#include "PlayerX.h"
#include "ObjMgr.h"
#include "Status.h"
#include "MyButton.h"

#include "MonsterX1.h"
#include "MonsterX2.h"

CStageX::CStageX()
{
}

CStageX::~CStageX()
{
	Release();
}

void CStageX::Initialize()
{
	CObjMgr::Get_Instance()->Reset_Player();

	CObj* pPlayer = new CPlayerX;
	pPlayer->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
}

void CStageX::Release()
{
	CObjMgr::Get_Instance()->SetDead_ID(OBJ_BUTTON);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_FLAG);
	CObjMgr::Get_Instance()->SetDead_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
}

int CStageX::Update()
{
	if (m_bDead)
	{
		CObjMgr::Get_Instance()->Update();
		return OBJ_DEAD;
	}

	CObjMgr::Get_Instance()->Update();

	if (m_dwSpawnTime + 1000 < GetTickCount())
	{
		CObj* pMonster;

		switch (m_dwSpawnTime % 2)
		{
		case 0:
			pMonster = new CMonsterX1;
			pMonster->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pMonster);
			break;

		case 1:
			pMonster = new CMonsterX2;
			pMonster->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pMonster);
			break;
		}

		m_dwSpawnTime = GetTickCount();
	}

	
	return OBJ_NOEVENT;
}

void CStageX::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	if (CStatus::Get_Instance()->Get_Hp() <= 0.f && !m_bDead)
	{
		m_bDead = true;
		auto pButton = new CMyButton;
		pButton->Initialize();
		pButton->Set_vPos({ WINCX / 2, WINCY / 2, 0.f });
		pButton->Set_StageID(SC_MENU);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);
	}
}

void CStageX::Render(HDC _hDC)
{
	MoveToEx(_hDC, 0, 480, nullptr);
	LineTo(_hDC, 800, 480);

	CObjMgr::Get_Instance()->Render(_hDC);
}

