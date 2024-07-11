#include "stdafx.h"
#include "CollisionMgr.h"
#include "FlagY.h"
#include "PlayerY.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}


void CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		if (Dst->Get_Inv())
		{
			return;
		}
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->OnCollision();
				Src->OnCollision();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * pDst, CObj * pSrc)
{
	float	fWidth  = abs(pDst->Get_Info().vPos.x - pSrc->Get_Info().vPos.x);
	float	fHeight	= abs(pDst->Get_Info().vPos.y - pSrc->Get_Info().vPos.y);

	float	fDiagonal = sqrt(fWidth * fWidth + fHeight  * fHeight);

	float	fRadius = (pDst->Get_Info().fRadius + pSrc->Get_Info().fRadius);
	
	return fRadius >= fDiagonal;
}

void CCollisionMgr::Pass_FlagY(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (On_Passed(Dst, Src))
			{
				Dst->OnCollision();
				//dynamic_cast<CPlayerY*>(Dst)->Plus_Rotation_Chance();
			}
		}
	}
}

bool CCollisionMgr::On_Passed(CObj* pDst, CObj* pSrc)
{
	auto pFlag = dynamic_cast<CFlagY*>(pSrc);
	if (pFlag->Get_Pass())
	{
		return false;
	}

	INFO tPlayerInfo = pDst->Get_Info();
	INFO tFlagInfo = pFlag->Get_Info();
	float fDistance = pFlag->Get_Distance();

	if (tPlayerInfo.vPos.x <= tFlagInfo.vPos.x + fDistance &&
		tPlayerInfo.vPos.x >= tFlagInfo.vPos.x - fDistance &&
		tPlayerInfo.vPos.y <= tFlagInfo.vPos.y + 10 &&
		tPlayerInfo.vPos.y >= tFlagInfo.vPos.y - 10)
	{
		pFlag->Set_Passed();
		return true;
	}

	return false;
}