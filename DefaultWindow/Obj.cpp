#include "stdafx.h"
#include "Obj.h"


CObj::CObj() : m_fSpeed(0.f), m_fAngle(0.f), m_bDead(false), m_bInvincibillity(false), m_dwInvTime(NULL), m_bRenderNow(true)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	m_vOrigin = { 0.f, 0.f, 0.f };
}

CObj::~CObj()
{
}


