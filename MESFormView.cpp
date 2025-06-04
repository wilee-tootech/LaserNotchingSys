// MESFormView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "MESFormView.h"
#include "ProjectBaseView.h"


// CMESFormView

IMPLEMENT_DYNCREATE(CMESFormView, CProjectBaseView)

CMESFormView::CMESFormView()
	: CProjectBaseView(CMESFormView::IDD)
{
	m_pCurWnd = NULL;
}

CMESFormView::~CMESFormView()
{
}

void CMESFormView::DoDataExchange(CDataExchange* pDX)
{
	CProjectBaseView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_CTRL, m_tabCtrl);
}

BEGIN_MESSAGE_MAP(CMESFormView, CProjectBaseView)
	ON_BN_CLICKED(IDOK, &CMESFormView::OnBnClickedOk)
	ON_WM_ERASEBKGND()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CTRL, &CMESFormView::OnTcnSelchangeTabCtrl)
END_MESSAGE_MAP()


// CMESFormView �����Դϴ�.

#ifdef _DEBUG
void CMESFormView::AssertValid() const
{
	CProjectBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CMESFormView::Dump(CDumpContext& dc) const
{
	CProjectBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMESFormView �޽��� ó�����Դϴ�.


void CMESFormView::OnInitialUpdate()
{
	CProjectBaseView::OnInitialUpdate();

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


	m_tabCtrl.InsertItem( E_MES_SETTING		, _T("SETTING") );
	m_tabCtrl.InsertItem( E_MES_SETTING2	, _T("SETTING2") );

	CRect rt;

	m_tabCtrl.GetClientRect(&rt);

	m_TabSetting		.Create(IDD_TAB_SETTING					, &m_tabCtrl);
	m_TabPowermeter		.Create(IDD_TAB_POWERMETER				, &m_tabCtrl);
	
	m_TabSetting		.SetWindowPos(NULL, 5, 40, rt.Width() -10, rt.Height() - 45, SWP_NOZORDER);
	m_TabPowermeter.SetWindowPos(NULL, 5, 40, rt.Width() -10, rt.Height() - 45, SWP_NOZORDER);

	m_tabCtrl.SetItemSize(CSize(150,30));
	m_tabCtrl.ModifyStyle(0, TCS_FIXEDWIDTH);

	m_pCurWnd = &m_TabSetting;

	Init();

}
//
//
//BOOL CMESFormView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
//{
//	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
//
//	return CProjectBaseView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
//}

void CMESFormView::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


BOOL CMESFormView::OnEraseBkgnd(CDC* pDC)
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

	//return CProjectBaseView::OnEraseBkgnd(pDC);
}



void CMESFormView::Init()
{
	if(m_pCurWnd)
	{
		m_pCurWnd->ShowWindow(SW_HIDE);
	}
	else
	{
		m_pCurWnd = &m_TabSetting;
	}

	m_pCurWnd = &m_TabSetting;
	m_pCurWnd->ShowWindow(SW_SHOW);
	m_tabCtrl.SetCurSel(E_MES_SETTING);


	//////////////////////////////////////////////////////////////////////////
	m_tabCtrl.ModifyStyle(0, TCS_OWNERDRAWFIXED);

	
	
}


void CMESFormView::OnTcnSelchangeTabCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nIndex = m_tabCtrl.GetCurSel();

	if(m_pCurWnd)
	{
		m_pCurWnd->ShowWindow(SW_HIDE);
		m_pCurWnd = NULL;
	}

	switch(nIndex)
	{

	case E_MES_SETTING:
		m_TabSetting.ShowWindow(SW_SHOW);
		m_pCurWnd = &m_TabSetting;

		break;

	case E_MES_SETTING2:
		m_TabPowermeter.ShowWindow(SW_SHOW);
		m_pCurWnd = &m_TabPowermeter;

		break;
	}

	*pResult = 0;
}
