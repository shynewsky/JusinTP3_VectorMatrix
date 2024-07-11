#pragma once

#include "Obj.h"

class CBulletX : public CObj
{
public:
	CBulletX();
	~CBulletX();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void OnCollision() override;

private:
	// 최초 위치
	D3DXVECTOR3		m_vOriginPos;

	// 표창 몸체
	D3DXVECTOR3		m_vPoint[10];
	D3DXVECTOR3		m_vOriginPoint[10];


};

