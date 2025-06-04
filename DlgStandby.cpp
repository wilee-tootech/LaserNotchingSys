// DlgStandby.cpp : implementation file
//

#include "stdafx.h"
#include "mk.h"
#include "DlgStandby.h"
#include "MainFrm.h"
#include "MKDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgStandby dialog


CDlgStandby::CDlgStandby(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStandby::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgStandby)
	m_fStandbyCurrent = 0.0f;
	m_iStandbyTime = 0;
	//}}AFX_DATA_INIT
}


void CDlgStandby::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStandby)
	DDX_Text(pDX, IDC_STANDBY_CURRENT, m_fStandbyCurrent);
	DDV_MinMaxFloat(pDX, m_fStandbyCurrent, 0.f, 22.f);
	DDX_Text(pDX, IDC_STANDBY_TIME, m_iStandbyTime);
	DDV_MinMaxInt(pDX, m_iStandbyTime, 1, 1440);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStandby, CDialog)
	//{{AFX_MSG_MAP(CDlgStandby)
	ON_BN_CLICKED(IDC_STANDBYTIME_RESET, OnStandbytimeReset)
	ON_BN_CLICKED(IDC_STANDBYCURRENT_RESET, OnStandbycurrentReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgStandby message handlers

void CDlgStandby::OnStandbytimeReset() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMKDoc * pDoc = (CMKDoc*)pFrame->GetActiveDocument();

	if (pDoc->m_user.m_userType != ENGINEER)
	{
		AfxMessageBox(IDS_AUTHORITY, MB_OK);
		m_iStandbyTime = pDoc->m_iStandbyTime;
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		pDoc->m_iStandbyTime = m_iStandbyTime;
	}
}

BOOL CDlgStandby::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMKDoc * pDoc = (CMKDoc*)pFrame->GetActiveDocument();

	m_iStandbyTime = pDoc->m_iStandbyTime;
	m_fStandbyCurrent = pDoc->m_dStandbyCurrent;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgStandby::OnStandbycurrentReset() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMKDoc * pDoc = (CMKDoc*)pFrame->GetActiveDocument();

	if (pDoc->m_user.m_userType != ENGINEER)
	{
		AfxMessageBox(IDS_AUTHORITY, MB_OK);
		m_fStandbyCurrent = pDoc->m_dStandbyCurrent;
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		pDoc->m_dStandbyCurrent = m_fStandbyCurrent;
	}
}
