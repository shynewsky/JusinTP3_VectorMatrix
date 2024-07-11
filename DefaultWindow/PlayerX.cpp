#include "stdafx.h"
#include "PlayerX.h"
#include "KeyMgr.h"

#include "BulletX.h"
#include "ObjMgr.h"
#include "Status.h"
#include "SceneMgr.h"

CPlayerX::CPlayerX()
    : m_bJump(false), m_fPower(0.f), m_fTime(0.f)
    , m_fCarAngle(0.f), m_fPosinAngle(0.f), m_fJumpAngle(0.f)
    , m_dwDead(0.f)
{
}

CPlayerX::~CPlayerX()
{
}

void CPlayerX::Initialize()
{
    m_tInfo.fRadius = 50.f;

    m_tInfo.vPos = { 150.f, 450.f, 0.f };
    m_vOriginPos = m_tInfo.vPos;

    m_tInfo.vLook = { 1.f, 0.f, 0.f }; // 오른쪽을 바라보고 있다
    m_tInfo.vDir = { 1.f, 0.f, 0.f };
    m_fSpeed = 5.f;

    m_fPower = 18.f;

#pragma region 차 몸체

    m_vPoint[0] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y - 30.f, 0.f };
    m_vPoint[1] = { m_tInfo.vPos.x - 40.f, m_tInfo.vPos.y - 25.f, 0.f };
    m_vPoint[2] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y - 10.f, 0.f };
    m_vPoint[3] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y + 5.f, 0.f };
    m_vPoint[4] = { m_tInfo.vPos.x - 45.f, m_tInfo.vPos.y + 10.f, 0.f };
    m_vPoint[5] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y + 20.f, 0.f };

    m_vPoint[6] = { m_tInfo.vPos.x + 45.f, m_tInfo.vPos.y + 20.f, 0.f };
    m_vPoint[7] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y + 15.f, 0.f };
    m_vPoint[8] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y + 5.f, 0.f };
    m_vPoint[9] = { m_tInfo.vPos.x + 45.f, m_tInfo.vPos.y - 10.f, 0.f };
    m_vPoint[10] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y - 25.f, 0.f };
    m_vPoint[11] = { m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - 28.f, 0.f };

    for (int i = 0; i < 12; ++i)
        m_vOriginPoint[i] = m_vPoint[i];    // 기준값 + 상대좌표 --> 초기값으로 저장 (절대좌표로 저장됨)

#pragma endregion

#pragma region 차 바퀴

    m_vWheel[0] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y + 20.f, 0.f };
    m_vWheel[1] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y + 20.f, 0.f };

    for (int i = 0; i < 2; ++i)
        m_vOriginWheel[i] = m_vWheel[i];     // 기준값 + 상대좌표 --> 초기값으로 저장 (절대좌표로 저장됨)

#pragma endregion

#pragma region 포신

    m_vGunPoint = { m_tInfo.vPos.x + 100.f, m_tInfo.vPos.y, 0.f };
    m_vOriginGunPoint = m_vGunPoint;

#pragma endregion

#pragma region 눈

    m_vEye = { m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - 10.f, 0.f };
    m_vOriginEye = m_vEye;

#pragma endregion

#pragma region 귀

    m_vEar[0] = { m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - 28.f, 0.f };
    m_vEar[1] = { m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - 35.f, 0.f };
    m_vEar[2] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y - 38.f, 0.f };
    m_vEar[3] = { m_tInfo.vPos.x + 32.f, m_tInfo.vPos.y - 30.f, 0.f };
    m_vEar[4] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y - 25.f, 0.f };

    for (int i = 0; i < 5; ++i)
        m_vOriginEar[i] = m_vEar[i];     // 기준값 + 상대좌표 --> 초기값으로 저장 (절대좌표로 저장됨)

#pragma endregion


}

