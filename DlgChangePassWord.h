#if !defined(AFX_DLGCHANGEPASSWORD_H__D8748C41_2BB5_11D6_97D6_0000B4BB2A6F__INCLUDED_)
#define AFX_DLGCHANGEPASSWORD_H__D8748C41_2BB5_11D6_97D6_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgChangePassWord.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgChangePassWord dialog

class CDlgChangePassWord : public CDialog
{
// Construction
public:
	BOOL m_flag[3];
	int m_userType;
	CDlgChangePassWord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgChangePassWord)
	enum { IDD = IDD_DIG_CHANGE_PASSWORD };
	CString	m_ad1;
	CString	m_ad2;
	CString	m_eng1;
	CString	m_eng2;
	CString	m_oper1;
	CString	m_oper2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgChangePassWord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgChangePassWord)
	virtual BOOL OnInitDialog();
	afx_msg void OnComformOper();
	afx_msg void OnComformEng();
	afx_msg void OnComformAdmin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHANGEPASSWORD_H__D8748C41_2BB5_11D6_97D6_0000B4BB2A6F__INCLUDED_)
