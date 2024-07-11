#pragma once
#include "Stage.h"
class CMyMenu : public CStage
{
public:
	CMyMenu();
	~CMyMenu() override;

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC _hDC) override;
	void Release() override;
};