int CPlayerX::Update()
{
    if (m_bDead)
    {
        if (m_dwDead + 2000.f <= GetTickCount())
        {
            return OBJ_DEAD;
        }
        
    }

    Key_Input();

    D3DXVECTOR3 vTemp{}; // 비어있는 구조체 선언

#pragma region 차 몸체

    for (int i = 0; i < 12; ++i)
    {
        vTemp = m_vOriginPoint[i]; // 처음에 설정한 절대좌표를 받아온다
        vTemp -= m_vOriginPos; // (0,0)으로 평행이동
        // (0,0)으로 이동하지 않으면 cos sin 공식이 더 복잡해지기 때문

        // 회전공식 : x 좌표 = x * cosA - y * sinA
        m_vPoint[i].x = vTemp.x * cos(m_fCarAngle) - vTemp.y * sin(m_fCarAngle);
        // 회전공식 : y 좌표 = x * sinA + y * cosA
        m_vPoint[i].y = vTemp.x * sin(m_fCarAngle) + vTemp.y * cos(m_fCarAngle);

        // ----------- 회전끝 -----------------------

        m_vPoint[i] += m_tInfo.vPos; // (0,0)에서 원하는 지점으로 이동

        // ----------- 이동끝 -----------------------
    }

#pragma endregion

#pragma region 차 바퀴

    for (int i = 0; i < 2; ++i)
    {
        vTemp = m_vOriginWheel[i];
        vTemp -= m_vOriginPos;

        m_vWheel[i].x = vTemp.x * cos(m_fCarAngle) - vTemp.y * sin(m_fCarAngle);
        m_vWheel[i].y = vTemp.x * sin(m_fCarAngle) + vTemp.y * cos(m_fCarAngle);

        m_vWheel[i] += m_tInfo.vPos;
    }

#pragma endregion

#pragma region 포신

    vTemp = m_vOriginGunPoint;
    vTemp -= m_vOriginPos;

    m_vGunPoint.x = (vTemp.x * cos(m_fCarAngle) - vTemp.y * sin(m_fCarAngle))
        * cos(m_fPosinAngle * (D3DX_PI / 180.f));
    m_vGunPoint.y = (vTemp.x * sin(m_fCarAngle) + vTemp.y * cos(m_fCarAngle))
        - 100.f * sin(m_fPosinAngle * (D3DX_PI / 180.f));

    m_vGunPoint += m_tInfo.vPos;

#pragma endregion

#pragma region 눈

    vTemp = m_vOriginEye;
    vTemp -= m_vOriginPos;

    m_vEye.x = vTemp.x * cos(m_fCarAngle) - vTemp.y * sin(m_fCarAngle);
    m_vEye.y = vTemp.x * sin(m_fCarAngle) + vTemp.y * cos(m_fCarAngle);

    m_vEye += m_tInfo.vPos;

#pragma endregion

#pragma region 귀

    for (int i = 0; i < 5; ++i)
    {
        vTemp = m_vOriginEar[i];
        vTemp -= m_vOriginPos;

        m_vEar[i].x = vTemp.x * cos(m_fCarAngle) - vTemp.y * sin(m_fCarAngle);
        m_vEar[i].y = vTemp.x * sin(m_fCarAngle) + vTemp.y * cos(m_fCarAngle);

        m_vEar[i] += m_tInfo.vPos;
    }

#pragma endregion


    return OBJ_NOEVENT;
}

void CPlayerX::Late_Update()
{
    Jump();
    if (CStatus::Get_Instance()->Get_Hp() <= 0 && !m_bDead)
    {
        m_bDead = true;
        m_dwDead = GetTickCount();
    }
}

void CPlayerX::Render(HDC hDC)
{
    if (m_bDead)
    {

        m_vPoint[0] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y + 30.f, 0.f };
        m_vPoint[1] = { m_tInfo.vPos.x - 40.f, m_tInfo.vPos.y + 25.f, 0.f };
        m_vPoint[2] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y + 10.f, 0.f };
        m_vPoint[3] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y - 5.f, 0.f };
        m_vPoint[4] = { m_tInfo.vPos.x - 45.f, m_tInfo.vPos.y - 10.f, 0.f };
        m_vPoint[5] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y - 20.f, 0.f };

        m_vPoint[6] = { m_tInfo.vPos.x + 45.f, m_tInfo.vPos.y - 20.f, 0.f };
        m_vPoint[7] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y - 15.f, 0.f };
        m_vPoint[8] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y - 5.f, 0.f };
        m_vPoint[9] = { m_tInfo.vPos.x + 45.f, m_tInfo.vPos.y + 10.f, 0.f };
        m_vPoint[10] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y + 25.f, 0.f };
        m_vPoint[11] = { m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y + 28.f, 0.f };

        m_vWheel[0] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y - 20.f, 0.f };
        m_vWheel[1] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y - 20.f, 0.f };

        m_vEye = { m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y + 10.f, 0.f };

        m_vEar[0] = { m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y + 28.f, 0.f };
        m_vEar[1] = { m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y + 35.f, 0.f };
        m_vEar[2] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y + 38.f, 0.f };
        m_vEar[3] = { m_tInfo.vPos.x + 32.f, m_tInfo.vPos.y + 30.f, 0.f };
        m_vEar[4] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y + 25.f, 0.f };

    }


    if (m_bDead)
    {
        D3DXMATRIX matScale;
        D3DXMatrixScaling(&matScale, 1.f, -1.f, 1.f);
        m_tInfo.matWorld = matScale;

        D3DXVECTOR3 vTemp = m_tInfo.vPos;
        vTemp -= m_tInfo.vPos;
        D3DXVec3TransformCoord(&vTemp, &vTemp, &m_tInfo.matWorld);

        vTemp += m_tInfo.vPos;
        m_tInfo.vPos = vTemp;
    }

#pragma region 차 몸체

    MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

    for (int i = 0; i < 12; ++i)
        LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

    LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);

#pragma endregion

