// DlgDirSelect.cpp : implementation file
//

#include "stdafx.h"
#include "MK.h"
#include "DlgDirSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDirSelect dialog
#include "def.h"

CDlgDirSelect::CDlgDirSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDirSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDirSelect)
	m_dirText = _T("");

	//}}AFX_DATA_INIT
		m_SetPath = "";
}


void CDlgDirSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDirSelect)
	DDX_Control(pDX, IDC_DIR_TREE, m_fileTreeCtrl);
	DDX_Text(pDX, IDC_DIR_TEXT, m_dirText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDirSelect, CDialog)
	//{{AFX_MSG_MAP(CDlgDirSelect)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_PATHCHANGED, OnChangePath)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDirSelect message handlers

BOOL CDlgDirSelect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_fileTreeCtrl.SetImageList();
	m_fileTreeCtrl.InitDriveCtrl();

	
	if( m_SetPath == "") m_SetPath= "c:\\";
	
	m_dirText=m_SetPath;
	m_fileTreeCtrl.SetFilePathTree(m_SetPath);
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDirSelect::OnChangePath(WPARAM wParam, LPARAM lParam)
{
	HTREEITEM hItem;
	hItem = (HTREEITEM)wParam;

	m_dirText = m_fileTreeCtrl.GetPathFromNode(hItem);
	m_strDir = m_dirText;
	
	UpdateData(FALSE);
}

void CDlgDirSelect::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
