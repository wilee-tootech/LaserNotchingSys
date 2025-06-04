// DlgAmkorDir.cpp : implementation file
//

#include "stdafx.h"
#include "Options.h"
#include "DlgAmkorDir.h"
#include "DlgSelectDir.h"
#include <direct.h> // 2003.11.03 현재 작업 디렉토리 알아오기
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAmkorDir dialog


CDlgAmkorDir::CDlgAmkorDir(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAmkorDir::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAmkorDir)
	m_strEditDir = _T("");
	m_strRscDir = _T("");
	m_strFontDir = _T("");
	m_strHpglDir = _T("");
	m_strTmpDir = _T("");
	m_strPrjDir = _T("");
	m_strFieldSize = _T("");
	m_strAmkorField = _T("");
	m_strCompanyCode = _T("");
	m_strPenFile = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAmkorDir::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAmkorDir)
	DDX_Text(pDX, IDC_EDIT_EDIT_DIR, m_strEditDir);
	DDX_Text(pDX, IDC_EDIT_RSC_DIR, m_strRscDir);
	DDX_Text(pDX, IDC_EDIT_FONT_DIR, m_strFontDir);
	DDX_Text(pDX, IDC_EDIT_HPGL_DIR, m_strHpglDir);
	DDX_Text(pDX, IDC_EDIT_TMP_DIR, m_strTmpDir);
	DDX_Text(pDX, IDC_EDIT_PRJ_DIR, m_strPrjDir);
	DDX_Text(pDX, IDC_EDIT_FIELD_SET, m_strFieldSize);
	DDX_Text(pDX, IDC_EDIT_FIELD_SET, m_strAmkorField);
	DDX_Text(pDX, IDC_EDIT_COMPANY, m_strCompanyCode);
	DDX_Text(pDX, IDC_EDIT_PEN_DIR, m_strPenFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAmkorDir, CDialog)
	//{{AFX_MSG_MAP(CDlgAmkorDir)
	ON_BN_CLICKED(IDC_BUTTON_EDITDIR, OnButtonEditdir)
	ON_BN_CLICKED(IDC_BUTTON_RSC_DIR, OnButtonRscDir)
	ON_BN_CLICKED(IDC_BUTTON_FONT_DIR, OnButtonFontDir)
	ON_BN_CLICKED(IDC_BUTTON_HPGL_DIR, OnButtonHpglDir)
	ON_BN_CLICKED(IDC_BUTTON_TMP_DIR, OnButtonTmpDir)
	ON_BN_CLICKED(IDC_BUTTON_PRJ_DIR, OnButtonPrjDir)
	ON_BN_CLICKED(IDC_BUTTON_PEN_DIR, OnButtonPenDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAmkorDir message handlers

void CDlgAmkorDir::OnButtonEditdir() 
{
	CDlgSelectDir dlg;
	if (dlg.DoModal() == IDOK) {
		GetDlgItem(IDC_EDIT_EDIT_DIR)->SetWindowText(dlg.m_SetPath);
	}
	UpdateData(TRUE);
	
}

void CDlgAmkorDir::OnButtonRscDir() 
{
CDlgSelectDir dlg;
	if (dlg.DoModal() == IDOK) {
		GetDlgItem(IDC_EDIT_RSC_DIR)->SetWindowText(dlg.m_SetPath);
	}
	UpdateData(TRUE);
}

void CDlgAmkorDir::OnButtonFontDir() 
{
CDlgSelectDir dlg;
	if (dlg.DoModal() == IDOK) {
		GetDlgItem(IDC_EDIT_FONT_DIR)->SetWindowText(dlg.m_SetPath);
	}	
	UpdateData(TRUE);
}

void CDlgAmkorDir::OnButtonHpglDir() 
{
CDlgSelectDir dlg;
	if (dlg.DoModal() == IDOK) {
		GetDlgItem(IDC_EDIT_HPGL_DIR)->SetWindowText(dlg.m_SetPath);
	}	
	UpdateData(TRUE);
}

void CDlgAmkorDir::OnButtonTmpDir() 
{
CDlgSelectDir dlg;
	if (dlg.DoModal() == IDOK) {
		GetDlgItem(IDC_EDIT_TMP_DIR)->SetWindowText(dlg.m_SetPath);
	}
	UpdateData(TRUE);
}

void CDlgAmkorDir::OnButtonPrjDir() 
{
	CDlgSelectDir dlg;
	if (dlg.DoModal() == IDOK) {
		GetDlgItem(IDC_EDIT_PRJ_DIR)->SetWindowText(dlg.m_SetPath);
	}	
	UpdateData(TRUE);
	
}

void CDlgAmkorDir::OnOK() 
{
	// TODO: Add extra validation here
    UpdateData(TRUE);
	GetDlgItemText(IDC_EDIT_FIELD_SET, m_strAmkorField);
	GetDlgItemText(IDC_EDIT_COMPANY, m_strCompanyCode);

	CDialog::OnOK();
}

void CDlgAmkorDir::OnButtonPenDir() 
{
/*	char cwd[256];
	_getcwd(cwd, 256);
	static char szFilters[] = "scr 파일(*.scr)";
	CString m_strCwd; // 현재 작업 디렉토리 저장
	CString strFileName;
	m_strCwd = cwd;

///	char buffer[257];
// ::ZeroMemory(buffer, 257);
//    ::GetCurrentDirectory(256, buffer);

	//m_strCwd.MakeLower();

	CFileDialog fileDlg(TRUE, NULL, m_strCwd+"\\*.scr" , OFN_OVERWRITEPROMPT, szFilters, NULL);
	if (IDOK == fileDlg.DoModal())
		//strFileName.Format("%s\\%s",m_strCwd,fileDlg.GetFileName());
		strFileName = fileDlg.GetPathName(); 
	else
	    strFileName = _T("");

	GetDlgItem(IDC_EDIT_PEN_DIR)->SetWindowText(strFileName);
	UpdateData(TRUE);
	*/
	CDlgSelectDir dlg;
	if (dlg.DoModal() == IDOK) {
		GetDlgItem(IDC_EDIT_PEN_DIR)->SetWindowText(dlg.m_SetPath);
	}	
	UpdateData(TRUE);
}
