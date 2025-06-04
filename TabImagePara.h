#if !defined(AFX_TABIMAGEPARA_H__510AD3C2_D966_4205_BBD9_EC64E04031F5__INCLUDED_)
#define AFX_TABIMAGEPARA_H__510AD3C2_D966_4205_BBD9_EC64E04031F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabImagePara.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabImagePara dialog
#include "TabPageSSL.h"

class CTabImagePara : public CTabPageSSL
{
// Construction
public:
	CTabImagePara(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTabImagePara)
	enum { IDD = IDD_TAB_IMAGEPARA };
	int		m_iBmpSize;
	int		m_iDwellTime;
	int		m_iLineMoveDelayTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabImagePara)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabImagePara)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABIMAGEPARA_H__510AD3C2_D966_4205_BBD9_EC64E04031F5__INCLUDED_)
