//{{AFX_INCLUDES()
#include "talbarcd.h"
//}}AFX_INCLUDES
#if !defined(AFX_MDLESS2DBARCODEDLG_H__DFCDFC84_D152_4AF7_B484_1DB8BC63A9A0__INCLUDED_)
#define AFX_MDLESS2DBARCODEDLG_H__DFCDFC84_D152_4AF7_B484_1DB8BC63A9A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mdless2DBarcodeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMdless2DBarcodeDlg dialog

class CMdless2DBarcodeDlg : public CDialog
{
// Construction
public:
	CMdless2DBarcodeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMdless2DBarcodeDlg)
	enum { IDD = IDD_MDLESSBARCODE };
	CTALBarCd	m_TalBarCd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMdless2DBarcodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMdless2DBarcodeDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDLESS2DBARCODEDLG_H__DFCDFC84_D152_4AF7_B484_1DB8BC63A9A0__INCLUDED_)
