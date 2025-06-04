// Util.h: interface for the CUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTIL_H__2B4BE8E6_4D0E_492F_A427_247C86F1C542__INCLUDED_)
#define AFX_UTIL_H__2B4BE8E6_4D0E_492F_A427_247C86F1C542__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUtil  
{
public:
	CUtil();
	virtual ~CUtil();
	static CUtil &Instance();
	static BOOL IsFileExist(CString &strFileName);


};

#endif // !defined(AFX_UTIL_H__2B4BE8E6_4D0E_492F_A427_247C86F1C542__INCLUDED_)
