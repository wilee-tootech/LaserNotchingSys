#if !defined(AFX_DLGDIRSELECT_H__896624A2_EF5C_11D5_9CF0_0000B4BB2A6F__INCLUDED_)
#define AFX_DLGDIRSELECT_H__896624A2_EF5C_11D5_9CF0_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDirSelect.h : header file
//

#include "FileTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDirSelect dialog
class CDlgDirSelect : public CDialog
{
// Construction
public:
	CString m_SetPath;
	CDlgDirSelect(CWnd* pParent = NULL);   // standard constructor

	CString m_strDir;

// Dialog Data
	//{{AFX_DATA(CDlgDirSelect)
	enum { IDD = IDD_DLG_DIR };
	CFileTreeCtrl	m_fileTreeCtrl;
	CString	m_dirText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDirSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDirSelect)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg void OnChangePath(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDIRSELECT_H__896624A2_EF5C_11D5_9CF0_0000B4BB2A6F__INCLUDED_)
