#pragma once
#include "Player.h"

class CPlayerX :	public CPlayer
{
public:
	CPlayerX();
	~CPlayerX();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void OnCollision() override;

private:
	void	Key_Input();
	void	Jump();
	void	Create_Bullet();

private:
	// 최초 위치
	D3DXVECTOR3		m_vOriginPos;

	// 차 몸체
	D3DXVECTOR3		m_vPoint[12];
	D3DXVECTOR3		m_vOriginPoint[12];

	// 바퀴 중심
	D3DXVECTOR3		m_vWheel[2];
	D3DXVECTOR3		m_vOriginWheel[2];

	// 눈 중심
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vOriginEye;

	// 귀
	D3DXVECTOR3		m_vEar[5];
	D3DXVECTOR3		m_vOriginEar[5];

	// 포신(앵그리버드?)
	D3DXVECTOR3		m_vGunPoint;
	D3DXVECTOR3		m_vOriginGunPoint;

	// 점프
	bool			m_bJump;
	float			m_fPower;
	float			m_fTime;

	// 회전 각도
	float			m_fCarAngle;
	float			m_fPosinAngle;
	float			m_fJumpAngle;

	// 죽은 시각
	DWORD			m_dwDead;

};

