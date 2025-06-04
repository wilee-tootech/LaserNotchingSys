// BoolArrConvertor.h: interface for the CBoolArrConvertor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOOLARRCONVERTOR_H__A08DDB64_DD7D_40B7_BC50_9B3A82BE90C3__INCLUDED_)
#define AFX_BOOLARRCONVERTOR_H__A08DDB64_DD7D_40B7_BC50_9B3A82BE90C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBoolArrConvertor  
{
public:
	CBoolArrConvertor();
	virtual ~CBoolArrConvertor();
	DWORD *EncodetoBit(BOOL *pStartAddr, DWORD dwArrCount , DWORD &dwResultSize);
	void DecodetoBOOL(BOOL *pTargetAddr, DWORD *pchSourceAddr, DWORD dwArrCount);
	
	

};

#endif // !defined(AFX_BOOLARRCONVERTOR_H__A08DDB64_DD7D_40B7_BC50_9B3A82BE90C3__INCLUDED_)
