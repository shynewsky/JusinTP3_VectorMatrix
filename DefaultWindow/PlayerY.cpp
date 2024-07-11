#include "stdafx.h"
#include "PlayerY.h"

#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Status.h"

CPlayerY::CPlayerY()
	: m_fRotSpeed(0.f), m_fHeadSize(0.f), m_bRight(false), m_iHp(0), m_bSlip(false), m_bIdle(true)
{
	// 벡터 초기화
	ZeroMemory(&m_vCar, sizeof(D3DXVECTOR3) * 4);
	ZeroMemory(&m_vOriginCar, sizeof(D3DXVECTOR3) * 4);

	ZeroMemory(&m_vHead, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vOriginHead, sizeof(D3DXVECTOR3));

	ZeroMemory(&m_vAngle, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vScale, sizeof(D3DXVECTOR3));

	// 월드 행렬 초기화 (항등행렬화)
	D3DXMatrixIdentity(&m_tInfo.matWorld);
}

CPlayerY::~CPlayerY()
{
	Release();
}

void CPlayerY::Initialize()
{
	m_tInfo.vPos = { 400.f, 100.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_fHeadSize = 10.f;

	m_vCar[0] = { m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y - 25.f, 0.f };
	m_vCar[1] = { m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y - 25.f, 0.f };
	m_vCar[2] = { m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y + 25.f, 0.f };
	m_vCar[3] = { m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y + 25.f, 0.f };

	for (int i = 0; i < 4; ++i)
	{
		m_vOriginCar[i] = m_vCar[i];
	}

	m_vHead = { m_tInfo.vPos.x, m_tInfo.vPos.y + -10.f, 0.f };
	m_vOriginHead = m_vHead;

	m_bDead = false;
	m_iHp = 3;
	m_fSpeed = 5.f;
	m_fRotSpeed = 1.5f;
	m_vScale = { 1.f, 1.f, 1.f };
	m_vAngle = { 0, 0, 0.f };
}

int CPlayerY::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	if (m_tInfo.vPos.x <= 90.f ||
		m_tInfo.vPos.x >= 710.f)
	{
		m_bSlip = true;
	}
	else
	{
		Key_Input();
	}

	D3DXMATRIX matScale, matBodyRotZ, matTrans;

	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationZ(&matBodyRotZ, m_vAngle.z);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matBodyRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vCar[i] = m_vOriginCar[i];
		m_vCar[i] -= {400.f, 100.f, 0.f};
		D3DXVec3TransformCoord(&m_vCar[i], &m_vCar[i], &m_tInfo.matWorld);
	}

	m_vHead = m_vOriginHead;
	m_vHead -= {400.f, 100.f, 0.f};
	D3DXVec3TransformCoord(&m_vHead, &m_vHead, &m_tInfo.matWorld);

	return OBJ_NOEVENT;
}

void CPlayerY::Late_Update()
{
	if (m_bSlip)
	{
		Slip();
	}
	else if (m_bIdle)
	{
		Move();
	}
	else
	{
		Rotation();
		Move();
	}
}

void CPlayerY::Render(HDC hDC)
{
	MoveToEx(hDC, static_cast<int>(m_vCar[0].x), static_cast<int>(m_vCar[0].y), nullptr);

	for (auto& vPoint : m_vCar)
	{
		LineTo(hDC, static_cast<int>(vPoint.x), static_cast<int>(vPoint.y));
	}
	LineTo(hDC, static_cast<int>(m_vCar[0].x), static_cast<int>(m_vCar[0].y));

	Ellipse(hDC, 
		static_cast<int>(m_vHead.x - m_fHeadSize + ((1.f - m_vScale.x) * 10.f)),
		static_cast<int>(m_vHead.y - m_fHeadSize + ((1.f - m_vScale.x) * 10.f)),
		static_cast<int>(m_vHead.x + m_fHeadSize - ((1.f - m_vScale.x) * 10.f)),
		static_cast<int>(m_vHead.y + m_fHeadSize - ((1.f - m_vScale.x) * 10.f)));


	//TCHAR strBuffer[64];

	//swprintf_s(strBuffer, L"%f", m_tInfo.vPos.x);
	//TextOut(hDC, 0, 20, strBuffer, lstrlen(strBuffer));
	//
	//swprintf_s(strBuffer, L"%f", m_tInfo.vPos.y);
	//TextOut(hDC, 0, 40, strBuffer, lstrlen(strBuffer));
}

void CPlayerY::Release()
{
}

void CPlayerY::OnCollision()
{
	CStatus::Get_Instance()->Add_Hp(1);
	CObjMgr::Get_Instance()->Add_Heart_UI();
}

bool CPlayerY::Slip()
{
	if (m_tInfo.vPos.x >= 710.f)
	{
		//m_vAngle.z += D3DXToRadian(10.f);
		m_tInfo.vPos.x += cosf(D3DXToRadian(60.f)) * m_fSpeed;
		m_tInfo.vPos.y -= sinf(D3DXToRadian(60.f)) * m_fSpeed;
	}
	else if(m_tInfo.vPos.x <= 90.f)
	{
		//m_vAngle.z -= D3DXToRadian(10.f);
		m_tInfo.vPos.x -= cosf(D3DXToRadian(60.f)) * m_fSpeed;
		m_tInfo.vPos.y -= sinf(D3DXToRadian(60.f)) * m_fSpeed;
	}
	m_vScale.x -= 0.05f;
	m_vScale.y -= 0.05f;
	m_vScale.z -= 0.05f;

	return true;
}

void CPlayerY::Key_Input()
{
	if (CKeyMgr::GetInstance()->KeyUp(VK_SPACE))
	{
		if (m_bIdle)
		{
			m_bIdle = false;
		}

		if (CStatus::Get_Instance()->Get_Hp() > 0)
		{
			CStatus::Get_Instance()->Add_Hp(-1);
			CObjMgr::Get_Instance()->Less_UI(UI_HEART);
			Set_Right(!m_bRight); 
		}
	}
}

void CPlayerY::Rotation()
{
	if (m_bRight)
	{
		m_vAngle.z += D3DXToRadian(m_fRotSpeed);
		if (m_vAngle.z >= D3DXToRadian(30.f))
		{
			m_vAngle.z = D3DXToRadian(30.f);
		}
	}
	else
	{
		m_vAngle.z -= D3DXToRadian(m_fRotSpeed);
		if (m_vAngle.z <= D3DXToRadian(-30.f))
		{
			m_vAngle.z = D3DXToRadian(-30.f);
		}
	}

	if (abs(D3DXToDegree(m_vAngle.z)) < 30.f)
	{
		m_fSpeed -= 0.1f;
		if (m_fSpeed < 3.f)
		{
			m_fSpeed = 3.f;
		}
	}
	else
	{
		m_fSpeed += 0.1f;
		if (m_fSpeed > 5.f)
		{
			m_fSpeed = 5.f;
		}
	}
}

void CPlayerY::Move()
{
	if (m_vAngle.z > 0.f)
	{
		m_tInfo.vPos.x -= cosf(m_vAngle.z) * m_fSpeed;
	}

	if (m_vAngle.z < 0.f)
	{
		m_tInfo.vPos.x += cosf(m_vAngle.z) * m_fSpeed;
	}
}