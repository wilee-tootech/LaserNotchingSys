#if !defined(AFX_STATICCOLOR_H__9661E615_E804_4E4F_9051_7ED36D530B80__INCLUDED_)
#define AFX_STATICCOLOR_H__9661E615_E804_4E4F_9051_7ED36D530B80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticColor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticColor window

class CStaticColor : public CStatic
{
// Construction
public:
	CStaticColor();

// Attributes
public:
	COLORREF m_col;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticColor)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticColor();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticColor)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICCOLOR_H__9661E615_E804_4E4F_9051_7ED36D530B80__INCLUDED_)
