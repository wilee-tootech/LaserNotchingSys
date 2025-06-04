// TimeMessage.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "TimeMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeMessage dialog


CTimeMessage::CTimeMessage(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeMessage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeMessage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_stMessage = _T("");
	m_iSecond = 5;
}

CTimeMessage::CTimeMessage(CWnd* pParent, CString message)
{
	m_stMessage = message;
}


void CTimeMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeMessage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimeMessage, CDialog)
	//{{AFX_MSG_MAP(CTimeMessage)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeMessage message handlers

BOOL CTimeMessage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString str;

	SetDlgItemText(IDC_ST_MESSAGE, m_stMessage);
	str.Format(str, "%d 초 후에 자동으로 꺼집니다.", m_iSecond);
	SetDlgItemText(IDD_DLG_TIME_MESSAGE, str);

	SetTimer(0, 1000, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTimeMessage::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 0)
	{
		CString str;
		str.Format(str, "%d 초 후에 자동으로 꺼집니다.", --m_iSecond);
		if (m_iSecond < 0) 
		{
			CDialog::OnOK();
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}
