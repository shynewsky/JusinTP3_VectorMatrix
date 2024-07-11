#pragma once
#include "Player.h"
class CPlayerZ : public CPlayer
{
public:
	CPlayerZ();
	~CPlayerZ();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;


	void OnCollision() override;

private:
	void		Key_Input();
	void		Update_DrawPoint();
	void		FirstPoint();

	D3DXVECTOR3		m_vDrawPointWheel[8];
	D3DXVECTOR3		m_vOriginDrawPointWheel[8];

	D3DXVECTOR3		m_vDrawPointWheelLine[4];
	D3DXVECTOR3		m_vOriginDrawPointWheelLine[4];

	D3DXVECTOR3		m_vDrawPointBody[10];
	D3DXVECTOR3		m_vOriginDrawPointBody[10];

	D3DXVECTOR3		m_vDrawPointSheet[4];
	D3DXVECTOR3		m_vOriginDrawPointSheet[4];

	D3DXVECTOR3		m_vHeadPos;
	D3DXVECTOR3		m_vDrawPointEar[2];
	D3DXVECTOR3		m_vOriginDrawPointEar[2];

	DWORD		m_dwBlinkTime;

	bool		m_bIdleCtr;
	bool		m_bPeekNow;
	bool		m_bIsBroken;

};

