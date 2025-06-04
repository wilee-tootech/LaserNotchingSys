// InfoMESPanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "InfoMESPanel.h"


// CInfoMESPanel

IMPLEMENT_DYNCREATE(CInfoMESPanel, CProjectBaseView)

CInfoMESPanel::CInfoMESPanel()
	: CProjectBaseView(CInfoMESPanel::IDD)
{
}

CInfoMESPanel::~CInfoMESPanel()
{
}

void CInfoMESPanel::DoDataExchange(CDataExchange* pDX)
{
	CProjectBaseView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CInfoMESPanel, CProjectBaseView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CInfoMESPanel 진단입니다.

#ifdef _DEBUG
void CInfoMESPanel::AssertValid() const
{
	CProjectBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoMESPanel::Dump(CDumpContext& dc) const
{
	CProjectBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfoMESPanel 메시지 처리기입니다.


void CInfoMESPanel::OnInitialUpdate()
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

	m_pMES = new CDlgMES(this);

	m_pMES->Create(IDD_DLG_MES, this);

	m_pMES->MoveWindow(m_rect, TRUE);

	m_pMES->ShowWindow(SW_SHOW); 

	
}


BOOL CInfoMESPanel::OnEraseBkgnd(CDC* pDC)
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
