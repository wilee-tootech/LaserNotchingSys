#if !defined(AFX_DLGLOGSETTING_H__180A74BF_2F3F_4B2C_9C35_B89EAF14F0E3__INCLUDED_)
#define AFX_DLGLOGSETTING_H__180A74BF_2F3F_4B2C_9C35_B89EAF14F0E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLogSetting dialog

class CDlgLogSetting : public CDialog
{
// Construction
public:
	BOOL FindSameCode(int iCode);
	CDlgLogSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLogSetting)
	enum { IDD = IDD_LOG_DIALOG };
	BOOL	m_bAutoEnd;
	BOOL	m_bAutoEndEvent;
	BOOL	m_bAutoStart;
	int		m_iAutoEnd;
	int		m_iAutoEndEvent;
	int		m_iAutoStart;
	int		m_iLaserError;
	int		m_iManualEnd;
	int		m_iManualStart;
	int		m_iWaitEnd;
	int		m_iWaitStart;
	BOOL	m_bLaserError;
	BOOL	m_bManualEnd;
	BOOL	m_bManualStart;
	int		m_iSavePeriod;
	BOOL	m_bWaitEnd;
	BOOL	m_bWaitStart;
	CString	m_strSaveDir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLogSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLogSetting)
	afx_msg void OnSelDir();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOGSETTING_H__180A74BF_2F3F_4B2C_9C35_B89EAF14F0E3__INCLUDED_)
