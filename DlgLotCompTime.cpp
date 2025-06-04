// DlgLotCompTime.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "DlgLotCompTime.h"
#include "MainFrm.h"
#include "BeamEditor6Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLotCompTime dialog


CDlgLotCompTime::CDlgLotCompTime(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLotCompTime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLotCompTime)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgLotCompTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLotCompTime)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLotCompTime, CDialog)
	//{{AFX_MSG_MAP(CDlgLotCompTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLotCompTime message handlers

BOOL CDlgLotCompTime::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();
	FILE *pTime;
	CString m_strTmp;
	
   	pTime = fopen(pApp->m_strCwd + "\\LotCompTime.ini","rt");	
	if(pTime)
	{
		fscanf(pTime , "%d", &m_nLotCompTime);
		fclose(pTime);
		m_strTmp.Format("%d",m_nLotCompTime);
		SetDlgItemText(IDC_EDIT_LOT_COMP_TIME, m_strTmp);
	}
	else
	{
//		AfxMessageBox("Cannot find LotCompTime.ini file!");
		m_nLotCompTime = 0;	
		m_strTmp.Format("%d",m_nLotCompTime);
		SetDlgItemText(IDC_EDIT_LOT_COMP_TIME, m_strTmp);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLotCompTime::OnOK() 
{
	// TODO: Add extra validation here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	
	m_nLotCompTime=GetDlgItemInt(IDC_EDIT_LOT_COMP_TIME);
	FILE *File;
	File = fopen(pApp->m_strCwd+"\\LotCompTime.ini", "wt");
	if(File)
	{
		fprintf(File, "%d\n", m_nLotCompTime);
		fclose(File);
	}

	CDialog::OnOK();
}
