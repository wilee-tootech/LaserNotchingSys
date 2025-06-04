#if !defined(AFX_DLGPROGRESSBAR_H__F509BD25_33E0_4821_B274_686D371F3DCA__INCLUDED_)
#define AFX_DLGPROGRESSBAR_H__F509BD25_33E0_4821_B274_686D371F3DCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProgressBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProgressBar dialog

class CDlgProgressBar : public CDialog
{
// Construction
public:
	CDlgProgressBar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProgressBar)
	enum { IDD = IDD_DLG_PROGRESSBAR };
	CStatic	m_ctrProgressSta;
	CProgressCtrl	m_ctrProgress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProgressBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProgressBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROGRESSBAR_H__F509BD25_33E0_4821_B274_686D371F3DCA__INCLUDED_)
