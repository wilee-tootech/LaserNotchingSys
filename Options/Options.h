// Options.h : main header file for the OPTIONS application
//

#if !defined(AFX_OPTIONS_H__83E078CE_8DC7_422B_AA36_13F64DDE2650__INCLUDED_)
#define AFX_OPTIONS_H__83E078CE_8DC7_422B_AA36_13F64DDE2650__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COptionsApp:
// See Options.cpp for the implementation of this class
//

class COptionsApp : public CWinApp
{
public:
	COptionsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COptionsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONS_H__83E078CE_8DC7_422B_AA36_13F64DDE2650__INCLUDED_)
