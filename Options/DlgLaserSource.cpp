// DlgLaserSource.cpp : implementation file
//

#include "stdafx.h"
#include "Options.h"
#include "DlgLaserSource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLaserSource dialog


CDlgLaserSource::CDlgLaserSource(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLaserSource::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLaserSource)
	m_iHead = -1;
	m_iKindOfLaser = -1;
	m_iLaserSource = -1;
	m_LowLimitPower = 0.0;
	m_MaxLimitPower = 0.0;
	m_NormalLimitPower = 0.0;
	m_iRtcBorad = -1;
	//}}AFX_DATA_INIT
}


void CDlgLaserSource::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLaserSource)
	DDX_Radio(pDX, IDC_SINGLE_HEAD, m_iHead);
	DDX_Radio(pDX, IDC_YAG, m_iKindOfLaser);
	DDX_Radio(pDX, IDC_SPECTRON, m_iLaserSource);
	DDX_Text(pDX, IDC_EDIT_POWER_L, m_LowLimitPower);
	DDX_Text(pDX, IDC_EDIT_POWER_M, m_MaxLimitPower);
	DDX_Text(pDX, IDC_EDIT_POWER_N, m_NormalLimitPower);
	DDX_Radio(pDX, IDC_SCANLAB, m_iRtcBorad);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLaserSource, CDialog)
	//{{AFX_MSG_MAP(CDlgLaserSource)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLaserSource message handlers

BOOL CDlgLaserSource::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_iKindOfLaser == 1) {
//		EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLaserSource::EnableWindow(BOOL bFlag)
{
	GetDlgItem(IDC_SINGLE_HEAD)->EnableWindow(bFlag);
	GetDlgItem(IDC_DUAL_HEAD)->EnableWindow(bFlag);
	GetDlgItem(IDC_SPECTRON)->EnableWindow(bFlag);
	GetDlgItem(IDC_ROFIN)->EnableWindow(bFlag);
	GetDlgItem(IDC_QUANTRONIX)->EnableWindow(bFlag);
	GetDlgItem(IDC_LEE)->EnableWindow(bFlag);
	GetDlgItem(IDC_HANA)->EnableWindow(bFlag);
	
}

void CDlgLaserSource::OnOK() 
{
	CDialog::OnOK();
}

