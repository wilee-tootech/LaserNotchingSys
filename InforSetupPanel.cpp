// InforSetupPanel.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "InforSetupPanel.h"

#include "./NX_CONFIRM/Confirm.h"
#include "./NX_KEYPAD/AlphaKeyPad.h"
#include "./NX_KEYPAD/NumberKeyPad.h"
#include "./Include/EXTERN/FileMgr.h"

// CInforSetupPanel

IMPLEMENT_DYNCREATE(CInforSetupPanel, CProjectBaseView)

CInforSetupPanel::CInforSetupPanel()
	: CProjectBaseView(CInforSetupPanel::IDD)
{

}

CInforSetupPanel::~CInforSetupPanel()
{
}

void CInforSetupPanel::DoDataExchange(CDataExchange* pDX)
{
	CProjectBaseView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CInforSetupPanel, CProjectBaseView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CInforSetupPanel �����Դϴ�.

#ifdef _DEBUG
void CInforSetupPanel::AssertValid() const
{
	CProjectBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CInforSetupPanel::Dump(CDumpContext& dc) const
{
	CProjectBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInforSetupPanel �޽��� ó�����Դϴ�.


BOOL CInforSetupPanel::OnEraseBkgnd(CDC* pDC)
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


void CInforSetupPanel::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
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

	m_pDlgIPGDualLaser = new CDlgIPGDualLaser(this);

	m_pDlgIPGDualLaser->Create(IDD_DLG_IPG_LASER_DUAL, this);

	IniUtil _iniUtil;
	CString strSiteName;
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("siteName"), sitePath, strSiteName);
	if(strSiteName == "SDI_POUCH")
	{
		m_rect.right = m_rect.right - 1170;
	}
	m_pDlgIPGDualLaser->MoveWindow(m_rect, TRUE);

	m_pDlgIPGDualLaser->ShowWindow(SW_SHOW);  

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}
BEGIN_EVENTSINK_MAP(CInforSetupPanel, CProjectBaseView)
	ON_EVENT(CInforSetupPanel, IDC_CTPUSH_LASER, DISPID_CLICK, CInforSetupPanel::ClickCtpushLaser, VTS_NONE)
END_EVENTSINK_MAP()


void CInforSetupPanel::ClickCtpushLaser()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
