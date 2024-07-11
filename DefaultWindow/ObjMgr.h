#pragma once

#include "Obj.h"
#include "Define.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*			Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }	// 선생님이 짜 놓은 코드입니다.
	CObj*			Get_Monster() { return m_ObjList[OBJ_MONSTER].front(); }
	list<CObj*>&	Get_MonsterList() { return m_ObjList[OBJ_MONSTER]; }

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	void		Add_UI(UIID eID, CObj* pObj);
	void		Update();		
	void		Late_Update();
	void		Render(HDC hDC);		
	void		Release();

	void		Less_UI(UIID eID);
	void		Set_UI_Render(bool _b) { m_bUIRender = _b; }
	void		Add_Heart_UI();

	void		Delete_ID(OBJID eID);
	void		SetDead_ID(OBJID eID);

	void		Reset_Player();

private:
	list<CObj*>	m_ObjList[OBJ_END]; 
	list<CObj*>	m_UIList[UI_END];

public:
	static CObjMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}
	static void		Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjMgr*		m_pInstance;

	bool		m_bUIRender;

};

