#include "stdafx.h"
#include "Stage.h"

CStage::CStage() : m_dwSpawnTime(GetTickCount()), m_bDead(false)
{
}

CStage::~CStage()
{
}
