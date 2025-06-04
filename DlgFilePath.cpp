// DlgFilePath.cpp : implementation file
//

#include "stdafx.h"
#include "MK.h"
#include "DlgFilePath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFilePath dialog


CDlgFilePath::CDlgFilePath(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFilePath::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFilePath)
	m_pathDev = _T("");
	m_pathFont = _T("");
	m_pathMrk = _T("");
	m_pathObj = _T("");
	m_pathScr = _T("");
	m_pathImg = _T("");
	m_pathHpgl = _T("");
	//}}AFX_DATA_INIT
}


void CDlgFilePath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFilePath)
	DDX_Text(pDX, IDC_PATH_DEV, m_pathDev);
	DDX_Text(pDX, IDC_PATH_FONT, m_pathFont);
	DDX_Text(pDX, IDC_PATH_MRK, m_pathMrk);
	DDX_Text(pDX, IDC_PATH_OBJ, m_pathObj);
	DDX_Text(pDX, IDC_PATH_SCR, m_pathScr);
	DDX_Text(pDX, IDC_PATH_IMG, m_pathImg);
	DDX_Text(pDX, IDC_PATH_HPGL, m_pathHpgl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFilePath, CDialog)
	//{{AFX_MSG_MAP(CDlgFilePath)
	ON_BN_CLICKED(IDC_BUTTON_MARKFILE, OnButtonMarkfile)
	ON_BN_CLICKED(IDC_BUTTON_OJBECTFILE, OnButtonOjbectfile)
	ON_BN_CLICKED(IDC_BUTTON_DEVICEFILE, OnButtonDevicefile)
	ON_BN_CLICKED(IDC_BUTTON_SCRIBEFILE, OnButtonScribefile)
	ON_BN_CLICKED(IDC_BUTTON_FONTFILE, OnButtonFontfile)
	ON_BN_CLICKED(IDC_BUTTON_IMG, OnButtonImg)
	ON_BN_CLICKED(IDC_BUTTON_HPGL, OnButtonHpgl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFilePath message handlers

////////////////////////////////////
// Mark File 변경 버튼
void CDlgFilePath::OnButtonMarkfile() 
{
	// TODO: Add your control notification handler code here
	m_pDirSelect = new CDlgDirSelect();
	m_pDirSelect->m_SetPath = m_pathMrk;
	if (m_pDirSelect->DoModal() == IDOK)
	{	// 새로운 path를 받는다
		m_pathMrk = m_pDirSelect->m_dirText ;
		UpdateData(FALSE);
	}
	delete m_pDirSelect;

}
//////////////////////////////////////////
// Object File 변경 버턴
void CDlgFilePath::OnButtonOjbectfile() 
{
	// TODO: Add your control notification handler code here
	m_pDirSelect = new CDlgDirSelect();
	m_pDirSelect->m_SetPath = m_pathObj;
	if (m_pDirSelect->DoModal() == IDOK)
	{	// 새로운 path를 받는다
		m_pathObj = m_pDirSelect->m_dirText ;
		UpdateData(FALSE);
	}
	delete m_pDirSelect;

}
//////////////////////////////////////////
// Device File 변경 버튼
void CDlgFilePath::OnButtonDevicefile() 
{
	// TODO: Add your control notification handler code here
	m_pDirSelect = new CDlgDirSelect();
	m_pDirSelect->m_SetPath = m_pathDev;
	if (m_pDirSelect->DoModal() == IDOK)
	{	// 새로운 path를 받는다
		m_pathDev = m_pDirSelect->m_dirText ;
		UpdateData(FALSE);
	}
	delete m_pDirSelect;	

}
///////////////////////////////////////////
// Scribe File 변경 버튼 
void CDlgFilePath::OnButtonScribefile() 
{
	// TODO: Add your control notification handler code here
	m_pDirSelect = new CDlgDirSelect();
	m_pDirSelect->m_SetPath = m_pathScr;
	if (m_pDirSelect->DoModal() == IDOK)
	{	// 새로운 path를 받는다
		m_pathScr = m_pDirSelect->m_dirText ;
		UpdateData(FALSE);
	}
	delete m_pDirSelect;
	
}
//////////////////////////////////////
// Font File Path 변경 버튼
void CDlgFilePath::OnButtonFontfile() 
{
	// TODO: Add your control notification handler code here
	m_pDirSelect = new CDlgDirSelect();
	m_pDirSelect->m_SetPath = m_pathFont;
	if (m_pDirSelect->DoModal() == IDOK)
	{	// 새로운 path를 받는다
		m_pathFont = m_pDirSelect->m_dirText ;
		UpdateData(FALSE);
	}
	delete m_pDirSelect;	
}

void CDlgFilePath::OnButtonImg() 
{
	// TODO: Add your control notification handler code here
	m_pDirSelect = new CDlgDirSelect();
	m_pDirSelect->m_SetPath = m_pathImg;
	if (m_pDirSelect->DoModal() == IDOK)
	{	// 새로운 path를 받는다
		m_pathImg = m_pDirSelect->m_dirText ;
		UpdateData(FALSE);
	}
	delete m_pDirSelect;	
}

void CDlgFilePath::OnButtonHpgl() 
{
	// TODO: Add your control notification handler code here
	m_pDirSelect = new CDlgDirSelect();
	m_pDirSelect->m_SetPath = m_pathHpgl;
	if (m_pDirSelect->DoModal() == IDOK)
	{	// 새로운 path를 받는다
		m_pathHpgl = m_pDirSelect->m_dirText ;
		UpdateData(FALSE);
	}
	delete m_pDirSelect;	
}
