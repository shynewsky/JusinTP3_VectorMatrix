#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src);
	static bool Check_Sphere(CObj* pDst, CObj* pSrc);

	static void Pass_FlagY(list<CObj*> _Dst, list<CObj*> _Src);
	static bool On_Passed(CObj* pDst, CObj* pSrc);
};

