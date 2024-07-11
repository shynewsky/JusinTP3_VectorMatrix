#include "stdafx.h"
#include "FlagY.h"

CFlagY::CFlagY()
	: m_fDistance(0), m_iScore(0), m_bPassed(false), m_bMove(false), m_iDir(0), m_fSide(0), m_fMaxSide(0)
{
	ZeroMemory(&m_vLPoints, sizeof(D3DXVECTOR3) * 4);
	ZeroMemory(&m_vRPoints, sizeof(D3DXVECTOR3) * 4);

	ZeroMemory(&m_vOriginLPoints, sizeof(D3DXVECTOR3) * 4);
	ZeroMemory(&m_vOriginRPoints, sizeof(D3DXVECTOR3) * 4);

	ZeroMemory(&m_vScale, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vAngle, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vStartPoint, sizeof(D3DXVECTOR3));

	D3DXMatrixIdentity(&m_tInfo.matWorld);
}

CFlagY::CFlagY(float _fX, float _fY)
	: CFlagY()
{
	m_vStartPoint.x = _fX;
	m_vStartPoint.y = _fY;
	m_vStartPoint.z = 0.f;
}

CFlagY::~CFlagY()
{
	Release();
}

void CFlagY::Initialize()
{
	m_tInfo.vPos = m_vStartPoint;
	m_tInfo.vLook = { 0.f, 1.f, 0.f };
	m_tInfo.vDir = { 0.f, 1.f, 0.f };

	m_fDistance = 70.f;

	m_vLPoints[0] = { m_tInfo.vPos.x - 5.f - m_fDistance, m_tInfo.vPos.y - 20.f, 0.f };
	m_vLPoints[1] = { m_tInfo.vPos.x + 5.f - m_fDistance, m_tInfo.vPos.y - 20.f, 0.f };
	m_vLPoints[2] = { m_tInfo.vPos.x + 5.f - m_fDistance, m_tInfo.vPos.y + 20.f, 0.f };
	m_vLPoints[3] = { m_tInfo.vPos.x - 5.f - m_fDistance, m_tInfo.vPos.y + 20.f, 0.f };
											
	m_vRPoints[0] = { m_tInfo.vPos.x - 5.f + m_fDistance, m_tInfo.vPos.y - 20.f, 0.f };
	m_vRPoints[1] = { m_tInfo.vPos.x + 5.f + m_fDistance, m_tInfo.vPos.y - 20.f, 0.f };
	m_vRPoints[2] = { m_tInfo.vPos.x + 5.f + m_fDistance, m_tInfo.vPos.y + 20.f, 0.f };
	m_vRPoints[3] = { m_tInfo.vPos.x - 5.f + m_fDistance, m_tInfo.vPos.y + 20.f, 0.f };

	for (int i = 0; i < 4; ++i)
	{
		m_vOriginLPoints[i] = m_vLPoints[i];
		m_vOriginRPoints[i] = m_vRPoints[i];
	} 

	m_bDead = false;
	m_fSpeed = 3.f;
	m_vScale = { 1.f, 1.f, 1.f };
	m_vAngle = { 0, 0, 0.f };
}

int CFlagY::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	m_tInfo.vPos.y -= m_tInfo.vDir.y * m_fSpeed;
	m_tInfo.vPos.x += m_fSide;

	D3DXMATRIX matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationZ(&matRotZ, m_vAngle.z);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vLPoints[i] = m_vOriginLPoints[i];
		m_vRPoints[i] = m_vOriginRPoints[i];

		m_vLPoints[i] -= m_vStartPoint;
		m_vRPoints[i] -= m_vStartPoint;

		D3DXVec3TransformCoord(&m_vLPoints[i], &m_vLPoints[i], &m_tInfo.matWorld);
		D3DXVec3TransformCoord(&m_vRPoints[i], &m_vRPoints[i], &m_tInfo.matWorld);
	}

 	return OBJ_NOEVENT;
} 

void CFlagY::Late_Update()
 {
	if (m_tInfo.vPos.y + 20.f <= 0.f)
	{
 		m_bDead = true; 
	}

	Move_Side();
}

void CFlagY::Render(HDC hDC)
{
	MoveToEx(hDC, static_cast<int>(m_vLPoints[0].x), static_cast<int>(m_vLPoints[0].y), nullptr);

	for (auto& vPoint : m_vLPoints)
	{
		LineTo(hDC, static_cast<int>(vPoint.x), static_cast<int>(vPoint.y));
	}

	LineTo(hDC, static_cast<int>(m_vLPoints[0].x), static_cast<int>(m_vLPoints[0].y));

	MoveToEx(hDC, static_cast<int>(m_vRPoints[0].x), static_cast<int>(m_vRPoints[0].y), nullptr);

	for (auto& vPoint : m_vRPoints)
	{
		LineTo(hDC, static_cast<int>(vPoint.x), static_cast<int>(vPoint.y));
	}

	LineTo(hDC, static_cast<int>(m_vRPoints[0].x), static_cast<int>(m_vRPoints[0].y));

	//TCHAR strInfo[64];
	//swprintf_s(strInfo, L"%f", m_tInfo.vPos.y);
	//TextOut(hDC, static_cast<int>(m_vRPoints[0].x), static_cast<int>(m_vRPoints[0].y), strInfo, lstrlen(strInfo));

}

void CFlagY::Release()
{
}

void CFlagY::OnCollision()
{
}

void CFlagY::Set_Distance(float _fDist)
{
	m_fDistance = _fDist;

	m_vLPoints[0] = { m_tInfo.vPos.x - 5.f - m_fDistance, m_tInfo.vPos.y - 20.f, 0.f };
	m_vLPoints[1] = { m_tInfo.vPos.x + 5.f - m_fDistance, m_tInfo.vPos.y - 20.f, 0.f };
	m_vLPoints[2] = { m_tInfo.vPos.x + 5.f - m_fDistance, m_tInfo.vPos.y + 20.f, 0.f };
	m_vLPoints[3] = { m_tInfo.vPos.x - 5.f - m_fDistance, m_tInfo.vPos.y + 20.f, 0.f };

	m_vRPoints[0] = { m_tInfo.vPos.x - 5.f + m_fDistance, m_tInfo.vPos.y - 20.f, 0.f };
	m_vRPoints[1] = { m_tInfo.vPos.x + 5.f + m_fDistance, m_tInfo.vPos.y - 20.f, 0.f };
	m_vRPoints[2] = { m_tInfo.vPos.x + 5.f + m_fDistance, m_tInfo.vPos.y + 20.f, 0.f };
	m_vRPoints[3] = { m_tInfo.vPos.x - 5.f + m_fDistance, m_tInfo.vPos.y + 20.f, 0.f };

	for (int i = 0; i < 4; ++i)
	{
		m_vOriginLPoints[i] = m_vLPoints[i];
		m_vOriginRPoints[i] = m_vRPoints[i];
	}
}

void CFlagY::Move_Side()
{
	if (m_bMove)
	{
		if (m_fSide > m_fMaxSide / 2.f || 
			m_fSide < -m_fMaxSide / 2.f)
		{
			m_iDir *= -1;
		}

		m_fSide += static_cast<float>(m_iDir) * 0.05f;
	}
}
