#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Status.h"
#include "UIHeart.h"


CObjMgr*		CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr() :	m_bUIRender(false)
{
}


CObjMgr::~CObjMgr()
{
	Release();
}


void CObjMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if (OBJ_END <= eID || nullptr == pObj || eID < 0)
		return;

	m_ObjList[eID].push_back(pObj);
}

void CObjMgr::Add_UI(UIID eID, CObj* pObj)
{
	if (UI_END <= eID || nullptr == pObj || eID < 0)
		return;

	m_UIList[eID].push_back(pObj);
}

void CObjMgr::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
	 	for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int		iResult = (*iter)->Update();
			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Late_Update()
{
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER]);

	CCollisionMgr::Pass_FlagY(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_FLAG]);

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			if (iter == nullptr)
			{
				continue;
			}
			iter->Late_Update();
		}
	}

}

void CObjMgr::Render(HDC hDC)
{

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}

	if (m_bUIRender)
	{
		for (size_t i = 0; i < UI_END; ++i)
		{
			for (auto& iter : m_UIList[i])
				iter->Render(hDC);
		}
		
	}

}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
	for (size_t i = 0; i < UI_END; ++i)
	{
		for_each(m_UIList[i].begin(), m_UIList[i].end(), Safe_Delete<CObj*>);
		m_UIList[i].clear();
	}
}

void CObjMgr::Less_UI(UIID eID)
{
	if (!m_UIList[eID].empty())
	{
		Safe_Delete<CObj*>(m_UIList[eID].back());
		m_UIList[eID].pop_back();
	}
}

void CObjMgr::Reset_Player()
{
	if (!m_ObjList->empty())
	{
		Safe_Delete<CObj*>(m_ObjList[OBJ_PLAYER].front());
		m_ObjList[OBJ_PLAYER].clear();
	}
}

void CObjMgr::Add_Heart_UI()
{
	CObj* UIObj;
	int iPosX = CStatus::Get_Instance()->Get_Hp();
	UIObj = new CUIHeart(18 + 32 * (iPosX - 1), 550);
	UIObj->Initialize();
	Add_UI(UI_HEART, UIObj);
}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& pObj : m_ObjList[eID])
		Safe_Delete<CObj*>(pObj);

	m_ObjList[eID].clear();
}

void CObjMgr::SetDead_ID(OBJID eID)
{
	for (auto& pObj : m_ObjList[eID])
		pObj->Set_Dead();
}
