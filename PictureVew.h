#if !defined(AFX_PICTUREVEW_H__960AA198_A262_4495_BAC5_AA33BCB65654__INCLUDED_)
#define AFX_PICTUREVEW_H__960AA198_A262_4495_BAC5_AA33BCB65654__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PictureVew.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPictureVew window

class CPictureVew : public CStatic
{
// Construction
public:
	CPictureVew();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictureVew)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPictureVew();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPictureVew)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTUREVEW_H__960AA198_A262_4495_BAC5_AA33BCB65654__INCLUDED_)
