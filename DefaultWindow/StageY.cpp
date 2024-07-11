#include "stdafx.h"
#include "StageY.h"

#include <ctime>

#include "FlagY.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "PlayerY.h"
#include "Status.h"

CStageY::CStageY()
	: m_dwMonsterTimer(GetTickCount()), m_dwFlagTimer(GetTickCount()),
	m_iFlagInterval(0), m_iFlagCount(0), m_iScore(0), m_bIsFinished(false)
{
	ZeroMemory(&m_vCreatePos, sizeof(D3DXVECTOR3) * 3);
}

CStageY::~CStageY()
{
	Release();
}

void CStageY::Initialize()
{
	auto pPlayer = new CPlayerY;
	pPlayer->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);

	m_iFlagInterval = 2000;

	m_vCreatePos[0] = { 200.f, 600.f, 0.f };
	m_vCreatePos[1] = { 400.f, 600.f, 0.f };
	m_vCreatePos[2] = { 600.f, 600.f, 0.f };
}

void CStageY::Release()
{
	CObjMgr::Get_Instance()->SetDead_ID(OBJ_BUTTON);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_FLAG);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
}

int CStageY::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bIsFinished)
	{
		if (CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos.x - 50.f >= 800.f ||
			CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos.x + 50.f <= 0.f)
		{
			Show_ExitBtn();
			m_bIsFinished = true;
			m_bDead = true;
		}
	}

	Create_Flag();
	CObjMgr::Get_Instance()->Update();

	return OBJ_NOEVENT;
}

void CStageY::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStageY::Render(HDC _hDC)
{
	MoveToEx(_hDC, 100.f, 0.f, nullptr);
	LineTo(_hDC, 100.f, 600.f);

	MoveToEx(_hDC, 700.f, 0.f, nullptr);
	LineTo(_hDC, 700.f, 600.f);

	CObjMgr::Get_Instance()->Render(_hDC);
}

void CStageY::Create_Flag()
{
	if (m_dwFlagTimer + m_iFlagInterval < GetTickCount())
	{
		auto pFlag = new CFlagY(
			m_vCreatePos[m_iFlagCount].x,
			m_vCreatePos[m_iFlagCount].y);

		pFlag->Initialize();

		srand(static_cast<unsigned>(time(nullptr)));
		int iRand = rand() % 4;

		pFlag->Set_Distance(70.f - static_cast<float>(iRand) * 10.f);

		if (CStatus::Get_Instance()->Get_Score(SC_Y) >= 100)
		{
			iRand = rand() % (CStatus::Get_Instance()->Get_Score(SC_Y) / 100);

			if (iRand != 0)
			{
				if (m_iFlagCount == 0)
				{
					pFlag->Set_Dir(1);
					pFlag->Set_Side(static_cast<float>(iRand));
					pFlag->Set_Move();
				}
				else
				{
					pFlag->Set_Dir(-1);
					pFlag->Set_Side(static_cast<float>(iRand));
					pFlag->Set_Move();
				}
			}
		}

		CObjMgr::Get_Instance()->Add_Object(OBJ_FLAG, pFlag);

		m_iFlagCount += 2;
		if (m_iFlagCount >= 3)
		{
			m_iFlagCount = 0;
		}

		m_dwFlagTimer = GetTickCount();
	}
}

void CStageY::Show_ExitBtn() const
{
	auto pButton = new CMyButton;
	pButton->Initialize();
	pButton->Set_vPos({ WINCX / 2, WINCY / 2, 0.f });
	pButton->Set_StageID(SC_MENU);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);
}
