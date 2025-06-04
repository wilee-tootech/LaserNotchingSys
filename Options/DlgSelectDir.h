#if !defined(AFX_DLGSELECTDIR_H__251936FD_5D2C_4594_B0C1_F3CA68DD6D76__INCLUDED_)
#define AFX_DLGSELECTDIR_H__251936FD_5D2C_4594_B0C1_F3CA68DD6D76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelectDir.h : header file
//
#include "Options.h"
#include "FileTreeCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgSelectDir dialog

class CDlgSelectDir : public CDialog
{
// Construction
public:
	CDlgSelectDir(CWnd* pParent = NULL);   // standard constructor
	CString m_SetPath;

// Dialog Data
	//{{AFX_DATA(CDlgSelectDir)
	enum { IDD = IDD_DIR_DIALOG };
	CFileTreeCtrl	m_fileTreeCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelectDir)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSelectDir)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnChangePath(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELECTDIR_H__251936FD_5D2C_4594_B0C1_F3CA68DD6D76__INCLUDED_)
