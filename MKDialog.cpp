// MKDialog.cpp: implementation of the CMKDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "MKDialog.h"
#include "MKObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMKDialog::CMKDialog(UINT ID,CWnd *pWnd)
{
	CDialog::CDialog(ID,pWnd);
	
}

CMKDialog::~CMKDialog()
{

}


void CMKDialog::SetMKObject(CMKObject *pObject)
{
	ASSERT(FALSE == IsBadReadPtr(pObject, sizeof(CMKObject) ) );
	m_pObject = pObject;
}
CMKObject *CMKDialog::GetMKObject()
{

	return m_pObject;
}