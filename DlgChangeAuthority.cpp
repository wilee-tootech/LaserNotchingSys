// DlgChangeAuthority.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgChangeAuthority.h"
#include "LoadString.h"
#include "UserCheck.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgChangeAuthority dialog


CDlgChangeAuthority::CDlgChangeAuthority(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChangeAuthority::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgChangeAuthority)
	// 2007.05.21  
	for (int i=0; i < MAX_USER_SIZE-1;i++)	{
		for (int j=0; j < MAX_AUTH_SIZE; j++) {
			m_iAuthority[i][j] = 0;
		}
	}
	//}}AFX_DATA_INIT
}


void CDlgChangeAuthority::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChangeAuthority)
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOk);
	int i, j, index;

	// BinData Control 생성
	index = IDC_AUTOMARK_AD;

	// 2007.05.21  
	for (i=0; i < MAX_USER_SIZE-1;i++)
	{
		for (j=0; j < MAX_AUTH_SIZE; j++)
		{
			DDX_Check(pDX, index+i*MAX_AUTH_SIZE+j, m_iAuthority[i][j]);
		}
	}

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChangeAuthority, CDialog)
	//{{AFX_MSG_MAP(CDlgChangeAuthority)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChangeAuthority message handlers

BOOL CDlgChangeAuthority::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CLoadString LoadString;
	//LoadString.LoadString(this, IDS_AUTHORITY_1, IDC_AUTHORITY_1, IDC_AUTHORITY_32/*IDC_AUTHORITY_28*/, TRUE, TRUE); // 2021.11.12 한글로 변환하지 않는다. 김준혁
	LoadString.LoadIcon(this, -1, -1, TRUE, TRUE);
		
	LoadValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgChangeAuthority::OnOK() 
{
	// TODO: Add extra validation here
	SetValue();
//IDC_SETAUTHORITY_AD
	//IDC_SETAUTHORITY_OP
	//IDC_SAVEDEV_OP
//	IDC_TEXTCHANGE_OP

	CBeamEditor6App *pApp = (CBeamEditor6App*) AfxGetApp();
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	pUserCheckMng->Save(pApp->m_strCwd + "\\AUTHORITY.usr");	

	CDialog::OnOK();
}

void CDlgChangeAuthority::SetValue()
{
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	CUserCheck *pUser = pUserCheckMng->GetFirst();
	int *iAutority_Ad = new int[MAX_AUTH_SIZE];
	int *iAutority_En = new int[MAX_AUTH_SIZE];
	int *iAutority_Op = new int[MAX_AUTH_SIZE];
	int *iAutority_Et = new int[MAX_AUTH_SIZE]; // 2007.05.21  

	UpdateData(TRUE);

	int i = 0, j;

	for (j = 0; j < MAX_AUTH_SIZE; j++) {
		*(iAutority_Ad + j) = m_iAuthority[0][j];
		*(iAutority_En + j) = m_iAuthority[1][j];
		*(iAutority_Op + j) = m_iAuthority[2][j];
		*(iAutority_Et + j) = m_iAuthority[3][j]; // 2007.05.21  
	}

	while (pUser != NULL) {
		switch(i) {
		case 0:
			pUser->SetAuthority(iAutority_Op, MAX_AUTH_SIZE);
			break;
		case 1:
			pUser->SetAuthority(iAutority_En, MAX_AUTH_SIZE);
			break;
		case 2:
			pUser->SetAuthority(iAutority_Ad, MAX_AUTH_SIZE);
			break;

		// 2007.05.21  	
		case 3:
			pUser->SetAuthority(iAutority_Et, MAX_AUTH_SIZE);
			break;
		}
		pUser = pUserCheckMng->GetNext();
		i++;
	}
}

void CDlgChangeAuthority::LoadValue()
{
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	CUserCheck *pUser = pUserCheckMng->GetFirst();
	int i = 0, j;
	int iLength = MAX_AUTH_SIZE;
	int *iAutority_Ad = new int[MAX_AUTH_SIZE];
	int *iAutority_En = new int[MAX_AUTH_SIZE];
	int *iAutority_Op = new int[MAX_AUTH_SIZE];
	int *iAutority_Et = new int[MAX_AUTH_SIZE]; // 2007.05.21  

	UpdateData(TRUE);

	while (pUser != NULL) {
		switch(i) {
		case 0:
			iAutority_Op = pUser->GetAuthority(iLength);
			break;
		case 1:
			iAutority_En = pUser->GetAuthority(iLength);
			break;
		case 2:
			iAutority_Ad = pUser->GetAuthority(iLength);
			break;

		// 2007.05.21  	
		case 3:
			iAutority_Et = pUser->GetAuthority(iLength);
			break;
		}
		pUser = pUserCheckMng->GetNext();
		i++;
	}

	for (j = 0; j < MAX_AUTH_SIZE; j++) {
		m_iAuthority[0][j] = *(iAutority_Ad + j);
		m_iAuthority[1][j] = *(iAutority_En + j);
		m_iAuthority[2][j] = *(iAutority_Op + j);
		m_iAuthority[3][j] = *(iAutority_Et + j); // 2007.05.21  
	}

	UpdateData(FALSE);
}
