// DlgChangeLever.cpp : implementation file
//

#include "stdafx.h"
#include "mk.h"
#include "DlgChangeLever.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgChangeLevel dialog


CDlgChangeLevel::CDlgChangeLevel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChangeLevel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgChangeLevel)
	m_level = -1;
	m_passWord = _T("");
	//}}AFX_DATA_INIT
}


void CDlgChangeLevel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChangeLevel)
	DDX_Radio(pDX, IDC_OPERATOR, m_level);
	DDX_Text(pDX, IDC_USER_PASSWORD, m_passWord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChangeLevel, CDialog)
	//{{AFX_MSG_MAP(CDlgChangeLevel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChangeLevel message handlers

BOOL CDlgChangeLevel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	CButton *pButton = (CButton*)GetDlgItem(IDD_DIG_CHANGE_LEVER);
//	pButton->SetCheck(TRUE);
	m_level = 0 ;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
