#if !defined(AFX_DLGAMKORDIR_H__90030941_9404_40C8_AE8C_7F6953D83E50__INCLUDED_)
#define AFX_DLGAMKORDIR_H__90030941_9404_40C8_AE8C_7F6953D83E50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAmkorDir.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAmkorDir dialog

class CDlgAmkorDir : public CDialog
{
// Construction
public:
	CDlgAmkorDir(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAmkorDir)
	enum { IDD = IDD_DIALOG_AMKORDIR_SET };
	CString	m_strEditDir;
	CString	m_strRscDir;
	CString	m_strFontDir;
	CString	m_strHpglDir;
	CString	m_strTmpDir;
	CString	m_strPrjDir;
	CString	m_strFieldSize;
	CString	m_strAmkorField;
	CString	m_strCompanyCode;
	CString	m_strPenFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAmkorDir)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAmkorDir)
	afx_msg void OnButtonEditdir();
	afx_msg void OnButtonRscDir();
	afx_msg void OnButtonFontDir();
	afx_msg void OnButtonHpglDir();
	afx_msg void OnButtonTmpDir();
	afx_msg void OnButtonPrjDir();
	virtual void OnOK();
	afx_msg void OnButtonPenDir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAMKORDIR_H__90030941_9404_40C8_AE8C_7F6953D83E50__INCLUDED_)
