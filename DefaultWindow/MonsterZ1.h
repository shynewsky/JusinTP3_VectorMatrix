#pragma once
#include "Obj.h"

class CMonsterZ1 :	public CObj
{
public:
	CMonsterZ1(float _X, float _Y);
	virtual ~CMonsterZ1();

	enum BOXDIR { LEFT, RIGHT };

public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision() override;


private:
	BOXDIR		m_eBoxDir;
	void		Update_DrawPoint();
	float		m_fScale;
	D3DXVECTOR3		m_vDrawPoint[7];
	D3DXVECTOR3		m_vOriginDrawPoint[7];

};

