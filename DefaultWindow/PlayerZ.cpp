#include "stdafx.h"
#include "PlayerZ.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Status.h"

CPlayerZ::CPlayerZ() : m_dwBlinkTime(NULL), m_bIdleCtr(true), m_vHeadPos({ 0, 0, 0 }), m_bPeekNow(false), m_bIsBroken(false)
{
}

CPlayerZ::~CPlayerZ()
{
}

void CPlayerZ::Initialize()
{
	m_tInfo.vPos = { WINCX / 2.f, WINCY - 200.f, 0.f };
	m_tInfo.vLook = { 0.f, 1.f, 0.f };
	m_fSpeed = 5.f;
	m_tInfo.fRadius = 90.f;
	m_tInfo.vDir = { 1.f, 0.f, 0.f };

	FirstPoint();
	
}

int CPlayerZ::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	if (!m_bIsBroken)
	{
		if (m_bIdleCtr)
		{
			m_tInfo.vPos.y += 0.1f;
			if (m_tInfo.vPos.y >= 405)
			{
				m_bIdleCtr = !m_bIdleCtr;
			}
		}
		else
		{
			m_tInfo.vPos.y -= 0.1f;
			if (m_tInfo.vPos.y <= 395)
			{
				m_bIdleCtr = !m_bIdleCtr;
			}
		}

		if (m_bInvincibillity)
		{
			if (m_dwBlinkTime + 150 <= GetTickCount())
			{
				m_bRenderNow = !m_bRenderNow;
				m_dwBlinkTime = GetTickCount();
			}

			if (m_dwInvTime + 1500 <= GetTickCount())
			{
				m_bInvincibillity = false;
				m_bRenderNow = true;

			}
		}

		if (!m_bPeekNow)
		{
			m_fAngle -= m_fAngle * 0.1f;
		}

		Key_Input();
	}
	else   //hp °¡ ¾ø´Ù¸é
	{
		if (m_tInfo.vPos.y <= 900)
		{
			m_tInfo.vPos.y += m_fSpeed;
		}
		else
		{
			m_bDead = true;
		}
	}
	
    return OBJ_NOEVENT;
}

void CPlayerZ::Late_Update()
{
	if (m_tInfo.vPos.x < 90.f)
	{
		m_tInfo.vPos.x = 90.f;
	}
	if (m_tInfo.vPos.x > 710.f)
	{
		m_tInfo.vPos.x = 710.f;
	}
	m_vHeadPos = { m_tInfo.vPos.x , m_tInfo.vPos.y - 75, 0};
	Update_DrawPoint();
}

