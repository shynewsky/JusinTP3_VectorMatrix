#pragma once
#include "Obj.h"

class CUIHeart	:	public CObj
{
public:
	CUIHeart(float _X, float _Y);
	~CUIHeart();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision() override;


private:

	D3DXVECTOR3		m_vDrawPoint[10];
	D3DXVECTOR3		m_vOriginDrawPoint[10];

	void		Update_DrawPoint();

};

