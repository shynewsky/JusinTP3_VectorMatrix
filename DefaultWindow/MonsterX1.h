#pragma once

#include "Obj.h"

class CMonsterX1 : public CObj
{
public:
	CMonsterX1();
	~CMonsterX1();

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

	// 몬스터 몸체
	D3DXVECTOR3		m_vPoint[12];
	D3DXVECTOR3		m_vOriginPoint[12];

	// 몬스터 크기 증가
	float			m_fSizeUp;

};

