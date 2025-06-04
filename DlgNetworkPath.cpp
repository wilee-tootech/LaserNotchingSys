// DlgNetworkPath.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgNetworkPath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNetworkPath dialog


CDlgNetworkPath::CDlgNetworkPath(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNetworkPath::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNetworkPath)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgNetworkPath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNetworkPath)
	DDX_Control(pDX, IDC_NETDRIVE_TREE, m_ctrFileTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNetworkPath, CDialog)
	//{{AFX_MSG_MAP(CDlgNetworkPath)
	ON_MESSAGE(WM_USER_PATHCHANGED, OnChangePath)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgNetworkPath::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNetworkPath message handlers
LRESULT CDlgNetworkPath::OnChangePath(WPARAM wParam, LPARAM lParam)
{
	HTREEITEM hItem;
	hItem = (HTREEITEM)wParam;

	m_strNetworkPath = m_ctrFileTree.GetPathFromNode(hItem);
	return TRUE;
}

BOOL CDlgNetworkPath::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctrFileTree.SetImageList();
	m_ctrFileTree.InitDriveCtrl();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CDlgNetworkPath::GetNetworkPath()
{
	return m_strNetworkPath;
}



void CDlgNetworkPath::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}
