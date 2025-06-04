// UserChangeOrderState.h: interface for the CUserChangeOrderState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERCHANGEORDERSTATE_H__58754193_79FE_4DB0_8EAC_28FCDF76AB3C__INCLUDED_)
#define AFX_USERCHANGEORDERSTATE_H__58754193_79FE_4DB0_8EAC_28FCDF76AB3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UserState.h"
#include "define.h"

/*class CUserChangeOrderState : public CUserState   
{
public:
	CUserChangeOrderState();
	virtual ~CUserChangeOrderState();

	static CUserState *Instance();
	static void Remove();
	virtual void OnLButtonDown(CUserInterface *UI, UINT nFlags, CPoint point);
	virtual void OnMouseMove(CUserInterface *, UINT nFlags, CPoint point);
	virtual void OnLButtonUp(CUserInterface *, UINT nFlags, CPoint point);

private:
	static CUserState *m_pInstance;
};*/
class CUserChangeOrderState : public CUserState  
{
public:
	CUserChangeOrderState();
	virtual ~CUserChangeOrderState();

	static CUserState *Instance();
	static void Remove();
	virtual void OnLButtonDown(CUserInterface *UI, UINT nFlags, CPoint point);
	virtual void OnMouseMove(CUserInterface *, UINT nFlags, CPoint point);
	virtual void OnLButtonUp(CUserInterface *, UINT nFlags, CPoint point);

	enum DragDirection 
	{
		D_UPWARD = 1,
		D_DOWNWARD = 2
	};

private:
	static CUserState *m_pInstance;
	CPoint m_NowMousePoint;
	CRect m_rtLast;
};

#endif // !defined(AFX_USERCHANGEORDERSTATE_H__58754193_79FE_4DB0_8EAC_28FCDF76AB3C__INCLUDED_)