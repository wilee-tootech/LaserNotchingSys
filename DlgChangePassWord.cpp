// DlgChangePassWord.cpp : implementation file
//

#include "stdafx.h"
#include "mk.h"
#include "DlgChangePassWord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgChangePassWord dialog


CDlgChangePassWord::CDlgChangePassWord(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChangePassWord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgChangePassWord)
	m_ad1 = _T("");
	m_ad2 = _T("");
	m_eng1 = _T("");
	m_eng2 = _T("");
	m_oper1 = _T("");
	m_oper2 = _T("");
	//}}AFX_DATA_INIT
	m_userType = 1;
}

void CDlgChangePassWord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChangePassWord)
	DDX_Text(pDX, IDC_ADMINISTRATOR_1, m_ad1);
	DDX_Text(pDX, IDC_ADMINISTRATOR_2, m_ad2);
	DDX_Text(pDX, IDC_ENGINEER_1, m_eng1);
	DDX_Text(pDX, IDC_ENGINEER_2, m_eng2);
	DDX_Text(pDX, IDC_OPERATOR_1, m_oper1);
	DDX_Text(pDX, IDC_OPERATOR_2, m_oper2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChangePassWord, CDialog)
	//{{AFX_MSG_MAP(CDlgChangePassWord)
	ON_BN_CLICKED(IDC_COMFORM_OPER, OnComformOper)
	ON_BN_CLICKED(IDC_COMFORM_ENG, OnComformEng)
	ON_BN_CLICKED(IDC_COMFORM_ADMIN, OnComformAdmin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChangePassWord message handlers

BOOL CDlgChangePassWord::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	CStatic *pStatic;
	CEdit *pEdit;
	CButton *pButton;

	switch(m_userType)
	{
	case 1:	// OPERATOR 
		pStatic = (CStatic*)GetDlgItem(IDC_STATIC_ENG);
		pStatic->ShowWindow(SW_HIDE);
		pEdit = (CEdit*)GetDlgItem(IDC_ENGINEER_1);
		pEdit->ShowWindow(SW_HIDE);
		pEdit = (CEdit*)GetDlgItem(IDC_ENGINEER_2);
		pEdit->ShowWindow(SW_HIDE);
		pButton = (CButton*)GetDlgItem(IDC_COMFORM_ENG);
		pButton->ShowWindow(SW_HIDE);

		pStatic = (CStatic*)GetDlgItem(IDC_STATIC_ADMIN);
		pStatic->ShowWindow(SW_HIDE);
		pEdit = (CEdit*)GetDlgItem(IDC_ADMINISTRATOR_1);
		pEdit->ShowWindow(SW_HIDE);
		pEdit = (CEdit*)GetDlgItem(IDC_ADMINISTRATOR_2);
		pEdit->ShowWindow(SW_HIDE);
		pButton = (CButton*)GetDlgItem(IDC_COMFORM_ADMIN);
		pButton->ShowWindow(SW_HIDE);
		break;
	case 2:	// ENGINEER
		pStatic = (CStatic*)GetDlgItem(IDC_STATIC_ADMIN);
		pStatic->ShowWindow(SW_HIDE);
		pEdit = (CEdit*)GetDlgItem(IDC_ADMINISTRATOR_1);
		pEdit->ShowWindow(SW_HIDE);
		pEdit = (CEdit*)GetDlgItem(IDC_ADMINISTRATOR_2);
		pEdit->ShowWindow(SW_HIDE);
		pButton = (CButton*)GetDlgItem(IDC_COMFORM_ADMIN);
		pButton->ShowWindow(SW_HIDE);
		break;
	case 4: // admin
		break;
	default:
		pStatic = (CStatic*)GetDlgItem(IDC_STATIC_ENG);
		pStatic->ShowWindow(SW_HIDE);
		pEdit = (CEdit*)GetDlgItem(IDC_ENGINEER_1);
		pEdit->ShowWindow(SW_HIDE);
		pEdit = (CEdit*)GetDlgItem(IDC_ENGINEER_2);
		pEdit->ShowWindow(SW_HIDE);
		pButton = (CButton*)GetDlgItem(IDC_COMFORM_ENG);
		pButton->ShowWindow(SW_HIDE);

		pStatic = (CStatic*)GetDlgItem(IDC_STATIC_ADMIN);
		pStatic->ShowWindow(SW_HIDE);
		pEdit = (CEdit*)GetDlgItem(IDC_ADMINISTRATOR_1);
		pEdit->ShowWindow(SW_HIDE);
		pEdit = (CEdit*)GetDlgItem(IDC_ADMINISTRATOR_2);
		pEdit->ShowWindow(SW_HIDE);
		pButton = (CButton*)GetDlgItem(IDC_COMFORM_ADMIN);
		pButton->ShowWindow(SW_HIDE);
		break;
	}
	m_flag[0] = FALSE;
	m_flag[1] = FALSE;
	m_flag[2] = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//////////////////
// 작업자 암호 변경 
void CDlgChangePassWord::OnComformOper() 
{
	// TODO: Add your control notification handler code here
	// 두 암호가 같으면 
	UpdateData(TRUE);
	if ( m_oper1 == m_oper2)
		m_flag[0] = TRUE;
	else
		m_flag[0] = FALSE;
}

void CDlgChangePassWord::OnComformEng() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if ( m_eng1 == m_eng2)
		m_flag[1] = TRUE;
	else
		m_flag[1] = FALSE;
	
}

void CDlgChangePassWord::OnComformAdmin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if ( m_ad1 == m_ad2)
		m_flag[2] = TRUE;
	else
		m_flag[2] = FALSE;
	
}
