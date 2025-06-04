// IOCheck.cpp : implementation file
//

#include "stdafx.h"
#include "mk.h"
#include "IOCheck.h"
#include "MainFrm.h"
#include "MKDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IOCheck dialog


IOCheck::IOCheck(CWnd* pParent /*=NULL*/)
	: CDialog(IOCheck::IDD, pParent)
{
	//{{AFX_DATA_INIT(IOCheck)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	

}


void IOCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(IOCheck)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(IOCheck, CDialog)
	//{{AFX_MSG_MAP(IOCheck)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IOCheck message handlers

void IOCheck::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMKDoc * pDoc = (CMKDoc*)pFrame->GetActiveDocument();
	pDoc->m_pDsp->autoMarking();
	Sleep(3);
	//pDoc->m_pDsp->StopAutoMark();

	
	if(	pDoc->m_pDsp->GetReset() ) GetDlgItem(IDC_STATIC_HANDLER_RESET)->SetWindowText("High");
	else GetDlgItem(IDC_STATIC_HANDLER_RESET)->SetWindowText("Low");
	Sleep(1);

	if( pDoc->m_pDsp->GetVisionReadyFlag() ) GetDlgItem(IDC_STATIC_VISION_READY)->SetWindowText("High");
	else GetDlgItem(IDC_STATIC_VISION_READY)->SetWindowText("Low");
	Sleep(1);



	if(pDoc->m_pDsp->GetStartFlag() ) GetDlgItem(IDC_STATIC_MARKSTART)->SetWindowText("High");
	else GetDlgItem(IDC_STATIC_MARKSTART)->SetWindowText("Low");
	Sleep(1);
	
	CString strTemp;
	strTemp.Format("%d",pDoc->m_pDsp->GetIO() );
	GetDlgItem(IDC_STATIC_IO)->SetWindowText(strTemp);

		
	Sleep(50);
	pDoc->m_pDsp->StopAutoMark();

		

	CDialog::OnTimer(nIDEvent);
}

BOOL IOCheck::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetTimer(0,2000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
