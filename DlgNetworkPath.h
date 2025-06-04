#if !defined(AFX_DLGNETWORKPATH_H__84276FF4_77A1_4DC9_8B2D_F11AD5EDCDE0__INCLUDED_)
#define AFX_DLGNETWORKPATH_H__84276FF4_77A1_4DC9_8B2D_F11AD5EDCDE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNetworkPath.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNetworkPath dialog
#include "FileTreeCtrl.h"

class CDlgNetworkPath : public CDialog
{
// Construction
public:
	CDlgNetworkPath(CWnd* pParent = NULL);   // standard constructor

	CString GetNetworkPath();

// Dialog Data
	//{{AFX_DATA(CDlgNetworkPath)
	enum { IDD = IDD_DLG_NETWORKPATH };
	CFileTreeCtrl	m_ctrFileTree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNetworkPath)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNetworkPath)
	afx_msg LRESULT OnChangePath(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString m_strNetworkPath;
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNETWORKPATH_H__84276FF4_77A1_4DC9_8B2D_F11AD5EDCDE0__INCLUDED_)
