#if !defined(AFX_GRIDDLG_H__7DB37F89_675E_11D5_9CEB_0000B4BB2A6F__INCLUDED_)
#define AFX_GRIDDLG_H__7DB37F89_675E_11D5_9CEB_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GridDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGridDlg dialog
#include "resource.h"

class CGridDlg : public CDialog
{
// Construction
public:
	CGridDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGridDlg)
	enum { IDD = IDD_GRID };
	BOOL	m_Check_Grid;
	BOOL	m_Fixat_Grid;
	int		m_GridHeight;
	int		m_GridWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGridDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckGrid();
	afx_msg void OnKillfocusHeight();
	afx_msg void OnKillfocusWidth();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDDLG_H__7DB37F89_675E_11D5_9CEB_0000B4BB2A6F__INCLUDED_)
