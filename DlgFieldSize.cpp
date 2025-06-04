// DlgFieldSize.cpp : implementation file
//

#include "stdafx.h"
#include "mk.h"
#include "DlgFieldSize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFieldSize dialog


CDlgFieldSize::CDlgFieldSize(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFieldSize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFieldSize)
	m_maxField = 0;
	m_maxMmSize = 0;
	//}}AFX_DATA_INIT
}


void CDlgFieldSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFieldSize)
	DDX_Text(pDX, IDC_MAX_FIELD_SIZE, m_maxField);
	DDV_MinMaxInt(pDX, m_maxField, 1000, 65535);
	DDX_Text(pDX, IDC_MAX_MM_SIZE, m_maxMmSize);
	DDV_MinMaxInt(pDX, m_maxMmSize, 10, 220);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFieldSize, CDialog)
	//{{AFX_MSG_MAP(CDlgFieldSize)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFieldSize message handlers
