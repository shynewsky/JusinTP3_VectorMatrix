#include "stdafx.h"
#include "MonsterX2.h"

CMonsterX2::CMonsterX2()
	: m_fBodyAngle(0.f), m_fWingSpeed(0.f)
{
}

CMonsterX2::~CMonsterX2()
{
}

void CMonsterX2::Initialize()
{
	m_tInfo.fRadius = 20.f;

	m_tInfo.vPos = { 900.f, 300.f, 0.f };
	m_vOriginPos = m_tInfo.vPos;

	m_tInfo.vLook = { -1.f, -1.f, 0.f };
	m_tInfo.vDir = { -1.f, 0.f, 0.f };

	m_fSpeed = D3DX_PI / 180.f * 10.f;
	m_fBodyAngle = D3DX_PI / 180.f * 0.f;

	// 회전공식을 사용했기 때문에, 회전 행렬을 곱할필요가 없어졌따
	// 공전행렬과 부모행렬을 사용하기 위해서는, 날개를 몸통과 다른 클래스로 나눠서 해야한다

	m_fWingSpeed = D3DX_PI / 180.f * 10.f;

	m_fLWingAngle = - D3DX_PI / 180.f * 150.f;
	m_vLWing.x = m_tInfo.vPos.x + 10.f * cos(m_fLWingAngle) - 10.f * sin(m_fLWingAngle);
	m_vLWing.y = m_tInfo.vPos.y + 10.f * cos(m_fLWingAngle) + 10.f * sin(m_fLWingAngle);
	m_vLWing.z = 0.f;

	m_fRWingAngle = - D3DX_PI / 180.f * 120.f;
	m_vRWing.x = m_tInfo.vPos.x + 10.f * cos(m_fRWingAngle) - 10.f * sin(m_fRWingAngle);
	m_vRWing.y = m_tInfo.vPos.y + 10.f * cos(m_fRWingAngle) + 10.f * sin(m_fRWingAngle);
	m_vRWing.z = 0.f;

}

int CMonsterX2::Update()
{
	if (m_bDead == true)
	{
		return OBJ_DEAD;
	}

#pragma region 몸체

	if (m_dwInvTime + 10 < GetTickCount())
	{
		m_fBodyAngle += m_fSpeed;
		m_tInfo.vPos.x += 5 * m_tInfo.vDir.x;
		m_tInfo.vPos.y += 5.f * sin(m_fBodyAngle);

		m_fLWingAngle -= m_fWingSpeed;
		m_fRWingAngle += m_fWingSpeed;

		if (m_fLWingAngle < -D3DX_PI / 180.f * 160.f || m_fLWingAngle > -D3DX_PI / 180.f * 140.f ||
			m_fRWingAngle < -D3DX_PI / 180.f * 130.f || m_fRWingAngle > -D3DX_PI / 180.f * 110.f)
		{
			m_fWingSpeed *= -1.f;
		}

		m_dwInvTime = GetTickCount();
	}

	D3DXMATRIX		matTrans;

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;

	m_tInfo.vPos = m_vOriginPos;
	m_tInfo.vPos -= m_vOriginPos;

	D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &m_tInfo.matWorld);

#pragma endregion

#pragma region 날개

	m_vLWing.x = m_tInfo.vPos.x + 10.f * cos(m_fLWingAngle) - 10.f * sin(m_fLWingAngle);
	m_vLWing.y = m_tInfo.vPos.y + 10.f * cos(m_fLWingAngle) + 10.f * sin(m_fLWingAngle);
	m_vLWing.z = 0.f;

	m_vRWing.x = m_tInfo.vPos.x + 10.f * cos(m_fRWingAngle) - 10.f * sin(m_fRWingAngle);
	m_vRWing.y = m_tInfo.vPos.y + 10.f * cos(m_fRWingAngle) + 10.f * sin(m_fRWingAngle);
	m_vRWing.z = 0.f;

#pragma endregion





	return 0;
}

void CMonsterX2::Late_Update()
{
	if (m_tInfo.vPos.x < -100.f)
	{
		m_bDead = true;
	}
}

void CMonsterX2::Render(HDC hDC)
{
	Ellipse(hDC,
		m_vLWing.x - 10.f,
		m_vLWing.y - 10.f,
		m_vLWing.x + 10.f,
		m_vLWing.y + 10.f);

	Ellipse(hDC,
		m_tInfo.vPos.x - 20.f,
		m_tInfo.vPos.y - 10.f,
		m_tInfo.vPos.x + 20.f,
		m_tInfo.vPos.y + 10.f);

 	Ellipse(hDC,
		m_vRWing.x - 10.f,
		m_vRWing.y - 10.f,
		m_vRWing.x + 10.f,
		m_vRWing.y + 10.f);
}

void CMonsterX2::Release()
{
}

void CMonsterX2::OnCollision()
{
	m_bDead = true;
}
