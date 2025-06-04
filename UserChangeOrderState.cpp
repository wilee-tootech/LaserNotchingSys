// UserChangeOrderState.cpp: implementation of the CUserChangeOrderState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "beameditor6.h"
#include "UserChangeOrderState.h"
#include "PointerContainer.h"

#include "MKObjectHandler.h"
#include "return.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUserState* CUserChangeOrderState::m_pInstance;

CUserChangeOrderState::CUserChangeOrderState()
{
}

CUserChangeOrderState::~CUserChangeOrderState()
{
	if (m_pInstance != NULL) {
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

CUserState *CUserChangeOrderState::Instance()
{
	if( m_pInstance == NULL)
	{
		m_pInstance = new CUserChangeOrderState;
	}
	return m_pInstance;
}

void CUserChangeOrderState::OnMouseMove(CUserInterface *UI, UINT nFlags, CPoint point)
{

}

void CUserChangeOrderState::OnLButtonUp(CUserInterface *UI, UINT nFlags, CPoint point)
{

}

void CUserChangeOrderState::OnLButtonDown(CUserInterface *UI, UINT nFlags, CPoint point)
{
	
}

void CUserChangeOrderState::Remove()
{
	if (m_pInstance != NULL) {
		delete m_pInstance;
		m_pInstance = NULL;
	}
}