#pragma region 차 바퀴

    for (int i = 0; i < 2; ++i)
    {
        MoveToEx(hDC, (int)m_vWheel[i].x, (int)m_vWheel[i].y, nullptr);

        Ellipse(hDC,
            int(m_vWheel[i].x - 10.f),
            int(m_vWheel[i].y - 10.f),
            int(m_vWheel[i].x + 10.f),
            int(m_vWheel[i].y + 10.f));
    }

#pragma endregion

#pragma region 포신

    MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
    LineTo(hDC, (int)m_vGunPoint.x, (int)m_vGunPoint.y);

#pragma endregion

#pragma region 눈

    MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);

    if (!m_bDead)
    {
        Ellipse(hDC,
            int(m_vEye.x - 5.f),
            int(m_vEye.y - 5.f),
            int(m_vEye.x + 5.f),
            int(m_vEye.y + 5.f));
    }
    else
    {
        MoveToEx(hDC, int(m_vEye.x - 5.f), int(m_vEye.y - 5.f), nullptr);
        LineTo(hDC, int(m_vEye.x + 5.f), int(m_vEye.y + 5.f));

        MoveToEx(hDC, int(m_vEye.x - 5.f), int(m_vEye.y + 5.f), nullptr);
        LineTo(hDC, int(m_vEye.x + 5.f), int(m_vEye.y - 5.f));
    }

#pragma endregion

#pragma region 귀

    MoveToEx(hDC, (int)m_vEar[0].x, (int)m_vEar[0].y, nullptr);

    for (int i = 0; i < 5; ++i)
        LineTo(hDC, (int)m_vEar[i].x, (int)m_vEar[i].y);

#pragma endregion


}

void CPlayerX::Release()
{
}

void CPlayerX::OnCollision()
{
    CStatus::Get_Instance()->Add_Hp(-1);
    CObjMgr::Get_Instance()->Less_UI(UI_HEART);
}

void CPlayerX::Key_Input()
{
    if (CKeyMgr::GetInstance()->KeyPressing(VK_LCONTROL))
    {
        if (m_dwInvTime + 200 < GetTickCount())
        {
            Create_Bullet();
            m_dwInvTime = GetTickCount();
        }
    }

    if (CKeyMgr::GetInstance()->KeyPressing(VK_LEFT) &&
        CKeyMgr::GetInstance()->KeyPressing(VK_SPACE))
    {
        m_bJump = true;
        m_fJumpAngle = D3DX_PI * 0.55f;
    }

    else if (CKeyMgr::GetInstance()->KeyPressing(VK_RIGHT) &&
        CKeyMgr::GetInstance()->KeyPressing(VK_SPACE))
    {
        m_bJump = true;
        m_fJumpAngle = D3DX_PI * 0.45f;
    }

    else if (CKeyMgr::GetInstance()->KeyPressing(VK_SPACE))
    {
        m_bJump = true;
        m_fJumpAngle = D3DX_PI * 0.5f;
    }

    else if (CKeyMgr::GetInstance()->KeyPressing(VK_LEFT))
    {
        m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
    }

    else if (CKeyMgr::GetInstance()->KeyPressing(VK_RIGHT))
    {
        m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
    }

    else if (CKeyMgr::GetInstance()->KeyPressing(VK_UP))
    {
        m_fPosinAngle += 5.f;
    }

    else if (CKeyMgr::GetInstance()->KeyPressing(VK_DOWN))
    {
        m_fPosinAngle -= 5.f;
    }

}

void CPlayerX::Jump()
{
    // 선 (0, 520) (800, 520)
    float pY = 450.f;

    if (m_bJump)
    {
        m_tInfo.vPos.x += m_fPower * m_fTime * cos(m_fJumpAngle);
        m_tInfo.vPos.y -= m_fPower * m_fTime * sin(m_fJumpAngle) - ((9.8f * m_fTime * m_fTime) * 0.5f);
        m_fTime += 0.2f;

        if (m_fJumpAngle == D3DX_PI * 0.5f)
        {
            m_fCarAngle = 0.f;
        }
        else if (m_fTime < 2.f)
        {
            m_fCarAngle = -m_tInfo.vPos.y / m_tInfo.vPos.x;
        }
        else if (2.f <= m_fTime)
        {
            m_fCarAngle = m_tInfo.vPos.y / m_tInfo.vPos.x;
        }

        if (pY < m_tInfo.vPos.y)
        {
            m_bJump = false;
            m_fTime = 0.f;
            m_tInfo.vPos.y = pY;
            m_tInfo.vLook = { 1.f, 0.f, 0.f };
        }
    }
    else
    {
        m_tInfo.vPos.y = pY;
        m_tInfo.vLook = { 1.f, 0.f, 0.f };
        m_fJumpAngle = 0.f;
        m_fCarAngle = 0.f;
    }
}

void CPlayerX::Create_Bullet()
{
    CObj* pBullet = new CBulletX;
    pBullet->Set_vPos(m_vGunPoint);
    pBullet->Set_vDir(m_vGunPoint-m_tInfo.vPos);

    pBullet->Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBullet);
}
