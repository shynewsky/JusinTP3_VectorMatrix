#pragma once

#include "Stage.h"

class CStageX : public CStage
{
public:
	CStageX();
	~CStageX();

public:
	// CStage을(를) 통해 상속됨
	void Initialize() override;
	void Release() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC _hDC) override;

};

