#include "stdafx.h"
#include "MyMenu.h"

#include "MyButton.h"
#include "ObjMgr.h"
#include "Status.h"

CMyMenu::CMyMenu()
{
	
}

CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	CObj* pObj = new CMyButton;
	pObj->Initialize();
	pObj->Set_vPos({200.f, 300.f, 0.f});
	dynamic_cast<CMyButton*>(pObj)->Set_StageID(SC_X);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

	pObj = new CMyButton;
	pObj->Initialize();
	pObj->Set_vPos({ 400.f, 300.f, 0.f });
	dynamic_cast<CMyButton*>(pObj)->Set_StageID(SC_Y);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

	pObj = new CMyButton;
	pObj->Initialize();
	pObj->Set_vPos({600.f, 300.f, 0.f});
	dynamic_cast<CMyButton*>(pObj)->Set_StageID(SC_Z);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);
}

int CMyMenu::Update()
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CMyMenu::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC _hDC)
{
	CObjMgr::Get_Instance()->Render(_hDC);

	TCHAR strBuffer[64];
	swprintf_s(strBuffer, L"최고 점수 : %d", CStatus::Get_Instance()->Get_HighScore(SC_X));
	TextOut(_hDC, 150, 400, strBuffer, lstrlen(strBuffer));

	swprintf_s(strBuffer, L"최고 점수 : %d", CStatus::Get_Instance()->Get_HighScore(SC_Y));
	TextOut(_hDC, 350, 400, strBuffer, lstrlen(strBuffer));

	swprintf_s(strBuffer, L"최고 점수 : %d", CStatus::Get_Instance()->Get_HighScore(SC_Z));
	TextOut(_hDC, 550, 400, strBuffer, lstrlen(strBuffer));

}

void CMyMenu::Release()
{
	CObjMgr::Get_Instance()->SetDead_ID(OBJ_BUTTON);
}
