#include "stdafx.h"
#include "MonsterX1.h"

CMonsterX1::CMonsterX1()
	: m_fSizeUp(0.f)
{
}

CMonsterX1::~CMonsterX1()
{
}

void CMonsterX1::Initialize()
{
	m_tInfo.fRadius = 30.f;

	m_tInfo.vPos = {900.f, 450.f, 0.f};
	m_vOriginPos = m_tInfo.vPos;

	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_tInfo.vDir = { -1.f, 0.f, 0.f };
	m_fSpeed = 5.f;

	m_fSizeUp = 1.f;

    m_vPoint[0] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y, 0.f };
    m_vPoint[1] = { m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y - 8.f, 0.f };
    m_vPoint[2] = { m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y - 5.f, 0.f };
    m_vPoint[3] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y - 5.f, 0.f };
    m_vPoint[4] = { m_tInfo.vPos.x + 55.f, m_tInfo.vPos.y - 8.f, 0.f };
    m_vPoint[5] = { m_tInfo.vPos.x + 70.f, m_tInfo.vPos.y - 8.f, 0.f };

	m_vPoint[6] = { m_tInfo.vPos.x + 60.f, m_tInfo.vPos.y, 0.f };
	m_vPoint[7] = { m_tInfo.vPos.x + 70.f, m_tInfo.vPos.y + 8.f, 0.f };
	m_vPoint[8] = { m_tInfo.vPos.x + 55.f, m_tInfo.vPos.y + 8.f, 0.f };
	m_vPoint[9] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y + 5.f, 0.f };
	m_vPoint[10] = { m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y + 5.f, 0.f };
	m_vPoint[11] = { m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y + 8.f, 0.f };

    for (int i = 0; i < 12; ++i)
        m_vOriginPoint[i] = m_vPoint[i];
}

int CMonsterX1::Update()
{
	if (m_bDead == true)
	{
		return OBJ_DEAD;
	}

	D3DXMATRIX		matScale, matTrans;

	D3DXMatrixScaling(&matScale, m_fSizeUp, m_fSizeUp, m_fSizeUp);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	for (int i = 0; i < 12; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= m_vOriginPos;

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

	if (m_dwInvTime + 10 < GetTickCount())
	{
		if (m_fSizeUp < 2.f)
		{
			m_fSizeUp += 0.1f;
		}
		else if (m_fSizeUp >= 2.f)
		{
			m_fSizeUp = 1.f;
		}

		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
		m_dwInvTime = GetTickCount();
	}

	return 0;
}

void CMonsterX1::Late_Update()
{
	if (m_tInfo.vPos.x < -100.f)
	{
		m_bDead = true;
	}

}

void CMonsterX1::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 12; ++i)
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

	LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);
}

void CMonsterX1::Release()
{
}

void CMonsterX1::OnCollision()
{
	m_bDead = true;
}
