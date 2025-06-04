#if !defined(AFX_DLGPARACOLOR_H__77CE29F5_4E73_408F_8270_B5AA90E27043__INCLUDED_)
#define AFX_DLGPARACOLOR_H__77CE29F5_4E73_408F_8270_B5AA90E27043__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgParaColor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgParaColor dialog

#include "StaticColor.h"

class CDlgParaColor : public CDialog
{
// Construction
public:
	void cDoModal(int iIndex);
	CDlgParaColor(CWnd* pParent = NULL);   // standard constructor
	COLORREF m_colPara[20];

// Dialog Data
	//{{AFX_DATA(CDlgParaColor)
	enum { IDD = IDD_PARA_DIALOG };
	CStaticColor	m_ctlPara[20];
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgParaColor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgParaColor)
	afx_msg void OnPara1();
	afx_msg void OnPara2();
	afx_msg void OnPara3();
	afx_msg void OnPara4();
	afx_msg void OnPara5();
	afx_msg void OnPara6();
	afx_msg void OnPara7();
	afx_msg void OnPara8();
	afx_msg void OnPara9();
	afx_msg void OnPara10();
	afx_msg void OnPara11();
	afx_msg void OnPara12();
	afx_msg void OnPara13();
	afx_msg void OnPara14();
	afx_msg void OnPara15();
	afx_msg void OnPara16();
	afx_msg void OnPara17();
	afx_msg void OnPara18();
	afx_msg void OnPara19();
	afx_msg void OnPara20();
	
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPARACOLOR_H__77CE29F5_4E73_408F_8270_B5AA90E27043__INCLUDED_)
