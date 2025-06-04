#if !defined(AFX_DLGUSERLOGIN_H__13D5C8EA_A611_4F05_BD6D_A0FA10F3DE73__INCLUDED_)
#define AFX_DLGUSERLOGIN_H__13D5C8EA_A611_4F05_BD6D_A0FA10F3DE73__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUserLogIn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUserLogIn dialog
#include "BtnST.h"
#include "DlgMES.h"
#include "afxwin.h"


class CDlgUserLogIn : public CDialog
{
// Construction
public:
	int m_iLoginCount;
	CDlgUserLogIn(CWnd* pParent = NULL);   // standard constructor

	BOOL GetIsFail();
	BOOL m_LoginEnter;
	CString m_strUserID;
	CString m_strUserPW;
	CWnd m_workerGrade;

// Dialog Data
	//{{AFX_DATA(CDlgUserLogIn)
	enum { IDD = IDD_DLG_LOGIN };
	CComboBox	m_cbUserName;
	CButtonST m_btnOk;
	CButtonST m_btnCancel;
	CEdit m_userID;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUserLogIn)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUserLogIn)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bFail;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboUserName();
	afx_msg void OnEnChangeUserPassword();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeVariableFlagEndLength();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeUseridValue();

	CCommunicate *m_pSockComm;

	CDlgUserLogIn(CCommunicate* pSockComm, CWnd* pParent = nullptr)
        : CDialog(IDD_DLG_LOGIN, pParent), m_pSockComm(pSockComm)
    {
    }
	afx_msg bool OnEnChangeRichedit21(CString workGrade);
	afx_msg void OnBnClickedButton1();
	bool MesLoginCheck(CString workGrade);
	DECLARE_EVENTSINK_MAP()
	void DblClickUseridValue();
	void DblClickUserPassword();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUSERLOGIN_H__13D5C8EA_A611_4F05_BD6D_A0FA10F3DE73__INCLUDED_)
