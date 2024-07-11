#include "stdafx.h"
#include "BulletX.h"

CBulletX::CBulletX()
{
}

CBulletX::~CBulletX()
{
}

void CBulletX::Initialize()
{
	//m_tInfo.vPos = { 900.f, 450.f, 0.f };
	m_vOriginPos = m_tInfo.vPos;

	float fLength = sqrt(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;

	//m_tInfo.vLook = { 1.f, -1.f, 0.f };
	//m_tInfo.vDir = { -1.f, 0.f, 0.f };
	m_tInfo.vLook = m_tInfo.vDir;

	m_fSpeed = 5.f;
	m_fAngle = 0.f;

	m_vPoint[0] = { m_tInfo.vPos.x, m_tInfo.vPos.y - 30.f, 0.f };

	m_vPoint[1] = { m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y, 0.f };
	m_vPoint[4] = { m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y + 20.f, 0.f };

	m_vPoint[5] = { m_tInfo.vPos.x, m_tInfo.vPos.y + 5.f, 0.f };

	m_vPoint[6] = { m_tInfo.vPos.x + 20.f, m_tInfo.vPos.y + 20.f, 0.f };
	m_vPoint[7] = { m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y, 0.f };
	m_vPoint[8] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[9] = { m_tInfo.vPos.x + 5.f, m_tInfo.vPos.y - 10.f, 0.f };

	for (int i = 0; i < 10; ++i)
		m_vOriginPoint[i] = m_vPoint[i];
}

int CBulletX::Update()
{
#pragma region Key_Input 대신

	//D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	m_fAngle += D3DX_PI * 3.f;

#pragma endregion

	D3DXMATRIX		matRotZ, matTrans;

	// 회전은 각도만큼 곱하고
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));

	// 이동은 위에서 변화한 위치값으로 이동한다
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	// 크기, 자전, 이동
	m_tInfo.matWorld = matRotZ * matTrans;

	for (int i = 0; i < 10; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= m_vOriginPos;

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	return 0;
}

void CBulletX::Late_Update()
{
}

void CBulletX::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 10; ++i)
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

	LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);
}

void CBulletX::Release()
{
}

void CBulletX::OnCollision()
{
}
