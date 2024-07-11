#pragma once
#include "Player.h"

class CPlayerY : public CPlayer
{
public:
	CPlayerY();
	~CPlayerY() override;

public:
	void	Initialize() override;
	int		Update() override;
	void	Late_Update() override;
	void	Render(HDC hDC) override;
	void	Release() override;
	void	OnCollision() override;

public:
	void	Set_Right(bool _bRight) { m_bRight = _bRight; }
	bool	Slip();


private:
	void	Key_Input();
	void	Rotation();
	void	Move();

private:
	D3DXVECTOR3 m_vAngle;
	D3DXVECTOR3 m_vScale;

	D3DXVECTOR3	m_vCar[4];
	D3DXVECTOR3 m_vOriginCar[4];
	D3DXVECTOR3	m_vHead;
	D3DXVECTOR3	m_vOriginHead;

	float	m_fRotSpeed;
	float	m_fHeadSize;
	bool	m_bRight;
	UINT	m_iHp;
	UINT	m_iRotCount;
	UINT	m_iMaxRotCount;
	bool	m_bSlip;
	bool	m_bIdle;
};

