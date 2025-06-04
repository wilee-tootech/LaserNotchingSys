// POWERCTR.cpp : implementation file
//

#include "stdafx.h"
#include "mk.h"
#include "POWERCTR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPOWERCTR dialog


CPOWERCTR::CPOWERCTR(CWnd* pParent /*=NULL*/)
	: CDialog(CPOWERCTR::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPOWERCTR)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPOWERCTR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPOWERCTR)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPOWERCTR, CDialog)
	//{{AFX_MSG_MAP(CPOWERCTR)
	ON_BN_CLICKED(IDC_AUTO_POWER, OnAutoPower)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPOWERCTR message handlers

void CPOWERCTR::OnAutoPower() 
{
	MessageBox("hyhyhy");
	// TODO: Add your control notification handler code here
	
}
