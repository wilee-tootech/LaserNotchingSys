// DlgPassword.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "DlgPassword.h"
#include "UserCheck.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPassword dialog


CDlgPassword::CDlgPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPassword::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPassword)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPassword)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPassword, CDialog)
	//{{AFX_MSG_MAP(CDlgPassword)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPassword message handlers

void CDlgPassword::OnOK() 
{
	// TODO: Add extra validation here
	CString strPwd, strUser;
	GetDlgItemText(IDC_EDIT_PW, strPwd);

	if (strPwd.GetLength() == 0)
	{
		GetDlgItem(IDC_EDIT_PW)->SetFocus();
		return;
	}

	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	CUserCheck *pUser;
	CString strTemp;

	
	pUser = pUserCheckMng->GetFirst();
	
	while (true)
	{
		if (pUser->GetUserName() == "EDITOR")
		{
			if (pUser->GetPassword() == strPwd)
			{
				CDialog::OnOK();
				return;
			}
			else
			{
				break;
			}
		}
		pUser = pUserCheckMng->GetNext();
	}

	AfxMessageBox("비밀번호가 일치하지 않습니다.");
//	AfxMessageBox("Incorrect password.");	//in English
	SetDlgItemText(IDC_EDIT_PW, "");
	GetDlgItem(IDC_EDIT_PW)->SetFocus();
	return;
}

void CDlgPassword::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

int CDlgPassword::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	/*
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	GetDlgItem(IDC_EDIT_PW)->SetFocus();
	*/
	return 0;
}
