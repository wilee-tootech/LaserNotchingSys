#if !defined(AFX_DLGCHANGEAUTHORITY_H__91B1BEB4_E5FC_4489_974A_ABE4961B7177__INCLUDED_)
#define AFX_DLGCHANGEAUTHORITY_H__91B1BEB4_E5FC_4489_974A_ABE4961B7177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgChangeAuthority.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgChangeAuthority dialog
#include "BtnST.h"

class CDlgChangeAuthority : public CDialog
{
// Construction
public:
	void LoadValue();
	void SetValue();
	CDlgChangeAuthority(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgChangeAuthority)
	enum { IDD = IDD_DLG_CHANGEAUTHORITY };
	CButtonST	m_btnCancel;
	CButtonST	m_btnOk;

	int		m_iAuthority[MAX_USER_SIZE][MAX_AUTH_SIZE]; // Control과 연결된 변수임
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgChangeAuthority)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgChangeAuthority)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHANGEAUTHORITY_H__91B1BEB4_E5FC_4489_974A_ABE4961B7177__INCLUDED_)
