#pragma once
#include "Define.h"

class CStatus
{
private:
	CStatus();
	~CStatus();

public:
	int Get_Hp() { return m_iHp; }
	int Get_Score(SCENEID _eID) { return m_iScore[_eID]; }
	int Get_HighScore(SCENEID _eID) { return m_iHighScore[_eID]; }

	void	Add_Hp(int _i) { m_iHp += _i; }
	void	Add_Score(SCENEID _eID, int _i) { m_iScore[_eID] += _i; }

	void	Reset_Hp() { m_iHp = 5; }
	void	Reset_Score(SCENEID _eID) { m_iScore[_eID] = 0; }

	void	Calc_HighScore(SCENEID _eID);

	static CStatus* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CStatus;
		}
		return m_pInstance;		//매니저 반환
	}
	static void Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CStatus* m_pInstance;

	int		m_iHp;
	int		m_iScore[SC_END];
	int		m_iHighScore[SC_END];

};

