// MKDocTemplate.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "MKDocTemplate.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMKDocTemplate

CMKDocTemplate::CMKDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass)
:CSingleDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass)
{
}

CMKDocTemplate::~CMKDocTemplate()
{
}

BEGIN_MESSAGE_MAP(CMKDocTemplate, CSingleDocTemplate)
	//{{AFX_MSG_MAP(CMKDocTemplate)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMKDocTemplate message handlers
CDocTemplate::Confidence CMKDocTemplate::MatchDocType(LPCTSTR lpszPathName, CDocument*& rpDocMatch )
{
	return yesAttemptNative; // extension matches, looks like ours
}
