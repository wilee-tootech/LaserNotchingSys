#include "stdafx.h"
#include "UserInterface.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CUserInterface::CUserInterface()
{

	
	ASSERT(_state != NULL);
}

CUserInterface::~CUserInterface()
{
	
}

void CUserInterface::OnMouseMove(UINT nFlags, CPoint point)
{
	_state->OnMouseMove(this, nFlags,point);
}

void CUserInterface::OnLButtonDown(UINT nFlags, CPoint point)
{
	_state->OnLButtonDown(this, nFlags,point);
}

void CUserInterface::OnLButtonUp(UINT nFlags, CPoint point)
{
	_state->OnLButtonUp(this, nFlags,point);
}



void CUserInterface::OnLButtonDblClk( UINT nFlags, CPoint point)
{
	_state->OnLButtonDblClk(this, nFlags,point);
	
}

void CUserInterface::OnRButtonDown(UINT nFlags, CPoint point)
{
	_state->OnRButtonDown(this, nFlags,point);

}

void CUserInterface::OnRButtonUp(UINT nFlags, CPoint point)
{
	_state->OnRButtonUp(this, nFlags,point);
}
void CUserInterface::OnRButtonDblClk( UINT nFlags, CPoint point)
{
	_state->OnRButtonDblClk(this, nFlags,point);
}



void CUserInterface::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{// 전역적으로 후킹 
	
		
	_state->OnKeyDown(this, nChar, nRepCnt, nFlags);
}

void CUserInterface::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags )
{

	_state->OnKeyUp(this, nChar, nRepCnt, nFlags);
}


void CUserInterface::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	_state->OnMouseWheel(this, nFlags, zDelta, pt);
}

void CUserInterface::ChangeState(CUserState* pUserState)
{
	return;
	_state = pUserState;

}