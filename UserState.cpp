// UserState.cpp: implementation of the CUserState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "UserState.h"
#include "UserInterface.h"
#include "define.h"
#include "PointerContainer.h"

#include "MainFrm.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserState::CUserState()
{
	m_iCurrentStatus = NULL_POINT;

}

CUserState::~CUserState()
{

}

void CUserState::OnMouseMove(CUserInterface *, UINT nFlags, CPoint point)
{


}
void CUserState::OnLButtonDown(CUserInterface *, UINT nFlags, CPoint point)
{

}
void CUserState::OnLButtonUp(CUserInterface *, UINT nFlags, CPoint point)
{


}
void CUserState::OnLButtonDblClk(CUserInterface *,  UINT nFlags, CPoint point)
{


}
void CUserState::OnRButtonDown(CUserInterface *, UINT nFlags, CPoint point)
{



}
void CUserState::OnRButtonUp(CUserInterface *, UINT nFlags, CPoint point)
{



}
void CUserState::OnRButtonDblClk(CUserInterface *,  UINT nFlags, CPoint point)
{


}
void CUserState::OnKeyDown(CUserInterface *, UINT nChar, UINT nRepCnt, UINT nFlags)
{



}

void CUserState::OnMouseWheel(CUserInterface *, UINT nFlags, short zDelta, CPoint pt)
{


}

void CUserState::OnKeyUp(CUserInterface *UI, UINT nChar, UINT nRepCnt, UINT nFlags )
{



}

void CUserState::ChangeState(CUserInterface *UI, CUserState *US)
{
	UI->ChangeState(US);
}

void CUserState::SetCurrentPointStatus(int iCurrentStatus)
{
	m_iCurrentStatus = iCurrentStatus;
}

