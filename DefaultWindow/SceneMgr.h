#pragma once

#include "Stage.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	SCENEID	Get_Scene() { return m_eCurScene; }

public:
	void Scene_Change(SCENEID eID);
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
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
	static CSceneMgr* m_pInstance;
	CStage* m_pScene;

	SCENEID	m_ePreScene;
	SCENEID	m_eCurScene;

	DWORD	m_dwScoreTime;

	

};

