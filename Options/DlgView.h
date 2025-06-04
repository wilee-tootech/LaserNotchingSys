#if !defined(AFX_DLGVIEW_H__44505079_BA40_460F_8373_16E3783D07CF__INCLUDED_)
#define AFX_DLGVIEW_H__44505079_BA40_460F_8373_16E3783D07CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgView dialog

#include "StaticColor.h"

class CDlgView : public CDialog
{
// Construction
public:
	CDlgView(CWnd* pParent = NULL);   // standard constructor
	void SetColor(int iID, int iColor);

// Dialog Data
	//{{AFX_DATA(CDlgView)
	enum { IDD = IDD_VIEW_DIALOG };
	CStaticColor	m_ctlSelBox;
	CStaticColor	m_ctlRuler;
	CStaticColor	m_ctlGridScale;
	CStaticColor	m_ctlGridLine;
	CStaticColor	m_ctlDevOuter;
	CStaticColor	m_ctlDevLine;
	CStaticColor	m_ctlDevInner;
	int		m_iSelBoxSize;
	int		m_iRulerSize;
	int		m_iRulerFontSize;
	int		m_iRulerScaleSize;
	//}}AFX_DATA

	COLORREF m_colDevInner;
	COLORREF m_colDevOuter;
	COLORREF m_colDevLine;
	COLORREF m_colGridLine;
	COLORREF m_colGridScale;
	COLORREF m_colSelBox;
	COLORREF m_colRuler;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgView)
	afx_msg void OnColDevInner();
	afx_msg void OnColDevOuter();
	virtual BOOL OnInitDialog();
	afx_msg void OnColDevline();
	afx_msg void OnColGridline();
	afx_msg void OnColGridscale();
	afx_msg void OnColRuler();
	afx_msg void OnColSelbox();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEW_H__44505079_BA40_460F_8373_16E3783D07CF__INCLUDED_)
