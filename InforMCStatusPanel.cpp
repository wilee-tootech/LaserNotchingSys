// InforMCStatusPanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "InforMCStatusPanel.h"


// CInforMCStatusPanel

IMPLEMENT_DYNCREATE(CInforMCStatusPanel, CProjectBaseView)

CInforMCStatusPanel::CInforMCStatusPanel()
	: CProjectBaseView(CInforMCStatusPanel::IDD)
{

}

CInforMCStatusPanel::~CInforMCStatusPanel()
{
}

void CInforMCStatusPanel::DoDataExchange(CDataExchange* pDX)
{
	CProjectBaseView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CInforMCStatusPanel, CProjectBaseView)
	ON_WM_ERASEBKGND()
	ON_STN_CLICKED(IDC_STATIC_RECT, &CInforMCStatusPanel::OnStnClickedStaticRect)
END_MESSAGE_MAP()


// CInforMCStatusPanel 진단입니다.

#ifdef _DEBUG
void CInforMCStatusPanel::AssertValid() const
{
	CProjectBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CInforMCStatusPanel::Dump(CDumpContext& dc) const
{
	CProjectBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInforMCStatusPanel 메시지 처리기입니다.


BOOL CInforMCStatusPanel::OnEraseBkgnd(CDC* pDC)
{
	if(!m_background.m_hObject) return TRUE;

	CRect rect;
	GetClientRect(&rect);

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dc.SelectObject(&m_background);

	BITMAP bmap;
	m_background.GetBitmap(&bmap);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, bmap.bmWidth, bmap.bmHeight, SRCCOPY);

	dc.SelectObject(pOldBitmap);
	return TRUE;
}


void CInforMCStatusPanel::OnInitialUpdate()
{
	CProjectBaseView::OnInitialUpdate();

	SetScrollSizes(MM_TEXT, CSize(0, 0));
    ShowScrollBar(SB_BOTH, FALSE);

	

	m_background.LoadBitmap(IDB_BITMAP_MAIN_BG);

	LOGFONT lf;

	this->GetFont()->GetLogFont(&lf);

	lf.lfHeight = 15;
	lf.lfWeight = FW_BOLD;

	wsprintf(lf.lfFaceName, _T("%s"), TEXT("Tahoma"));

	CFont NewFont;

	NewFont.CreateFontIndirect(&lf);

	CWnd* pWnd = this->GetWindow(GW_CHILD);

	while (pWnd)
	{
		pWnd->SetFont(&NewFont);
		pWnd = pWnd->GetNextWindow();
	}

	NewFont.Detach();


	GetDlgItem(IDC_STATIC_RECT)->GetWindowRect(m_rect);

	ScreenToClient(m_rect);

	m_pInforSetup_IOPanel = new CInforSetup_IOPanel(this);

	m_pInforSetup_IOPanel->Create(IDD_INFORSETUP_IOPANEL, this);

	m_pInforSetup_IOPanel->MoveWindow(m_rect, TRUE);

	m_pInforSetup_IOPanel->ShowWindow(SW_SHOW); 

	m_pDustCollector = new CDustCollector(this);

	m_pDustCollector->Create(IDD_TAP_DUSTTRAP, this);

	m_pDustCollector->MoveWindow(m_rect, TRUE);
	m_pDustCollector->ShowWindow(SW_HIDE);



	


}


void CInforMCStatusPanel::OnStnClickedStaticRect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
BEGIN_EVENTSINK_MAP(CInforMCStatusPanel, CProjectBaseView)
	ON_EVENT(CInforMCStatusPanel, IDC_CTPUSH_IO, DISPID_CLICK, CInforMCStatusPanel::ClickCtpushIo, VTS_NONE)
	ON_EVENT(CInforMCStatusPanel, IDC_CTPUSH_OTHERS, DISPID_CLICK, CInforMCStatusPanel::ClickCtpushOthers, VTS_NONE)
END_EVENTSINK_MAP()


void CInforMCStatusPanel::ClickCtpushIo()
{
	m_pDustCollector->ShowWindow(SW_HIDE);
	m_pInforSetup_IOPanel->ShowWindow(SW_SHOW);
}


void CInforMCStatusPanel::ClickCtpushOthers()
{
	m_pDustCollector->ShowWindow(SW_SHOW);
	m_pInforSetup_IOPanel->ShowWindow(SW_HIDE);
}
