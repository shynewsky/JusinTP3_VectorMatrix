#pragma once

#include "Obj.h"

class CMonsterX2 : public CObj
{
public:
	CMonsterX2();
	~CMonsterX2();

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
	float			m_fBodyAngle;
	float			m_fWingSpeed;

	// 몬스터 날개
	D3DXVECTOR3		m_vLWing;
	D3DXVECTOR3		m_vOriginLWing;
	float			m_fLWingAngle;

	// 몬스터 날개
	D3DXVECTOR3		m_vRWing;
	D3DXVECTOR3		m_vOriginRWing;
	float			m_fRWingAngle;


};

