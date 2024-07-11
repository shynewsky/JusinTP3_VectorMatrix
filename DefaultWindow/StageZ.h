#pragma once

#include "Stage.h"

class CStageZ : public CStage
{
public:
	CStageZ();
	~CStageZ();

public:
	// CStage을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC _hDC) override;
	void Release() override;

private:
	DWORD	m_dwGenTime;
	DWORD	m_dwTime;
	DWORD	m_dwDifTime;

	float	m_fDifficulty;

	bool	m_bRegenNow;
};

