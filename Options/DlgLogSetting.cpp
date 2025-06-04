// DlgLogSetting.cpp : implementation file
//

#include "stdafx.h"
#include "Options.h"
#include "DlgLogSetting.h"
#include "DlgSelectDir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLogSetting dialog


CDlgLogSetting::CDlgLogSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogSetting)
	m_bAutoEnd = FALSE;
	m_bAutoEndEvent = FALSE;
	m_bAutoStart = FALSE;
	m_iAutoEnd = 0;
	m_iAutoEndEvent = 0;
	m_iAutoStart = 0;
	m_iLaserError = 0;
	m_iManualEnd = 0;
	m_iManualStart = 0;
	m_iWaitEnd = 0;
	m_iWaitStart = 0;
	m_bLaserError = FALSE;
	m_bManualEnd = FALSE;
	m_bManualStart = FALSE;
	m_iSavePeriod = 0;
	m_bWaitEnd = FALSE;
	m_bWaitStart = FALSE;
	m_strSaveDir = _T("");
	//}}AFX_DATA_INIT
}


void CDlgLogSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogSetting)
	DDX_Check(pDX, IDC_AUTO_END, m_bAutoEnd);
	DDX_Check(pDX, IDC_AUTO_END_EVENT, m_bAutoEndEvent);
	DDX_Check(pDX, IDC_AUTO_START, m_bAutoStart);
	DDX_Text(pDX, IDC_CODE_AUTOEND, m_iAutoEnd);
	DDX_Text(pDX, IDC_CODE_AUTOENDEVENT, m_iAutoEndEvent);
	DDX_Text(pDX, IDC_CODE_AUTOSTART, m_iAutoStart);
	DDX_Text(pDX, IDC_CODE_LASERERROR, m_iLaserError);
	DDX_Text(pDX, IDC_CODE_MANUALEND, m_iManualEnd);
	DDX_Text(pDX, IDC_CODE_MANUALSTART, m_iManualStart);
	DDX_Text(pDX, IDC_CODE_WAITEND, m_iWaitEnd);
	DDX_Text(pDX, IDC_CODE_WAITSTART, m_iWaitStart);
	DDX_Check(pDX, IDC_LASER_ERROR, m_bLaserError);
	DDX_Check(pDX, IDC_MANUAL_END, m_bManualEnd);
	DDX_Check(pDX, IDC_MANUAL_START, m_bManualStart);
	DDX_Text(pDX, IDC_SAVE_PERIOD, m_iSavePeriod);
	DDX_Check(pDX, IDC_WAIT_END, m_bWaitEnd);
	DDX_Check(pDX, IDC_WAIT_START, m_bWaitStart);
	DDX_Text(pDX, IDC_SAVE_DIR, m_strSaveDir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgLogSetting)
	ON_BN_CLICKED(IDC_SEL_DIR, OnSelDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogSetting message handlers

void CDlgLogSetting::OnSelDir() 
{
	// TODO: Add your control notification handler code here
	CDlgSelectDir dlg;
	if (dlg.DoModal() == IDOK) {
		GetDlgItem(IDC_SAVE_DIR)->SetWindowText(dlg.m_SetPath);
	}
}

void CDlgLogSetting::OnOK() 
{
	// TODO: Add extra validation here
	CString strTemp;
	UpdateData(TRUE);

	if (FindSameCode(m_iAutoStart))
		return;
	if (FindSameCode(m_iAutoEnd))
		return;
	if (FindSameCode(m_iAutoEndEvent))
		return;
	if (FindSameCode(m_iManualStart))
		return;
	if (FindSameCode(m_iManualEnd))
		return;
	if (FindSameCode(m_iWaitStart))
		return;
	if (FindSameCode(m_iWaitEnd))
		return;
	if (FindSameCode(m_iLaserError))
		return;

	GetDlgItem(IDC_SAVE_DIR)->GetWindowText(strTemp);
	if (strTemp == "")
		return;

	CDialog::OnOK();
}

BOOL CDlgLogSetting::FindSameCode(int iCode)
{
	// 쩌비 이 방법 밖에 없나 ㅡㅡ;;
	int iCount = 0;

	if (m_iAutoStart == iCode)
		iCount++;
	if (m_iAutoEnd == iCode)
		iCount++;
	if (m_iAutoEndEvent == iCode)
		iCount++;
	if (m_iManualStart == iCode)
		iCount++;
	if (m_iManualEnd == iCode)
		iCount++;
	if (m_iWaitStart == iCode)
		iCount++;
	if (m_iWaitEnd == iCode)
		iCount++;
	if (m_iLaserError == iCode)
		iCount++;

	if (iCount == 1)
		return FALSE;
	else 
		return TRUE;
}
