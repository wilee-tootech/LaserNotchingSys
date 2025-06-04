#if !defined(AFX_MKDOCTEMPLATE_H__FBDAAA88_00E9_11D6_97D6_0000B4BB2A6F__INCLUDED_)
#define AFX_MKDOCTEMPLATE_H__FBDAAA88_00E9_11D6_97D6_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MKDocTemplate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMKDocTemplate window
class CMKDocTemplate : public CSingleDocTemplate
{
// Construction
public:
	CMKDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMKDocTemplate)
	public:
	virtual CDocTemplate::Confidence MatchDocType( LPCTSTR lpszPathName, CDocument*& rpDocMatch );
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMKDocTemplate();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMKDocTemplate)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MKDOCTEMPLATE_H__FBDAAA88_00E9_11D6_97D6_0000B4BB2A6F__INCLUDED_)
