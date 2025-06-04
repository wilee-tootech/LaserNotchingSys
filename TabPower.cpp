 // TabPower.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "MainFrm.h"
#include "TabPower.h"
#include "LoadString.h"
#include "PointerManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabPower dialog


CTabPower::CTabPower(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CTabPower::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabPower)
	m_dAperture = 0.0;
	m_dPower = 0.0;
	m_dCurrent = 0.0;
	m_strDate = "YYYY/MM/DD";
	//}}AFX_DATA_INIT
}


void CTabPower::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabPower)
	DDX_Text(pDX, IDC_SAVED_APERTURE, m_dAperture);
	DDX_Text(pDX, IDC_SAVED_POWER, m_dPower);
	DDX_Text(pDX, IDC_SAVED_CURRENT, m_dCurrent);
	DDX_Text(pDX, IDC_SAVED_DATE, m_strDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabPower, CDialog)
	//{{AFX_MSG_MAP(CTabPower)
	ON_BN_CLICKED(IDC_POWERMETER_7, OnRecordingMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabPower message handlers

BOOL CTabPower::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();

	CLoadString LoadString;
	LoadString.LoadString(this, IDS_POWERMETER_6, IDC_POWERMETER_6, IDC_POWERMETER_7, FALSE, FALSE);

	LoadValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTabPower::LoadValue()
{
//	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	
	if (pPointerManager->GetLaserControl() != NULL) {
		m_dAperture = pPointerManager->GetLaserControl()->GetAperture();
		m_dCurrent = pPointerManager->GetLaserControl()->GetCurrent();
		m_dPower = pPointerManager->GetLaserControl()->GetMeasuredPower();
		m_strDate = pPointerManager->GetLaserControl()->GetDate();
//		m_dAperture = pMainFrm->m_pLaserControl->GetAperture();
//		m_dCurrent = pMainFrm->m_pLaserControl->GetCurrent();
//		m_dPower = pMainFrm->m_pLaserControl->GetMeasuredPower();
//		m_strDate = pMainFrm->m_pLaserControl->GetDate();
	}		
	UpdateData(FALSE);
}

void CTabPower::OnRecordingMode() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SAVED_APERTURE)->EnableWindow(TRUE);
	/* º¸·ù */
//	GetDlgItem(IDC_SAVED_POWER)  ->EnableWindow(TRUE);
//	GetDlgItem(IDC_SAVED_CURRENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVED_DATE)  ->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVED_APERTURE)->SetFocus();		
}
