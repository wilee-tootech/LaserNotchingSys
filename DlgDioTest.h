#if !defined(AFX_DLGDIOTEST_H__8E115DFF_3E0A_4E4B_A19A_D8AF2E22BB53__INCLUDED_)
#define AFX_DLGDIOTEST_H__8E115DFF_3E0A_4E4B_A19A_D8AF2E22BB53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDioTest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDioTest dialog


#include "./Azin/AxtLIB.h"
#include "./Azin/AxtDIO.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDioTest dialog

class CDlgDioTest : public CDialog
{
// Construction
public:
	CDlgDioTest(CWnd* pParent = NULL);	// standard constructor

	BOOL		OpenDevice();
	BOOL		CloseDevice();
	BOOL		Initialize_DIOtest();

public:
	CString		m_strMessage;
	CString		m_strSucessMessage;
	CString		m_strFailMessage;
	CString		m_strErrorMessage;
	CString		m_strErrorMessage_Edge;
	CString		m_strEdgeStates;
	CString		m_strModuleData;

private:
	CComboBox	*m_pModuleID;
	CButton		*m_pInterruptOn;
	CButton		*m_pchkRising;
	CButton		*m_pchkFalling;
	CStatic		*m_pCheckBtn[2];
	CButton		*m_pchkHigh[16];
	CButton		*m_pchkLow[16];

// Dialog Data
	//{{AFX_DATA(CDlgDioTest)
	enum { IDD = IDD_DIOTEST_DIALOG };
	CListBox	m_List;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDioTest)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgDioTest)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckInterrupt();
	afx_msg void OnCheckRising();
	afx_msg void OnCheckFalling();
	afx_msg void OnButtonClear();
	afx_msg void OnButtonExit();
	afx_msg void OnEditchangeModuleid();
	afx_msg void On1002();
	//}}AFX_MSG
	afx_msg void OnClickAGroup(UINT nID);
	afx_msg void OnClickBGroup(UINT nID);
	afx_msg LRESULT OnInterruptMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDIOTEST_H__8E115DFF_3E0A_4E4B_A19A_D8AF2E22BB53__INCLUDED_)
