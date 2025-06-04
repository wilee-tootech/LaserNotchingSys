#if !defined(AFX_DLGSPECVIEW_H__4397FF26_A994_4A11_8F91_496D99C10D80__INCLUDED_)
#define AFX_DLGSPECVIEW_H__4397FF26_A994_4A11_8F91_496D99C10D80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSpecView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSpecView dialog
#include "BitmapPicture.h"
class CDlgSpecView : public CDialog
{
// Construction
public:
	CDlgSpecView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSpecView)
	enum { IDD = IDD_DLG_SPEC_Image };
	CBitmapPicture	m_Picture;
	//}}AFX_DATA
public:
	CString m_strPartNo;
	CString m_strFileName;
	CString m_strMsg;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSpecView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSpecView)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSPECVIEW_H__4397FF26_A994_4A11_8F91_496D99C10D80__INCLUDED_)
