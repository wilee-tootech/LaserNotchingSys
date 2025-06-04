// StaticColor.cpp : implementation file
//

#include "stdafx.h"
#include "Options.h"
#include "StaticColor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticColor

CStaticColor::CStaticColor()
{
	m_col = 0xffffff;
}

CStaticColor::~CStaticColor()
{
}


BEGIN_MESSAGE_MAP(CStaticColor, CStatic)
	//{{AFX_MSG_MAP(CStaticColor)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticColor message handlers

void CStaticColor::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	RECT rtClientRect;
	CBrush brBrush;
	brBrush.CreateSolidBrush(m_col);
	GetClientRect(&rtClientRect);
	dc.FillRect(&rtClientRect, &brBrush);
	// Do not call CStatic::OnPaint() for painting messages
}