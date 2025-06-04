// GridDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "MK.h"	//#include "FontEditor.h"
#include "GridDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridDlg dialog

CGridDlg::CGridDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGridDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGridDlg)
	m_Check_Grid = FALSE;
	m_Fixat_Grid = FALSE;
	m_GridHeight = 0;
	m_GridWidth = 0;
	//}}AFX_DATA_INIT
}

void CGridDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGridDlg)
	DDX_Check(pDX, IDC_CHECK_GRID, m_Check_Grid);
	DDX_Check(pDX, IDC_FIXAT_GRID, m_Fixat_Grid);
	DDX_Text(pDX, IDC_HEIGHT, m_GridHeight);
	DDX_Text(pDX, IDC_WIDTH, m_GridWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGridDlg, CDialog)
	//{{AFX_MSG_MAP(CGridDlg)
	ON_BN_CLICKED(IDC_CHECK_GRID, OnCheckGrid)
	ON_EN_KILLFOCUS(IDC_HEIGHT, OnKillfocusHeight)
	ON_EN_KILLFOCUS(IDC_WIDTH, OnKillfocusWidth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridDlg message handlers

BOOL CGridDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_Check_Grid == FALSE)
	{
		GetDlgItem(IDC_WIDTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_HEIGHT)->EnableWindow(FALSE);
	} else
	{
		GetDlgItem(IDC_WIDTH)->EnableWindow(TRUE);
		GetDlgItem(IDC_HEIGHT)->EnableWindow(TRUE);
	}
/*
	GetDlgItem(IDC_WIDTH)->SetWindowText("30");
	GetDlgItem(IDC_HEIGHT)->SetWindowText("30");
*/	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGridDlg::OnCheckGrid() 
{
	// TODO: Add your control notification handler code here
	if (((CButton*)GetDlgItem(IDC_CHECK_GRID))->GetCheck() == 1) // 체크 상황이면 아래 입력 박스를 enable
	{
		GetDlgItem(IDC_WIDTH)->EnableWindow(TRUE);
		GetDlgItem(IDC_HEIGHT)->EnableWindow(TRUE);
	} else
	{
		GetDlgItem(IDC_WIDTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_HEIGHT)->EnableWindow(FALSE);
	}	
}

void CGridDlg::OnKillfocusHeight() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_GridHeight < 10 || m_GridHeight > 200)
	{
		GetDlgItem(IDC_HEIGHT)->SetWindowText("30");
		AfxMessageBox("Input numeral letters from 10 to 200!",MB_OK);
	}	
}


void CGridDlg::OnKillfocusWidth() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_GridWidth < 10 || m_GridWidth > 200)
	{
		GetDlgItem(IDC_WIDTH)->SetWindowText("30");
		AfxMessageBox("Input numeral letters from 10 to 200!",MB_OK);
	}			
}
