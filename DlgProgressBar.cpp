// DlgProgressBar.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "DlgProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProgressBar dialog


CDlgProgressBar::CDlgProgressBar(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProgressBar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProgressBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgProgressBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProgressBar)
	DDX_Control(pDX, IDC_ST_STATUS, m_ctrProgressSta);
	DDX_Control(pDX, IDC_PROGRESS2, m_ctrProgress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProgressBar, CDialog)
	//{{AFX_MSG_MAP(CDlgProgressBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

