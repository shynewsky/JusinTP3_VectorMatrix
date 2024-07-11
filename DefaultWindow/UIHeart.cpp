#include "stdafx.h"
#include "UIHeart.h"

CUIHeart::CUIHeart(float _X, float _Y)
{
	m_tInfo.vPos.x = _X;
	m_tInfo.vPos.y = _Y;
	m_tInfo.vPos.z = 0.f;

}

CUIHeart::~CUIHeart()
{
}

void CUIHeart::Initialize()
{
	m_vDrawPoint[0] = { 0.f, 10.f, 0.f };
	m_vDrawPoint[1] = { 14.f, -2.f, 0.f };
	m_vDrawPoint[2] = { 14.f, -10.f, 0.f };
	m_vDrawPoint[3] = { 10.f, -15.f, 0.f };
	m_vDrawPoint[4] = { 5.f, -15.f, 0.f };
	m_vDrawPoint[5] = { 0.f, -10.f, 0.f };
	m_vDrawPoint[6] = { -5.f, -15.f, 0.f };
	m_vDrawPoint[7] = { -10.f, -15.f, 0.f };
	m_vDrawPoint[8] = { -14.f, -10.f, 0.f };
	m_vDrawPoint[9] = { -14.f, -2.f, 0.f };
	for (int i = 0; i < 10; ++i)
	{
		m_vOriginDrawPoint[i] = m_vDrawPoint[i];
	}
	Update_DrawPoint();
}

int CUIHeart::Update()
{
	return OBJ_NOEVENT;
}

void CUIHeart::Late_Update()
{
	Update_DrawPoint();
}

void CUIHeart::Render(HDC hDC)
{
	MoveToEx(hDC, m_vDrawPoint[9].x, m_vDrawPoint[9].y, NULL);
	for (int i = 0; i < 10; ++i)
	{
		LineTo(hDC, m_vDrawPoint[i].x, m_vDrawPoint[i].y);
	}
}

void CUIHeart::Release()
{
}

void CUIHeart::OnCollision()
{
}

void CUIHeart::Update_DrawPoint()
{
	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 10; ++i)
	{
		m_vDrawPoint[i] = m_vOriginDrawPoint[i];
	}
	for (int i = 0; i < 10; ++i)
	{
		D3DXVec3TransformCoord(&m_vDrawPoint[i], &m_vDrawPoint[i], &m_tInfo.matWorld);
	}

}