void CPlayerZ::Render(HDC hDC)
{
	//Ellipse(hDC, m_tInfo.vPos.x - m_tInfo.fRadius, m_tInfo.vPos.y - m_tInfo.fRadius, m_tInfo.vPos.x + m_tInfo.fRadius, m_tInfo.vPos.y + m_tInfo.fRadius);
	if (m_bRenderNow)
	{
		if (m_bIsBroken)
		{
			MoveToEx(hDC, m_vDrawPointWheelLine[0].x, m_vDrawPointWheelLine[0].y, nullptr);
			LineTo(hDC, m_vDrawPointWheelLine[0].x + 30, m_vDrawPointWheelLine[0].y - 20);
			LineTo(hDC, m_vDrawPointWheelLine[0].x - 30, m_vDrawPointWheelLine[0].y - 60);
			LineTo(hDC, m_vDrawPointWheelLine[0].x + 30, m_vDrawPointWheelLine[0].y - 100);

			MoveToEx(hDC, m_vDrawPointWheelLine[2].x, m_vDrawPointWheelLine[2].y, nullptr);
			LineTo(hDC, m_vDrawPointWheelLine[2].x + 30, m_vDrawPointWheelLine[2].y - 20);
			LineTo(hDC, m_vDrawPointWheelLine[2].x - 30, m_vDrawPointWheelLine[2].y - 60);
			LineTo(hDC, m_vDrawPointWheelLine[2].x + 30, m_vDrawPointWheelLine[2].y - 100);
		}
		//¹Ùµð
		MoveToEx(hDC, m_vDrawPointBody[0].x, m_vDrawPointBody[0].y, nullptr);
		for (int i = 1; i < 4; ++i)
		{
			LineTo(hDC, m_vDrawPointBody[i].x, m_vDrawPointBody[i].y);
		}
		LineTo(hDC, m_vDrawPointBody[0].x, m_vDrawPointBody[0].y);
		for (int i = 4; i < 10; ++i)
		{
			LineTo(hDC, m_vDrawPointBody[i].x, m_vDrawPointBody[i].y);
		}
		LineTo(hDC, m_vDrawPointBody[6].x, m_vDrawPointBody[6].y);
		LineTo(hDC, m_vDrawPointBody[0].x, m_vDrawPointBody[0].y);
		//½ÃÆ®m_vDrawPointSheet
		MoveToEx(hDC, m_vDrawPointSheet[3].x, m_vDrawPointSheet[3].y, nullptr);
		for (int i = 0; i < 4; ++i)
		{
			LineTo(hDC, m_vDrawPointSheet[i].x, m_vDrawPointSheet[i].y);
		}
		//ÈÙ
		MoveToEx(hDC, m_vDrawPointWheel[3].x, m_vDrawPointWheel[3].y, nullptr);
		for (int i = 0; i < 4; ++i)
		{
			LineTo(hDC, m_vDrawPointWheel[i].x, m_vDrawPointWheel[i].y);
		}
		MoveToEx(hDC, m_vDrawPointWheel[7].x, m_vDrawPointWheel[7].y, nullptr);
		for (int i = 4; i < 8; ++i)
		{
			LineTo(hDC, m_vDrawPointWheel[i].x, m_vDrawPointWheel[i].y);
		}

		MoveToEx(hDC, m_vDrawPointWheel[0].x, m_vDrawPointWheel[0].y, nullptr);
		LineTo(hDC, m_vDrawPointWheelLine[0].x, m_vDrawPointWheelLine[0].y);
		LineTo(hDC, m_vDrawPointWheelLine[1].x, m_vDrawPointWheelLine[1].y);
		LineTo(hDC, m_vDrawPointWheel[1].x, m_vDrawPointWheel[1].y);

		MoveToEx(hDC, m_vDrawPointWheel[4].x, m_vDrawPointWheel[4].y, nullptr);
		LineTo(hDC, m_vDrawPointWheelLine[2].x, m_vDrawPointWheelLine[2].y);
		LineTo(hDC, m_vDrawPointWheelLine[3].x, m_vDrawPointWheelLine[3].y);
		LineTo(hDC, m_vDrawPointWheel[5].x, m_vDrawPointWheel[5].y);

		//¸öÃ¼?
		MoveToEx(hDC, m_vDrawPointBody[0].x, m_vDrawPointBody[0].y, nullptr);
		LineTo(hDC, m_tInfo.vPos.x - 30, m_tInfo.vPos.y - 100);
		MoveToEx(hDC, m_vDrawPointBody[6].x, m_vDrawPointBody[6].y, nullptr);
		LineTo(hDC, m_tInfo.vPos.x + 30, m_tInfo.vPos.y - 100);

		//±Í
		Ellipse(hDC, m_vDrawPointEar[0].x - 30, m_vDrawPointEar[0].y - 30, m_vDrawPointEar[0].x + 30, m_vDrawPointEar[0].y + 30);
		Ellipse(hDC, m_vDrawPointEar[1].x - 30, m_vDrawPointEar[1].y - 30, m_vDrawPointEar[1].x + 30, m_vDrawPointEar[1].y + 30);

		Ellipse(hDC, m_vHeadPos.x - 50, m_vHeadPos.y - 50, m_vHeadPos.x + 50, m_vHeadPos.y + 50);
	}
	

}

void CPlayerZ::Release()
{
}

void CPlayerZ::OnCollision()
{
	m_bInvincibillity = true;
	m_dwBlinkTime = m_dwInvTime = GetTickCount();
	CObjMgr::Get_Instance()->Less_UI(UI_HEART);
	CStatus::Get_Instance()->Add_Hp(-1);
	if (CStatus::Get_Instance()->Get_Hp() <= 0)
	{
		m_bIsBroken = true;
	}

}

void CPlayerZ::Key_Input()
{
	if (CKeyMgr::GetInstance()->KeyPressing(VK_LEFT))
	{
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
		if (m_fAngle > -20.f)
		{
			m_fAngle -= 1.f;
		}
		
		m_bPeekNow = true;
	}

	if (CKeyMgr::GetInstance()->KeyPressing(VK_RIGHT))
	{
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		if (m_fAngle < 20.f)
		{
			m_fAngle += 1.f;
		}
		m_bPeekNow = true;
	}

	if (CKeyMgr::GetInstance()->KeyUp(VK_LEFT))
	{
		m_bPeekNow = false;
	}
	
	if (CKeyMgr::GetInstance()->KeyUp(VK_RIGHT))
	{
		m_bPeekNow = false;
	}

}

