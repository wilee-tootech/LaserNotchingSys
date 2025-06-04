// UserState.h: interface for the CUserState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERSTATE_H__1E016409_552C_41DE_BE19_22CE07C30EBC__INCLUDED_)
#define AFX_USERSTATE_H__1E016409_552C_41DE_BE19_22CE07C30EBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CUserInterface;

class CUserState  
{
public:
	CUserState();
	virtual ~CUserState();
	
public:



//	virtual CUserState *Instance()=0;

	virtual void OnMouseMove(CUserInterface *, UINT nFlags, CPoint point);
	virtual void OnLButtonDown(CUserInterface *, UINT nFlags, CPoint point);
	virtual void OnLButtonUp(CUserInterface *, UINT nFlags, CPoint point);
	virtual void OnLButtonDblClk(CUserInterface *,  UINT nFlags, CPoint point);
	virtual void OnRButtonDown(CUserInterface *, UINT nFlags, CPoint point);
	virtual void OnRButtonUp(CUserInterface *, UINT nFlags, CPoint point);
	virtual void OnRButtonDblClk(CUserInterface *,  UINT nFlags, CPoint point);
	virtual void OnKeyDown(CUserInterface *, UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnKeyUp(CUserInterface *UI, UINT nChar, UINT nRepCnt, UINT nFlags );

	virtual void OnMouseWheel(CUserInterface *, UINT nFlags, short zDelta, CPoint pt);

	virtual void ChangeState(CUserInterface *UI, CUserState *US);

	virtual void SetCurrentPointStatus(int iCurrentStatus);

	
	

protected:
	int m_iCurrentStatus;


private:
};

#endif // !defined(AFX_USERSTATE_H__1E016409_552C_41DE_BE19_22CE07C30EBC__INCLUDED_)
