#if !defined(AFX_DLGFILEPATH_H__F265EEA0_EDF3_11D5_9CF0_0000B4BB2A6F__INCLUDED_)
#define AFX_DLGFILEPATH_H__F265EEA0_EDF3_11D5_9CF0_0000B4BB2A6F__INCLUDED_

#include "FileTreeCtrl.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFilePath.h : header file
//
#include "DlgDirSelect.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgFilePath dialog

class CDlgFilePath : public CDialog
{
// Construction
public:
	CDlgDirSelect *m_pDirSelect;
	CDlgFilePath(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFilePath)
	enum { IDD = IDD_DIA_PATH };
	CString	m_pathDev;
	CString	m_pathFont;
	CString	m_pathMrk;
	CString	m_pathObj;
	CString	m_pathScr;
	CString	m_pathImg;
	CString	m_pathHpgl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFilePath)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFilePath)
	afx_msg void OnButtonMarkfile();
	afx_msg void OnButtonOjbectfile();
	afx_msg void OnButtonDevicefile();
	afx_msg void OnButtonScribefile();
	afx_msg void OnButtonFontfile();
	afx_msg void OnButtonImg();
	afx_msg void OnButtonHpgl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFILEPATH_H__F265EEA0_EDF3_11D5_9CF0_0000B4BB2A6F__INCLUDED_)
