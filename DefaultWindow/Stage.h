#pragma once
#include "Obj.h"
#include "Player.h"

class CStage
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual void Initialize()		PURE;
	virtual int Update()			PURE;
	virtual void Late_Update()		PURE;
	virtual void Render(HDC _hDC)	PURE;
	virtual void Release()			PURE;

protected:
	DWORD	m_dwSpawnTime;

	bool	m_bDead;

};
