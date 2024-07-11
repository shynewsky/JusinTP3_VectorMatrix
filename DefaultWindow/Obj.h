#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual		void		Initialize()	PURE;
	virtual		int			Update()		PURE;
	virtual		void		Late_Update()	PURE;
	virtual		void		Render(HDC hDC)	PURE;
	virtual		void		Release()		PURE;


public:
	INFO	Get_Info() { return m_tInfo; }
	bool	Get_Inv() { return m_bInvincibillity; }
	void	Set_Dead() { m_bDead = true; }

	// 양새하 추가
	void	Set_vPos(D3DXVECTOR3 _vGunPoint) { m_tInfo.vPos = _vGunPoint; };
	void	Set_vDir(D3DXVECTOR3 _vDir) { m_tInfo.vDir = _vDir; }

	virtual void OnCollision() PURE;

protected:
	INFO		m_tInfo;
	D3DVECTOR	m_vOrigin;
	RECT		m_tRect;

	float		m_fSpeed;
	float		m_fAngle;

	bool		m_bDead;

	bool		m_bRenderNow;
	bool		m_bInvincibillity;
	DWORD		m_dwInvTime;


};

