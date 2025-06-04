// DlgMsgDC.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "DlgMsgDC.h"
#include "./Control/cttextctrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMsgDC dialog


CDlgMsgDC::CDlgMsgDC(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMsgDC::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMsgDC)
		// NOTE: the ClassWizard will add member initialization here
	bFlag = true;
	//}}AFX_DATA_INIT
}


void CDlgMsgDC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMsgDC)
	DDX_Control(pDX, IDC_STATIC_MSG, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMsgDC, CDialog)
	//{{AFX_MSG_MAP(CDlgMsgDC)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMsgDC message handlers

void CDlgMsgDC::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

int CDlgMsgDC::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

BOOL CDlgMsgDC::Create(CWnd* pParentWnd) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}

void CDlgMsgDC::SetMessage(CString str)
{
	SetDlgItemText(IDC_STATIC_MSG, str);
	m_strMessage = str;
}

void CDlgMsgDC::ClearMessage(void)
{
	SetDlgItemText(IDC_STATIC_MSG, "");
}

BOOL CDlgMsgDC::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	/*Font.CreateFont( 30,0,0,255,FW_BOLD,FALSE,FALSE,0,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH,
        "굴림" );
	
	GetDlgItem(IDC_STATIC_MSG)->SetFont(&Font);*/

	//((CBlinkStatic *)GetDlgItem(IDC_STATIC_MSG))->SetForeColor(RGB(255,255,0));
	//((CBlinkStatic *)GetDlgItem(IDC_STATIC_MSG))->SetBackColor(RGB(0,0,0));
	//((CBlinkStatic *)GetDlgItem(IDC_STATIC_MSG))->SetInterval(500); 
	
	CRect rc;
    GetWindowRect(rc);

	SetWindowPos(NULL, rc.Width()/2, rc.Height()/2, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	SetTimer(1,900,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
BEGIN_EVENTSINK_MAP(CDlgMsgDC, CDialog)
	ON_EVENT(CDlgMsgDC, IDC_OK, DISPID_CLICK, CDlgMsgDC::ClickOk, VTS_NONE)
END_EVENTSINK_MAP()


void CDlgMsgDC::ClickOk()
{
	ShowWindow(SW_HIDE);
}


void CDlgMsgDC::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent == 1)
	{
		CCttextctrl* pCcText	= NULL;
		pCcText = (CCttextctrl*)GetDlgItem(	IDC_STATIC_MSG); 
		if(bFlag){
			pCcText->SetForeColor(RGB(255,255,0));
			pCcText->SetBackColor(RGB(0,0,0));
			pCcText->SetCaption(_T(m_strMessage));
			bFlag = 0;
		}
		else{
			pCcText->SetForeColor(RGB(255,0,0));
			pCcText->SetBackColor(RGB(0,0,0));
			pCcText->SetCaption(_T(m_strMessage));
			bFlag = 1;
		}


	}
	CDialog::OnTimer(nIDEvent);
}
