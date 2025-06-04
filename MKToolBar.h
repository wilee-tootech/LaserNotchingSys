#if !defined(AFX_MKTOOLBAR_H__41DCEE61_05F6_11D6_97D5_0000B4BB2A6F__INCLUDED_)
#define AFX_MKTOOLBAR_H__41DCEE61_05F6_11D6_97D5_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MKToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMKToolBar window

class CMKToolBar : public CToolBar
{
// Construction
public:
	CMKToolBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMKToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	RECT rect;
	virtual ~CMKToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMKToolBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MKTOOLBAR_H__41DCEE61_05F6_11D6_97D5_0000B4BB2A6F__INCLUDED_)
