 // DlgTest.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgTest.h"
#include "Lan.h"
/* Only TEST */
#include "Dsp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTest dialog


CDlgTest::CDlgTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTest)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTest)
	DDX_Control(pDX, IDC_TEST, m_btnTest);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTest, CDialog)
	//{{AFX_MSG_MAP(CDlgTest)
	ON_BN_CLICKED(IDC_TEST, OnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTest message handlers

void CDlgTest::OnTest() 
{
	// TODO: Add your control notification handler code here
 	m_pCommunicate = new CLan("Handler Setting");
	m_pCommunicate->StartCommunicate();
	
	/* Only TEST */
//	CDsp *pDsp = new CDsp;
//	pDsp->SetParameterData();

	/* Only TEST */
	int *pData = new int;

	delete pData;
}

BOOL CDlgTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnTest.SetIcon(IDI_ICON_RICO);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
