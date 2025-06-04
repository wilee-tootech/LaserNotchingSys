
// ProjectBaseView.cpp : CProjectBaseView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.


#include "BeamEditor6Doc.h"
#include "ProjectBaseView.h"

#include "./EXTERN/CColorDefine.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProjectBaseView

IMPLEMENT_DYNCREATE(CProjectBaseView, CFormView)

BEGIN_MESSAGE_MAP(CProjectBaseView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CProjectBaseView 생성/소멸

CProjectBaseView::CProjectBaseView()
	: CFormView(CProjectBaseView::IDD)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CProjectBaseView::CProjectBaseView(int IDD)
	: CFormView(IDD)
{
	m_bShowScroll = true;
}

CProjectBaseView::~CProjectBaseView()
{
}

void CProjectBaseView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CProjectBaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CProjectBaseView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();


	if(!m_bShowScroll)
	{
		CRect rtView;
		GetClientRect(&rtView);
		GetParentFrame()->RecalcLayout();
		SetScaleToFitSize(rtView.Size());
	}

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

	// 	GetParentFrame()->RecalcLayout();
	// 	ResizeParentToFit();
	m_pMainFrame	= (CMainFrame*)AfxGetMainWnd();
	m_pDocument		= (CBeamEditor6Doc*)GetDocument();

}

void CProjectBaseView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CProjectBaseView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CProjectBaseView 진단

#ifdef _DEBUG
void CProjectBaseView::AssertValid() const
{
	CFormView::AssertValid();
}

void CProjectBaseView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CBeamEditor6Doc* CProjectBaseView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBeamEditor6Doc)));
	return (CBeamEditor6Doc*)m_pDocument;
}
#endif //_DEBUG


// CProjectBaseView 메시지 처리기


HBRUSH CProjectBaseView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.

//
// #define CTLCOLOR_MSGBOX         0
// #define CTLCOLOR_EDIT           1
// #define CTLCOLOR_LISTBOX        2
// #define CTLCOLOR_BTN            3
// #define CTLCOLOR_DLG            4
// #define CTLCOLOR_SCROLLBAR      5
// #define CTLCOLOR_STATIC         6


//
// #define WHITE_BRUSH         0
// #define LTGRAY_BRUSH        1
// #define GRAY_BRUSH          2
// #define DKGRAY_BRUSH        3
// #define BLACK_BRUSH         4
// #define NULL_BRUSH          5
// #define HOLLOW_BRUSH        NULL_BRUSH
// #define WHITE_PEN           6
// #define BLACK_PEN           7
// #define NULL_PEN            8
// #define OEM_FIXED_FONT      10
// #define ANSI_FIXED_FONT     11
// #define ANSI_VAR_FONT       12
// #define SYSTEM_FONT         13
// #define DEVICE_DEFAULT_FONT 14
// #define DEFAULT_PALETTE     15
// #define SYSTEM_FIXED_FONT   16

//
	switch (nCtlColor)
	{

	case CTLCOLOR_DLG:
		if(*pWnd == *this)
		{
			//hbr = static_cast<HBRUSH>(GetStockObject((2)));
		}
		break;

	case CTLCOLOR_STATIC:
		{
			pDC->SetTextColor(RGB(55, 82, 110));
			pDC->SetBkMode(TRANSPARENT);
			hbr = static_cast<HBRUSH>(GetStockObject((2)));
		}
		break;

// 	case CTLCOLOR_BTN:
// 		{
// 			pDC->SetBkMode(TRANSPARENT);
// 			hbr = static_cast<HBRUSH>(GetStockObject((1)));
// 		}
// 		break;

	}



	return hbr;
}


BOOL CProjectBaseView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CRect rect;

	GetClientRect(&rect);

	CBrush myBrush(CustomColor::colorBackGraund);    // dialog background color <- 요기 바꾸면 됨.

	CBrush *pOld = pDC->SelectObject(&myBrush);

	BOOL bRes  = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);

	pDC->SelectObject(pOld);    // restore old brush

	return bRes;                // CDialog::OnEraseBkgnd(pDC);

	//return CProjectBaseView::OnEraseBkgnd(pDC);
}


void CProjectBaseView::OnNcPaint()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CProjectBaseView::OnNcPaint()을(를) 호출하지 마십시오.
	
// 	CDC* pDC = GetWindowDC();
// 
// 	CRect rcWindow;
// 	GetWindowRect( &rcWindow );
// 	rcWindow.OffsetRect( -rcWindow.left, -rcWindow.top );
// 
// 	CBrush brush(RGB(0,255,0));
// 	
// 	pDC->FrameRect(&rcWindow, &brush);
// 	ReleaseDC( pDC );

}


void CProjectBaseView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect rt;
	GetWindowRect(&rt);
	//GetWindowRect( &rt );

	CRgn rgn;
	rgn.CreateRoundRectRgn(0,0,rt.Width(),rt.Height(), 1, 1);
	SetWindowRgn((HRGN)rgn, TRUE);

}
