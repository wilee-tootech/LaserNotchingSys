// BlinkStatic.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "BlinkStatic.h"

#include "BeamEditor6Doc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlinkStatic

CBlinkStatic::CBlinkStatic()
 : m_ForeColor(RGB(0,0,0)),
   m_BlinkColor(RGB(255,0,0)), m_TextColor(RGB(0,0,0)),
   m_nInterval(0), m_nTimerID(0),
   m_bOnBlinking(FALSE)
{
  m_BackColor = GetSysColor(COLOR_BTNFACE);
  m_Brush.CreateSolidBrush(m_BackColor);
}

CBlinkStatic::~CBlinkStatic()
{
}


BEGIN_MESSAGE_MAP(CBlinkStatic, CStatic)
	//{{AFX_MSG_MAP(CBlinkStatic)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlinkStatic message handlers

HBRUSH CBlinkStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	pDC->SetTextColor(m_TextColor);
    pDC->SetBkColor(m_BackColor);

	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return m_Brush;
}

void CBlinkStatic::OnTimer(UINT nIDEvent) 
{
	CStatic::OnTimer(nIDEvent);
  if ( nIDEvent == m_nTimerID )
  {
    m_bOnBlinking = ~m_bOnBlinking;

    if ( m_bOnBlinking )
      m_TextColor = m_BlinkColor;
    else
      m_TextColor = m_ForeColor;

    Invalidate(FALSE);
  }
}
VOID CBlinkStatic::SetForeColor(const COLORREF nColor)
{ 
  m_ForeColor = nColor; 
  if ( !m_bOnBlinking )
  {
    m_TextColor = m_ForeColor;
    Invalidate(FALSE);
  }
}

VOID CBlinkStatic::SetBackColor(const COLORREF nColor)
{ 
  m_BackColor = nColor;

  m_Brush.DeleteObject();
  m_Brush.CreateSolidBrush(nColor);
  Invalidate();
}

VOID CBlinkStatic::SetBlinkColor(const COLORREF nColor)
{ 
  m_BlinkColor = nColor; 
  if ( m_bOnBlinking )
  {
    m_TextColor = m_BlinkColor;
    Invalidate(FALSE);
  }
}

VOID CBlinkStatic::SetInterval(const UINT nInterval)
{
  if ( nInterval > 0 )
  {
    m_nInterval = nInterval;
	  m_nTimerID = SetTimer(GetWindowLong(GetSafeHwnd(),GWL_ID),
                          m_nInterval,
                          NULL);
  }
  else
  {
    if ( m_nTimerID )	
      KillTimer(m_nTimerID);
  }
}

int CBlinkStatic::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
  if ( m_nInterval > 0 )
  {
	  m_nTimerID = SetTimer(GetWindowLong(GetSafeHwnd(),
                          GWL_ID),
                          m_nInterval,
                          NULL);
  }
	return 0;
}

void CBlinkStatic::OnDestroy() 
{
	CStatic::OnDestroy();
  if ( m_nTimerID )	
    KillTimer(m_nTimerID);
}
