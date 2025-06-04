#if !defined(AFX_BLINKSTATIC_H__7534B5D0_7DCE_11D3_A109_004095273B3E__INCLUDED_)
#define AFX_BLINKSTATIC_H__7534B5D0_7DCE_11D3_A109_004095273B3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BlinkStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBlinkStatic window

class CBlinkStatic : public CStatic
{
// Construction
public:
	CBlinkStatic();
	virtual ~CBlinkStatic();

  UINT GetForeColor(){ return m_ForeColor; }
  VOID SetForeColor(const COLORREF nColor);
  UINT GetBackColor(){ return m_BackColor; }
  VOID SetBackColor(const COLORREF nColor);
  UINT GetBlinkColor(){ return m_BlinkColor; }
  VOID SetBlinkColor(const COLORREF nColor);
  UINT GetInterval(){ return m_nInterval; }
	VOID SetInterval(const UINT nInterval);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlinkStatic)
	//}}AFX_VIRTUAL

// Implementation

private:
  COLORREF m_BackColor;
	COLORREF m_ForeColor;
	COLORREF m_BlinkColor;
  CBrush   m_Brush;

 	COLORREF m_TextColor;
  UINT     m_nTimerID;
  BOOL     m_bOnBlinking;
  UINT     m_nInterval;

	// Generated message map functions
protected:
	//{{AFX_MSG(CBlinkStatic)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG


	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLINKSTATIC_H__7534B5D0_7DCE_11D3_A109_004095273B3E__INCLUDED_)
