// DlgSelectDir.cpp : implementation file
//

#include "stdafx.h"
#include "DlgSelectDir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectDir dialog
#include "def.h"

CDlgSelectDir::CDlgSelectDir(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectDir::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelectDir)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSelectDir::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelectDir)
	DDX_Control(pDX, IDC_DIRECTORY, m_fileTreeCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelectDir, CDialog)
	//{{AFX_MSG_MAP(CDlgSelectDir)
	ON_MESSAGE(WM_USER_PATHCHANGED, OnChangePath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectDir message handlers

BOOL CDlgSelectDir::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_fileTreeCtrl.SetImageList();
	m_fileTreeCtrl.InitDriveCtrl();
	m_fileTreeCtrl.SetFilePathTree(m_SetPath);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CDlgSelectDir::OnChangePath(WPARAM wParam, LPARAM lParam)
{
	HTREEITEM hItem;
	hItem = (HTREEITEM)wParam;

	m_SetPath = m_fileTreeCtrl.GetPathFromNode(hItem);

	return 0;
}

