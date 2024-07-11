#pragma once
#include "Obj.h"
class CFlagY : public CObj
{
public:
	CFlagY();
	CFlagY(float _fX, float _fY);
	~CFlagY() override;

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision() override;

public:
	UINT	Get_Score() const { return m_iScore; }
	float	Get_Distance() const { return m_fDistance; }
	bool	Get_Pass() const { return m_bPassed; }

	void	Set_Score(UINT _iScore) { m_iScore = _iScore; }
	void	Set_Passed() { m_bPassed = true; }
	void	Set_Distance(float _fDist);
	void	Set_Side(float _fSide) { m_fMaxSide = _fSide; }
	void    Set_Dir(int _iDir) { m_iDir = _iDir; }
	void	Set_Move() { m_bMove = true; }

private:
	void	Move_Side();

private:
	D3DXVECTOR3 m_vLPoints[4];
	D3DXVECTOR3 m_vRPoints[4];

	D3DXVECTOR3 m_vOriginLPoints[4];
	D3DXVECTOR3 m_vOriginRPoints[4];

	D3DXVECTOR3 m_vScale;
	D3DXVECTOR3 m_vAngle;

	D3DXVECTOR3 m_vStartPoint;

	float		m_fDistance;
	UINT		m_iScore;
	bool		m_bPassed;
	bool		m_bMove;
	int			m_iDir;
	float		m_fSide;
	float		m_fMaxSide;
};

