#pragma once
#include "Obj.h"

class CFlagZ	:	public CObj
{
public:
	CFlagZ();
	~CFlagZ();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision() override;

	D3DXVECTOR3		m_vDrawPoint[6];
	D3DXVECTOR3		m_vOriginDrawPoint[6];

	void		Update_DrawPoint();

};

