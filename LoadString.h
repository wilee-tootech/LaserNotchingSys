// LoadString.h: interface for the CLoadString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADSTRING_H__82A64AAB_DFC5_4561_8CC6_00213EAC6466__INCLUDED_)
#define AFX_LOADSTRING_H__82A64AAB_DFC5_4561_8CC6_00213EAC6466__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BtnST.h"

class CLoadString  
{
public:
	void LoadBitmap(CWnd *pWnd, int iStartBitmap, int iStartID, int iEndID);
	void LoadBitmap(CWnd *pWnd, int iBitmapID, int iID);
	void LoadString(CWnd *pWnd, int iStartString, int iStartID, int iEndID, BOOL bOk, BOOL bCancel);
	void LoadIcon(CWnd *pWnd, int iStartID, int iEndID, BOOL bOk, BOOL bCancel);
	CLoadString();
	virtual ~CLoadString();
};

#endif // !defined(AFX_LOADSTRING_H__82A64AAB_DFC5_4561_8CC6_00213EAC6466__INCLUDED_)
