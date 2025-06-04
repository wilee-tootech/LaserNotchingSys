#if !defined(AFX_DLGSHUTTERDELAY_H__F7197F53_BB3A_4ECC_A55B_4D257C964584__INCLUDED_)
#define AFX_DLGSHUTTERDELAY_H__F7197F53_BB3A_4ECC_A55B_4D257C964584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgShutterDelay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgShutterDelay dialog

class CDlgShutterDelay : public CDialog
{
// Construction
public:
	void GetDelay();
	CDlgShutterDelay(CWnd* pParent = NULL);   // standard constructor
	int m_iShutterDelay;

// Dialog Data
	//{{AFX_DATA(CDlgShutterDelay)
	enum { IDD = IDD_DLG_SHUTTER_DELAY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgShutterDelay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgShutterDelay)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSHUTTERDELAY_H__F7197F53_BB3A_4ECC_A55B_4D257C964584__INCLUDED_)
