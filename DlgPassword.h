#if !defined(AFX_DLGPASSWORD_H__FB58ECDA_C76D_4FEE_9015_26B9EDBF36ED__INCLUDED_)
#define AFX_DLGPASSWORD_H__FB58ECDA_C76D_4FEE_9015_26B9EDBF36ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPassword.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPassword dialog

class CDlgPassword : public CDialog
{
// Construction
public:
	CDlgPassword(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPassword)
	enum { IDD = IDD_DLG_PW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPassword)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPassword)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPASSWORD_H__FB58ECDA_C76D_4FEE_9015_26B9EDBF36ED__INCLUDED_)
