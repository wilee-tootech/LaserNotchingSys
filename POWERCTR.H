#if !defined(AFX_POWERCTR_H__67554E4A_9AD6_4C36_9B74_5662E5F31D71__INCLUDED_)
#define AFX_POWERCTR_H__67554E4A_9AD6_4C36_9B74_5662E5F31D71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// POWERCTR.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPOWERCTR dialog

class CPOWERCTR : public CDialog
{
// Construction
public:
	CPOWERCTR(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPOWERCTR)
//	enum { IDD = IDD_POWERCTR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPOWERCTR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPOWERCTR)
	afx_msg void OnAutoPower();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POWERCTR_H__67554E4A_9AD6_4C36_9B74_5662E5F31D71__INCLUDED_)
