#if !defined(AFX_DLGCHANGELEVEL_H__7BA24FBA_5D61_42AC_BD0D_AB1370B07C03__INCLUDED_)
#define AFX_DLGCHANGELEVEL_H__7BA24FBA_5D61_42AC_BD0D_AB1370B07C03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgChangeLevel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgChangeLevel dialog
//#include "BtnST.h"

class CDlgChangeLevel : public CDialog
{
// Construction
public:
	void LoadValue();
	CDlgChangeLevel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgChangeLevel)
	enum { IDD = IDD_DLG_CHANGELEVEL };
	CButton	m_ctrUserLevel;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOk;
	int		m_iUserLevel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgChangeLevel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgChangeLevel)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHANGELEVEL_H__7BA24FBA_5D61_42AC_BD0D_AB1370B07C03__INCLUDED_)
