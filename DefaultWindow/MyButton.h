#pragma once
#include "Obj.h"
class CMyButton : public CObj
{
public:
	CMyButton();
	~CMyButton() override;

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision() override;

public:
	void Set_StageID(SCENEID _eStageID) { m_eStageID = _eStageID; }

	SCENEID Get_StageID() const { return m_eStageID; }

private:
	RECT	m_tRect;
	SCENEID m_eStageID;
};

