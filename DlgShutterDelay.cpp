// DlgShutterDelay.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "DlgShutterDelay.h"
#include "BeamEditor6Doc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgShutterDelay dialog


CDlgShutterDelay::CDlgShutterDelay(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShutterDelay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShutterDelay)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgShutterDelay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShutterDelay)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShutterDelay, CDialog)
	//{{AFX_MSG_MAP(CDlgShutterDelay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgShutterDelay message handlers

void CDlgShutterDelay::OnOK() 
{
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
    
	m_iShutterDelay = GetDlgItemInt(IDC_EDIT_DELAY);
	FILE *File;
	File = fopen(pApp->m_strCwd+"\\SetDelay.ini", "wt");
	fprintf(File, "%d\n", m_iShutterDelay);
	fclose(File);
	CDialog::OnOK();
}

void CDlgShutterDelay::GetDelay()
{
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();
	FILE *pDelay;
	CString m_strTmp;
	
   	pDelay = fopen(pApp->m_strCwd + "\\SetDelay.ini","rt");	
	if(pDelay)
	{
		fscanf(pDelay , "%d", &m_iShutterDelay);
		fclose(pDelay);
		m_strTmp.Format("%d",m_iShutterDelay);
		SetDlgItemText(IDC_EDIT_DELAY, m_strTmp);
	}
	else
	{
		AfxMessageBox("Cannot found SetDelay.ini file!");
	}

	
}

BOOL CDlgShutterDelay::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDelay();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
