// Mdless2DBarcodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mk.h"
#include "Mdless2DBarcodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMdless2DBarcodeDlg dialog


CMdless2DBarcodeDlg::CMdless2DBarcodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMdless2DBarcodeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMdless2DBarcodeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMdless2DBarcodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMdless2DBarcodeDlg)
	DDX_Control(pDX, IDC_TALBARCD_TEMP, m_TalBarCd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMdless2DBarcodeDlg, CDialog)
	//{{AFX_MSG_MAP(CMdless2DBarcodeDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMdless2DBarcodeDlg message handlers
