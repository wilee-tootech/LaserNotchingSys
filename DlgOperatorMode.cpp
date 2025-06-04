// DlgOperatorMode.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "DlgOperatorMode.h"
#include "MainFrm.h"
#include "BeamEditor6Doc.h"
#include "BeamEditor6View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOperatorMode dialog


CDlgOperatorMode::CDlgOperatorMode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOperatorMode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOperatorMode)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgOperatorMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOperatorMode)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOperatorMode, CDialog)
	//{{AFX_MSG_MAP(CDlgOperatorMode)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgOperatorMode::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOperatorMode message handlers

void CDlgOperatorMode::OnOK() 
{
	// TODO: Add extra validation here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
   
	m_nOperatorModeTime=GetDlgItemInt(IDC_EDIT_OPERATOR_MODE_TIME);
	FILE *File;
	File = fopen(pApp->m_strCwd+"\\OperatorTime.ini", "wt");
	fprintf(File, "%d\n", m_nOperatorModeTime);
	fclose(File);
	CDialog::OnOK();
}

BOOL CDlgOperatorMode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();
	FILE *pTime;
	CString m_strTmp;
	
   	pTime = fopen(pApp->m_strCwd + "\\OperatorTime.ini","rt");	
	if(pTime)
	{
		fscanf(pTime , "%d", &m_nOperatorModeTime);
		fclose(pTime);
		m_strTmp.Format("%d",m_nOperatorModeTime);
		SetDlgItemText(IDC_EDIT_OPERATOR_MODE_TIME, m_strTmp);
	}
	else
	{
		AfxMessageBox("Cannot find OperatorTime.ini file!");
		m_strTmp.Format("%d",m_nOperatorModeTime);
		SetDlgItemText(IDC_EDIT_OPERATOR_MODE_TIME, m_strTmp);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgOperatorMode::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}
