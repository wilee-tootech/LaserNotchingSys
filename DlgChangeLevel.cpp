// DlgChangeLevel.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgChangeLevel.h"
#include "LoadString.h"
#include "UserCheck.h"

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
	m_iUserLevel = -1;
	//}}AFX_DATA_INIT
}


void CDlgChangeLevel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChangeLevel)
	DDX_Control(pDX, IDC_CHANGELEVEL_2, m_ctrUserLevel);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Radio(pDX, IDC_CHANGELEVEL_2, m_iUserLevel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChangeLevel, CDialog)
	//{{AFX_MSG_MAP(CDlgChangeLevel)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChangeLevel message handlers

BOOL CDlgChangeLevel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CLoadString LoadString;
//	LoadString.LoadString(this, IDS_CHANGELEVEL_1, IDC_CHANGELEVEL_1, IDC_CHANGELEVEL_4, TRUE, TRUE);
	LoadString.LoadIcon(this, -1, -1, TRUE, TRUE);
		
	LoadValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgChangeLevel::OnOK() 
{
	// TODO: Add extra validation here
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	CString strTemp;

	/* Check하려면 int 값으로 받아야할 듯 */
	UpdateData(TRUE);
	m_ctrUserLevel.GetWindowText(strTemp);
	pUserCheckMng->SetCurUserWithName(strTemp);
	m_ctrUserLevel.GetCheck();
	CDialog::OnOK();
}

void CDlgChangeLevel::LoadValue()
{
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	CUserCheck *pUser = pUserCheckMng->GetCurUser();
	m_ctrUserLevel.SetWindowText(pUserCheckMng->GetCurUserName());
//	m_iUserLevel = pUserCheckMng->GetCurUserIndex();
	UpdateData(FALSE);
}

HBRUSH CDlgChangeLevel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
/*	
	// TODO: Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_STATIC)  
	{
	    pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,100));
		
        HBRUSH B = CreateSolidBrush(RGB(213,196,247)); // 배경색 흰색 
        return (HBRUSH) B;
	}
	else if (nCtlColor != CTLCOLOR_EDIT && nCtlColor != CTLCOLOR_LISTBOX)  
    {
        pDC->SetBkMode(TRANSPARENT);
        HBRUSH B = CreateSolidBrush(RGB(213,196,247)); // 배경색 흰색 
        return (HBRUSH) B;
    } 
	return hbr;
	// TODO: Return a different brush if the default is not desired
	*/
	return hbr;
}
