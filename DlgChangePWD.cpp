// DlgChangePWD.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgChangePWD.h"
#include "LoadString.h"
#include "UserCheck.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgChangePWD dialog


CDlgChangePWD::CDlgChangePWD(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChangePWD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgChangePWD)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgChangePWD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChangePWD)
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOk);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChangePWD, CDialog)
	//{{AFX_MSG_MAP(CDlgChangePWD)
	ON_BN_CLICKED(IDC_CONFIRM_OPER, OnConfirmOper)
	ON_BN_CLICKED(IDC_CONFIRM_ENG, OnConfirmEng)
	ON_BN_CLICKED(IDC_CONFIRM_ADMIN, OnConfirmAdmin)
	ON_BN_CLICKED(IDC_CONFIRM_EDITOR, OnConfirmEditor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChangePWD message handlers

BOOL CDlgChangePWD::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CLoadString LoadString;
	LoadString.LoadString(this, IDS_CHANGEPWD_1, IDC_CHANGEPWD_1, IDC_CHANGEPWD_5, TRUE, TRUE);
	LoadString.LoadIcon(this, -1, -1, TRUE, TRUE);
	
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	if (pUserCheckMng->GetCurUserName() == "OPERATOR") {
		GetDlgItem(IDC_CHANGEPWD_4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ENGINEER_1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ENGINEER_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONFIRM_ENG)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHANGEPWD_5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ADMINISTRATOR_1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ADMINISTRATOR_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONFIRM_ADMIN)->ShowWindow(SW_HIDE);
	}
	else if (pUserCheckMng->GetCurUserName() == "ENGINEER") {
		GetDlgItem(IDC_CHANGEPWD_5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ADMINISTRATOR_1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ADMINISTRATOR_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONFIRM_ADMIN)->ShowWindow(SW_HIDE);
	}
	


	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgChangePWD::OnConfirmOper() 
{
	// TODO: Add your control notification handler code here
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	CUserCheck *pUser = pUserCheckMng->GetFirst();
	CString strPwd1, strPwd2;

	GetDlgItem(IDC_OPERATOR_1)->GetWindowText(strPwd1);
	GetDlgItem(IDC_OPERATOR_2)->GetWindowText(strPwd2);

	if (strPwd1 != strPwd2) {
		AfxMessageBox(IDS_MESSAGE51);
		return;
	}

	while (pUser != NULL) {
		if (pUser->GetUserName() == "OPERATOR") {
			pUser->SetPassword(strPwd1);
			AfxMessageBox(IDS_MESSAGE52);
			break;
		}
		pUser = pUserCheckMng->GetNext();
	}
}

void CDlgChangePWD::OnConfirmEng() 
{
	// TODO: Add your control notification handler code here
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	CUserCheck *pUser = pUserCheckMng->GetFirst();
	CString strPwd1, strPwd2;

	GetDlgItem(IDC_ENGINEER_1)->GetWindowText(strPwd1);
	GetDlgItem(IDC_ENGINEER_2)->GetWindowText(strPwd2);

	if (strPwd1 != strPwd2) {
		AfxMessageBox(IDS_MESSAGE51);
		return;
	}

	while (pUser != NULL) {
		if (pUser->GetUserName() == "ENGINEER") {
			pUser->SetPassword(strPwd1);
			AfxMessageBox(IDS_MESSAGE52);
			break;
		}
		pUser = pUserCheckMng->GetNext();
	}
}

void CDlgChangePWD::OnConfirmAdmin() 
{
	// TODO: Add your control notification handler code here
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	CUserCheck *pUser = pUserCheckMng->GetFirst();
	CString strPwd1, strPwd2;

	GetDlgItem(IDC_ADMINISTRATOR_1)->GetWindowText(strPwd1);
	GetDlgItem(IDC_ADMINISTRATOR_2)->GetWindowText(strPwd2);

	if (strPwd1 != strPwd2) {
		AfxMessageBox(IDS_MESSAGE51);
		return;
	}

	while (pUser != NULL) {
		if (pUser->GetUserName() == "ADMINISTRATOR") {
			pUser->SetPassword(strPwd1);
			AfxMessageBox(IDS_MESSAGE52);
			break;
		}
		pUser = pUserCheckMng->GetNext();
	}
}

void CDlgChangePWD::OnConfirmEditor() 
{
	// TODO: Add your control notification handler code here
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	CUserCheck *pUser = pUserCheckMng->GetFirst();
	CString strPwd1, strPwd2;

	GetDlgItem(IDC_EDITOR_1)->GetWindowText(strPwd1);
	GetDlgItem(IDC_EDITOR_2)->GetWindowText(strPwd2);

	if (strPwd1 != strPwd2) {
		AfxMessageBox(IDS_MESSAGE51);
		return;
	}

	while (pUser != NULL) {
		if (pUser->GetUserName() == "EDITOR") {
			pUser->SetPassword(strPwd1);
			AfxMessageBox(IDS_MESSAGE52);
			break;
		}
		pUser = pUserCheckMng->GetNext();
	}	
}
