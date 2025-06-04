// DlgLampMessage.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "DlgLampMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLampMessage dialog


CDlgLampMessage::CDlgLampMessage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLampMessage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLampMessage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgLampMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLampMessage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLampMessage, CDialog)
	//{{AFX_MSG_MAP(CDlgLampMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLampMessage message handlers

void CDlgLampMessage::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
