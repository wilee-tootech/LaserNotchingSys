// Parser.cpp: implementation of the CParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "mk.h"
#include "Parser.h"
#include "Utility.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParser::CParser()
{
	

}

CParser::~CParser()
{

}



CString CParser::GetString(CString &strSource , CString strIndex)
{
	CString strTemp = "";
	int iResult;
	int iResult2, iResult3;

	iResult = strSource.Find(strIndex,0);
	iResult2 = strSource.Find("=",iResult);
	iResult3 = strSource.Find("\n",iResult);
	if( iResult2 < iResult3 )
	{
		strTemp = strSource.Mid(iResult2+1,iResult3-iResult2-1);
		//strTemp = CUtility::GetInstance()->TrimSpaceCharLeftRight(strTemp);
	}
	return strTemp;
}