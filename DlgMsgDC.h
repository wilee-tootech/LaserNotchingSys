#if !defined(AFX_DLGMSGDC_H__18E0C37E_C465_47AA_A2FB_C7C4C2E64F9C__INCLUDED_)
#define AFX_DLGMSGDC_H__18E0C37E_C465_47AA_A2FB_C7C4C2E64F9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMsgDC.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMsgDC dialog
#include "BlinkStatic.h"

class CDlgMsgDC : public CDialog
{
// Construction
public:
	CDlgMsgDC(CWnd* pParent = NULL);   // standard constructor
	void SetMessage(CString str);
	void ClearMessage(void);

	CFont Font;
	BOOL bFlag;
	CString m_strMessage;
	

// Dialog Data
	//{{AFX_DATA(CDlgMsgDC)
	enum { IDD = IDD_DLG_MSG_DC };
	CBlinkStatic	m_msg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMsgDC)
	public:
	virtual BOOL Create(CWnd* pParentWnd);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMsgDC)
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMSGDC_H__18E0C37E_C465_47AA_A2FB_C7C4C2E64F9C__INCLUDED_)
