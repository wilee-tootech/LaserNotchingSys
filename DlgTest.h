#if !defined(AFX_DLGTEST_H__4439ABD4_4D13_4DC0_A6A7_239BA2E1B2BA__INCLUDED_)
#define AFX_DLGTEST_H__4439ABD4_4D13_4DC0_A6A7_239BA2E1B2BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTest dialog
#include "Communicate.h"
#include "BtnST.h"

class CDlgTest : public CDialog
{
// Construction
public:
	CDlgTest(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTest)
	enum { IDD = IDD_DLG_TEST };
	CButtonST	m_btnTest;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTest)
	afx_msg void OnTest();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CCommunicate *m_pCommunicate;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTEST_H__4439ABD4_4D13_4DC0_A6A7_239BA2E1B2BA__INCLUDED_)
