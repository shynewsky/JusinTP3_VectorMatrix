#pragma once

#include "Stage.h"

class CStageY : public CStage
{
public:
	CStageY();
	~CStageY() override;

public:
	void Initialize() override;
	void Release() override;
	int Update() override;
	void Render(HDC _hDC) override;
	void Late_Update() override;

private:
	void Create_Flag();

public:
	void Show_ExitBtn() const;

private:
	DWORD	m_dwMonsterTimer;
	DWORD	m_dwFlagTimer;
	UINT	m_iFlagInterval;

	UINT	m_iFlagCount;
	UINT	m_iScore;

	bool	m_bIsFinished;
	D3DXVECTOR3 m_vCreatePos[3];
};

