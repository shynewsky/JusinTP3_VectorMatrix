#include "stdafx.h"
#include "Status.h"

CStatus* CStatus::m_pInstance = nullptr;

CStatus::CStatus()	: m_iHp(5)
{
	ZeroMemory(m_iScore, sizeof(m_iScore));
	ZeroMemory(m_iHighScore, sizeof(m_iHighScore));
}

CStatus::~CStatus()
{
}

void CStatus::Calc_HighScore(SCENEID _eID)
{
	if (m_iScore[_eID] > m_iHighScore[_eID])
	{
		m_iHighScore[_eID] = m_iScore[_eID];
	}
}
