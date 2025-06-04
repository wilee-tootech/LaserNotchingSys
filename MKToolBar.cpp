// MKToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "mk.h"
#include "MKToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMKToolBar

CMKToolBar::CMKToolBar():CToolBar()
{
}

CMKToolBar::~CMKToolBar()
{
}


BEGIN_MESSAGE_MAP(CMKToolBar, CToolBar)
	//{{AFX_MSG_MAP(CMKToolBar)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMKToolBar message handlers

BOOL CMKToolBar::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
/*	CBitmap bit;
	bit.LoadBitmap(IDB_TOOLBAR_COLOR);

	pDC->DrawState( CPoint(0,0), CSize(2100, 49), &bit, DST_BITMAP );
*/	
	return 	CToolBar::OnEraseBkgnd(pDC);
}

void CMKToolBar::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CToolBar::OnMouseMove(nFlags, point);

	//	GetDC()->LineTo(lpRect->right + lpRect->right/2, lpRect->bottom + lpRect->bottom/2);
}

void CMKToolBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	CBrush br;
//	br.CreateSolidBrush(RGB(0xff, 0xff, 0xff));

	CToolBar::OnLButtonDown(nFlags, point);
//	GetDC()->FrameRect(&rect, &br );

}

void CMKToolBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	CBrush br;
//	br.CreateSolidBrush(RGB(0xff, 0xff, 0xff));

	CToolBar::OnLButtonUp(nFlags, point);
//	GetDC()->FrameRect(&rect, &br );
}
