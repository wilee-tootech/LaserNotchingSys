// BeamEditor6View.cpp : implementation of the CBeamEditor6View class
//


#include "stdafx.h"
#include "BeamEditor6.h"
#include "BeamEditor6Doc.h"
#include "BeamEditor6View.h"

#include "PointerContainer.h"
#include "UserInterface.h"
#include "StatusDisplay.h"

#include "MainFrm.h"
#include "FieldParameter.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6View

IMPLEMENT_DYNCREATE(CBeamEditor6View, CView)

BEGIN_MESSAGE_MAP(CBeamEditor6View, CView)
	//{{AFX_MSG_MAP(CBeamEditor6View)
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(IDC_SCREEN_ZOOM_FRAME, OnScreenZoomFrame)
	ON_COMMAND(IDC_SCREEN_ZOOM, OnScreenZoom)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6View construction/destruction

CBeamEditor6View::CBeamEditor6View()
{
	// TODO: add construction code here

	m_bFirstTime= TRUE;
	m_bDrawFlag = FALSE;
	m_pDC= NULL;
	CPointerContainer::SetView(this);	
	m_pUI = new CUserInterface;
}

CBeamEditor6View::~CBeamEditor6View()
{
	delete m_pUI;
	
}

BOOL CBeamEditor6View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6View drawing


void CBeamEditor6View::OnDraw(CDC* pDC)
{
	
	//CBeamEditor6Doc* pDoc = GetDocument(); 
	//ASSERT_VALID(pDoc);
	
	return;



		
}

/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6View printing

BOOL CBeamEditor6View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation


	return DoPreparePrinting(pInfo);
}

void CBeamEditor6View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing


}

void CBeamEditor6View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6View diagnostics

#ifdef _DEBUG
void CBeamEditor6View::AssertValid() const
{
	CView::AssertValid();
}

void CBeamEditor6View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBeamEditor6Doc* CBeamEditor6View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBeamEditor6Doc)));
	return (CBeamEditor6Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6View message handlers

void CBeamEditor6View::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
	

}

void CBeamEditor6View::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	return;
	CView::OnShowWindow(bShow, nStatus);
}

void CBeamEditor6View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	return;
	
}

void CBeamEditor6View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	return;
	
}

void CBeamEditor6View::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	return;
	
}

void CBeamEditor6View::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	return;
	// TODO: Add your message handler code here and/or call default
	
}

BOOL CBeamEditor6View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	return true;
	// TODO: Add your message handler code here and/or call default
	

}

void CBeamEditor6View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	return;
	// TODO: Add your message handler code here and/or call default
	
}

void CBeamEditor6View::OnRButtonUp(UINT nFlags, CPoint point) 
{
	return;
	
}

void CBeamEditor6View::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	return;
	
}

void CBeamEditor6View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	return;
	
}

void CBeamEditor6View::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	return;
	// TODO: Add your message handler code here and/or call default

}

void CBeamEditor6View::OnScreenZoomFrame() 
{
	return;
	// TODO: Add your command handler code here
	
	
}


void CBeamEditor6View::OnScreenZoom() 
{
	return;
	
}
// jjTEST


BOOL CBeamEditor6View::PreTranslateMessage(MSG* pMsg) 
{
	
	return CView::PreTranslateMessage(pMsg);
}

