#include "stdafx.h"
#include "MonsterZ1.h"

CMonsterZ1::CMonsterZ1(float _X, float _Y) : m_fScale(1.f)
{
	m_tInfo.vPos = { _X, _Y, 0.f };
}

CMonsterZ1::~CMonsterZ1()
{
}

void CMonsterZ1::Initialize()
{
	
	m_tInfo.vLook = { 0.f, 1.f, 0.f };
	m_fSpeed = 2.f;
	m_tInfo.fRadius = 40.f;
	m_tInfo.vDir = { m_tInfo.vPos.x - 400, m_tInfo.vPos.y - 1125, 0.f };//400 , 1125
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);


	//기본 사각형
	m_vDrawPoint[0] = { -40.f, -40.f, 0.f };
	m_vDrawPoint[1] = { 40.f, -40.f, 0.f };
	m_vDrawPoint[2] = { 40.f, 40.f, 0.f };
	m_vDrawPoint[3] = { -40.f, 40.f, 0.f };

	if (m_tInfo.vPos.x <= 400)
	{
		m_eBoxDir = LEFT;
		m_vDrawPoint[4] = { -40.f - (m_tInfo.vDir.x * 20), -40.f + (m_tInfo.vDir.y * 20), 0.f };
		m_vDrawPoint[5] = { 40.f - (m_tInfo.vDir.x * 20), -40.f + (m_tInfo.vDir.y * 20), 0.f };
		m_vDrawPoint[6] = { 40.f - (m_tInfo.vDir.x * 20), 40.f + (m_tInfo.vDir.y * 20), 0.f };
	}
	else
	{
		m_eBoxDir = RIGHT;
		m_vDrawPoint[4] = { 40.f - (m_tInfo.vDir.x * 20), -40.f + (m_tInfo.vDir.y * 20), 0.f };
		m_vDrawPoint[5] = { -40.f - (m_tInfo.vDir.x * 20), -40.f + (m_tInfo.vDir.y * 20), 0.f };
		m_vDrawPoint[6] = { -40.f - (m_tInfo.vDir.x * 20), 40.f + (m_tInfo.vDir.y * 20), 0.f };
	}
	


	for (int i = 0; i < 7; ++i)
	{
		m_vOriginDrawPoint[i] = m_vDrawPoint[i];
	}

}

int CMonsterZ1::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	m_fScale += 0.005f;

	m_tInfo.vPos.x += m_tInfo.vDir.x * m_fSpeed;
	m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	Update_DrawPoint();

	m_tInfo.fRadius = 40.f * m_fScale;
	return OBJ_NOEVENT;
}

void CMonsterZ1::Late_Update()
{
	if (m_tInfo.vPos.y > 750.f)
	{
		m_bDead = true;
	}

}

void CMonsterZ1::Render(HDC hDC)
{
	//Ellipse(hDC, m_tInfo.vPos.x - m_tInfo.fRadius, m_tInfo.vPos.y - m_tInfo.fRadius, m_tInfo.vPos.x + m_tInfo.fRadius, m_tInfo.vPos.y + m_tInfo.fRadius);
	MoveToEx(hDC, m_vDrawPoint[3].x, m_vDrawPoint[3].y, NULL);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, m_vDrawPoint[i].x, m_vDrawPoint[i].y);
	}
	

	if (m_eBoxDir == RIGHT)
	{
		MoveToEx(hDC, m_vDrawPoint[1].x, m_vDrawPoint[1].y, NULL);
		LineTo(hDC, m_vDrawPoint[4].x, m_vDrawPoint[4].y);
		LineTo(hDC, m_vDrawPoint[5].x, m_vDrawPoint[5].y);
		LineTo(hDC, m_vDrawPoint[0].x, m_vDrawPoint[0].y);

		MoveToEx(hDC, m_vDrawPoint[5].x, m_vDrawPoint[5].y, NULL);
		LineTo(hDC, m_vDrawPoint[6].x, m_vDrawPoint[6].y);
		LineTo(hDC, m_vDrawPoint[3].x, m_vDrawPoint[3].y);
	}
	else
	{
		MoveToEx(hDC, m_vDrawPoint[0].x, m_vDrawPoint[0].y, NULL);
		LineTo(hDC, m_vDrawPoint[4].x, m_vDrawPoint[4].y);
		LineTo(hDC, m_vDrawPoint[5].x, m_vDrawPoint[5].y);
		LineTo(hDC, m_vDrawPoint[1].x, m_vDrawPoint[1].y);

		MoveToEx(hDC, m_vDrawPoint[5].x, m_vDrawPoint[5].y, NULL);
		LineTo(hDC, m_vDrawPoint[6].x, m_vDrawPoint[6].y);
		LineTo(hDC, m_vDrawPoint[2].x, m_vDrawPoint[2].y);
	}
	

}

void CMonsterZ1::Release()
{
}

void CMonsterZ1::OnCollision()
{
}

void CMonsterZ1::Update_DrawPoint()
{
	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, m_fScale, m_fScale, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 7; ++i)
	{
		m_vDrawPoint[i] = m_vOriginDrawPoint[i];
	}
	for (int i = 0; i < 7; ++i)
	{
		D3DXVec3TransformCoord(&m_vDrawPoint[i], &m_vDrawPoint[i], &m_tInfo.matWorld);
	}

}