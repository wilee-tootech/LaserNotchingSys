#if !defined(AFX_DLGHARDWARETEST_H__45843764_657B_44D6_952E_267F0EE40C06__INCLUDED_)
#define AFX_DLGHARDWARETEST_H__45843764_657B_44D6_952E_267F0EE40C06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHardwareTest.h : header file
//

#include "BtnST.h"
#include "../DIALOGEX/UserDialogEx.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgHardwareTest dialog

class CDlgHardwareTest : public CUserDialogEx
{
// Construction
public:
	BOOL SetParaMeter(int nCardNo, int index);
	CDlgHardwareTest(CWnd* pParent = NULL);   // standard constructor


	CButtonST	m_btnOk;
	CButtonST	m_btnCancel;
// Dialog Data
	//{{AFX_DATA(CDlgHardwareTest)
	enum { IDD = IDD_DLG_HARDWARE_TEST };
	int		m_tickleSet;
	int		m_scannerX;
	int		m_scannerY;
	int		m_fq;
	int		m_pw;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHardwareTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHardwareTest)
	afx_msg void OnStartingPoint();
	afx_msg void OnLaserOn();
	afx_msg void OnLaserOff();
	afx_msg void OnChangeEditTickle();
	virtual BOOL OnInitDialog();
	afx_msg void OnScannermove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClicked65535();
	void TimedLaserOn(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHARDWARETEST_H__45843764_657B_44D6_952E_267F0EE40C06__INCLUDED_)
