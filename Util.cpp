// Util.cpp: implementation of the CUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "beameditor6.h"
#include "Util.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUtil::CUtil()
{

}

CUtil::~CUtil()
{

}


CUtil &CUtil::Instance()
{
	static CUtil s_Util;
	return s_Util;
}

BOOL CUtil::IsFileExist(CString &strFileName)
{
	CFileFind FileFind;
	if ( FileFind.FindFile(strFileName) == TRUE )
		return TRUE;
	else return FALSE;
}