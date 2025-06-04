#if !defined(AFX_DLGCHANGEPWD_H__A5829215_4C82_4E7D_AE86_85A4281FC2F4__INCLUDED_)
#define AFX_DLGCHANGEPWD_H__A5829215_4C82_4E7D_AE86_85A4281FC2F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgChangePWD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgChangePWD dialog
#include "BtnST.h"

class CDlgChangePWD : public CDialog
{
// Construction
public:
	CDlgChangePWD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgChangePWD)
	enum { IDD = IDD_DLG_CHANGEPWD };
	CButtonST	m_btnCancel;
	CButtonST	m_btnOk;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgChangePWD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgChangePWD)
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	afx_msg void OnConfirmOper();
	afx_msg void OnConfirmEng();
	afx_msg void OnConfirmAdmin();
	afx_msg void OnConfirmEditor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHANGEPWD_H__A5829215_4C82_4E7D_AE86_85A4281FC2F4__INCLUDED_)
