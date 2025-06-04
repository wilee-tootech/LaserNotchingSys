#if !defined(AFX_DLGOPERATORMODE_H__8FE8F119_6B51_4DEF_A729_C5EBB30FD99C__INCLUDED_)
#define AFX_DLGOPERATORMODE_H__8FE8F119_6B51_4DEF_A729_C5EBB30FD99C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOperatorMode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOperatorMode dialog

class CDlgOperatorMode : public CDialog
{
// Construction
public:
	int m_nOperatorModeTime;
	CDlgOperatorMode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOperatorMode)
	enum { IDD = IDD_DLG_OPERATOR_MODE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOperatorMode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOperatorMode)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPERATORMODE_H__8FE8F119_6B51_4DEF_A729_C5EBB30FD99C__INCLUDED_)
