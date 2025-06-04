// InforParaPanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "InforParaPanel.h"
#include "ProjectBaseView.h"



IMPLEMENT_DYNCREATE(CInforParaPanel, CProjectBaseView)

CInforParaPanel::CInforParaPanel()
	: CProjectBaseView(CInforParaPanel::IDD)
{
	m_pCurWnd = NULL;
}

CInforParaPanel::~CInforParaPanel()
{
}

void CInforParaPanel::DoDataExchange(CDataExchange* pDX)
{
	CProjectBaseView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_CTRL, m_tabCtrl);
}

BEGIN_MESSAGE_MAP(CInforParaPanel, CProjectBaseView)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON1, &CInforParaPanel::OnBnClickedButton1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CTRL, &CInforParaPanel::OnTcnSelchangeTabCtrl)
END_MESSAGE_MAP()


// CInforParaPanel 진단입니다.

#ifdef _DEBUG
void CInforParaPanel::AssertValid() const
{
	CProjectBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CInforParaPanel::Dump(CDumpContext& dc) const
{
	CProjectBaseView::Dump(dc);
}
#endif
#endif //_DEBUG



void CInforParaPanel::OnInitialUpdate()
{
	CProjectBaseView::OnInitialUpdate();
	m_background.LoadBitmap(IDB_BITMAP_MAIN_BG);
	
	SetScrollSizes(MM_TEXT, CSize(0, 0));
    ShowScrollBar(SB_BOTH, FALSE);

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


	m_tabCtrl.InsertItem( E_MES_PARA		, _T("Parameter") );
	m_tabCtrl.InsertItem( E_MES_FIELD_SET	, _T("Field Setting") );

	CRect rt;

	m_tabCtrl.GetClientRect(&rt);

	m_TabDualScannerParameter		.Create(IDD_DLG_DUAL_SCANNER_PARAMETER	, &m_tabCtrl);
	m_TabFieldParameter		.Create(IDD_DLG_FIELD_PARAMETER				    , &m_tabCtrl);
	
	m_TabDualScannerParameter		.SetWindowPos(NULL, 5, 40, rt.Width() -10, rt.Height() - 45, SWP_NOZORDER);
	m_TabFieldParameter.SetWindowPos(NULL, 5, 40, rt.Width() -10, rt.Height() - 45, SWP_NOZORDER);

	m_tabCtrl.SetItemSize(CSize(150,30));
	m_tabCtrl.ModifyStyle(0, TCS_FIXEDWIDTH);

	m_pCurWnd = &m_TabDualScannerParameter;

	Init();

}

BOOL CInforParaPanel::OnEraseBkgnd(CDC* pDC)
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

// CInforParaPanel 메시지 처리기입니다.


void CInforParaPanel::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CInforParaPanel::UpdateInfo()
{
	m_TabDualScannerParameter.UpdateInfo();
	m_TabFieldParameter.LoadValue();
}


void CInforParaPanel::Init()
{
	if(m_pCurWnd)
	{
		m_pCurWnd->ShowWindow(SW_HIDE);
	}
	else
	{
		m_pCurWnd = &m_TabDualScannerParameter;
	}

	m_pCurWnd = &m_TabDualScannerParameter;
	m_pCurWnd->ShowWindow(SW_SHOW);
	m_tabCtrl.SetCurSel(E_MES_PARA);


	//////////////////////////////////////////////////////////////////////////
	m_tabCtrl.ModifyStyle(0, TCS_OWNERDRAWFIXED);

	
	
}

void CInforParaPanel::OnTcnSelchangeTabCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nIndex = m_tabCtrl.GetCurSel();

	if(m_pCurWnd)
	{
		m_pCurWnd->ShowWindow(SW_HIDE);
		m_pCurWnd = NULL;
	}

	switch(nIndex)
	{

	case E_MES_PARA:
		m_TabDualScannerParameter.ShowWindow(SW_SHOW);
		m_pCurWnd = &m_TabDualScannerParameter;

		break;

	case E_MES_FIELD_SET:
		m_TabFieldParameter.ShowWindow(SW_SHOW);
		m_pCurWnd = &m_TabFieldParameter;

		break;
	}

	*pResult = 0;
}