void CPlayerZ::Update_DrawPoint()
{
	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 2.f, 2.f, 1.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale  * matTrans;

	for (int i = 0; i < 8; ++i)
	{
		m_vDrawPointWheel[i] = m_vOriginDrawPointWheel[i];
	}
	for (int i = 0; i < 8; ++i)
	{
		D3DXVec3TransformCoord(&m_vDrawPointWheel[i], &m_vDrawPointWheel[i], &m_tInfo.matWorld);
	}

	for (int i = 0; i < 4; ++i)
	{
		m_vDrawPointWheelLine[i] = m_vOriginDrawPointWheelLine[i];
	}
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vDrawPointWheelLine[i], &m_vDrawPointWheelLine[i], &m_tInfo.matWorld);
	}
	
	for (int i = 0; i < 10; ++i)
	{
		m_vDrawPointBody[i] = m_vOriginDrawPointBody[i];
	}
	for (int i = 0; i < 10; ++i)
	{
		D3DXVec3TransformCoord(&m_vDrawPointBody[i], &m_vDrawPointBody[i], &m_tInfo.matWorld);
	}

	for (int i = 0; i < 4; ++i)
	{
		m_vDrawPointSheet[i] = m_vOriginDrawPointSheet[i];
	}
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vDrawPointSheet[i], &m_vDrawPointSheet[i], &m_tInfo.matWorld);
	}

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_vHeadPos.x, m_vHeadPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 2; ++i)
	{
		m_vDrawPointEar[i] = m_vOriginDrawPointEar[i];
	}
	for (int i = 0; i < 2; ++i)
	{
		D3DXVec3TransformCoord(&m_vDrawPointEar[i], &m_vDrawPointEar[i], &m_tInfo.matWorld);
	}




}

void CPlayerZ::FirstPoint()
{
	//ÈÙ
	m_vDrawPointWheel[0] = { -50.f, 16.f, 0.f };
	m_vDrawPointWheel[1] = { -26.f, 16.f, 0.f };
	m_vDrawPointWheel[2] = { -26.f, 40.f, 0.f };
	m_vDrawPointWheel[3] = { -50.f, 40.f, 0.f };

	m_vDrawPointWheel[4] = { 26.f, 16.f, 0.f };
	m_vDrawPointWheel[5] = { 50.f, 16.f, 0.f };
	m_vDrawPointWheel[6] = { 50.f, 40.f, 0.f };
	m_vDrawPointWheel[7] = { 26.f, 40.f, 0.f };

	for (int i = 0; i < 8; ++i)
	{
		m_vOriginDrawPointWheel[i] = m_vDrawPointWheel[i];
	}
	
	m_vDrawPointWheelLine[0] = { -40.f, -18.f , 0.f };
	m_vDrawPointWheelLine[1] = { -22.f, -18.f , 0.f };

	m_vDrawPointWheelLine[2] = { 22.f, -18.f , 0.f };
	m_vDrawPointWheelLine[3] = { 40.f, -18.f , 0.f };

	for (int i = 0; i < 4; ++i)
	{
		m_vOriginDrawPointWheelLine[i] = m_vDrawPointWheelLine[i];
	}

	//¹Ùµð
	m_vDrawPointBody[0] = { -25.f, 10.f, 0.f };
	m_vDrawPointBody[1]= { -42.f, 10.f, 0.f };
	m_vDrawPointBody[2] = { -40.f, -16.f, 0.f };
	m_vDrawPointBody[3] = { -23.f, -16.f, 0.f };

	m_vDrawPointBody[4] = { -25.f, 40.f, 0.f };
	m_vDrawPointBody[5] = { 25.f, 40.f, 0.f };
	m_vDrawPointBody[6] = { 25.f, 10.f, 0.f };

	m_vDrawPointBody[7] = { 42.f, 10.f, 0.f };
	m_vDrawPointBody[8] = { 40.f, -16.f, 0.f };
	m_vDrawPointBody[9] = { 23.f, -16.f, 0.f };

	for (int i = 0; i < 10; ++i)
	{
		m_vOriginDrawPointBody[i] = m_vDrawPointBody[i];
	}

	//½ÃÆ®
	m_vDrawPointSheet[0] = { -18.f, -12.f, 0.f };
	m_vDrawPointSheet[1] = { 18.f, -12.f, 0.f };
	m_vDrawPointSheet[2] = { 18.f, 8.f, 0.f };
	m_vDrawPointSheet[3] = { -18.f, 8.f, 0.f };
	for (int i = 0; i < 4; ++i)
	{
		m_vOriginDrawPointSheet[i] = m_vDrawPointSheet[i];
	}

	//±Í
	m_vDrawPointEar[0] = { -45, -15, 0 };
	m_vDrawPointEar[1] = { 45, -15, 0 };

	for (int i = 0; i < 2; ++i)
	{
		m_vOriginDrawPointEar[i] = m_vDrawPointEar[i];
	}
	
}
