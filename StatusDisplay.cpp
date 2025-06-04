// StatusDisplay.cpp: implementation of the CStatusDisplay class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "beameditor6.h"
#include "StatusDisplay.h"
#include "MainFrm.h"
#include "PointTranslator.h"

#include "PointerContainer.h"
#include "FieldParameter.h"
#include "TransUnit.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatusDisplay::CStatusDisplay()
{
	m_strStatus = "Ready";
}

CStatusDisplay::~CStatusDisplay()
{

}

void CStatusDisplay::SetString(CString strStatus)
{
	m_strStatus = strStatus;
}

void CStatusDisplay::DisplayStatus()
{
	// ¸¶¿ì½º ÁÂÇ¥ Display
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CStatusBar  *m_wndStatusBar = pMainFrm->GetStatusBar();
	

	m_wndStatusBar->SetWindowText(m_strStatus);


}

void CStatusDisplay::SetCurrentPoint(CPoint cpCurrent)
{
	
	
	
}
