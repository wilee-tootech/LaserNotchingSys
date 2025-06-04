// BoolArrConvertor.cpp: implementation of the CBoolArrConvertor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "BoolArrConvertor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//����Ÿ ���� ���� ������ ���� ���������

CBoolArrConvertor::CBoolArrConvertor()
{

}

CBoolArrConvertor::~CBoolArrConvertor()
{

}

DWORD *CBoolArrConvertor::EncodetoBit(BOOL *pStartAddr, DWORD dwArrCount, DWORD &dwResultSize)
{
	DWORD *pdwEncoded;
	DWORD dwCount=0;
	pdwEncoded = new DWORD[(dwArrCount >> 5) + 1];   // 32�� ���� ��
	
	memset(pdwEncoded,0,sizeof(DWORD) * dwArrCount>>5); // �ʱ�ȭ 

	while ( dwCount < dwArrCount )
	{
		pdwEncoded[dwCount>>5] = (pdwEncoded[dwCount>>5] )  |  ( (pStartAddr[dwCount]? 1:0) << (dwCount % 32) ); 
		dwCount ++;
	}
	dwResultSize = ((dwCount-1) >> 5);
	dwResultSize++;
	return pdwEncoded;
}
void CBoolArrConvertor::DecodetoBOOL(BOOL *pTargetAddr, DWORD *pchSourceAddr, DWORD dwArrCount)
{
	DWORD dwCount = 0;

	while( dwCount < dwArrCount )
	{
		if( pchSourceAddr[dwCount >> 5] & ( 0x01 << (dwCount % 32) ) )
			pTargetAddr[dwCount] = TRUE;
		else 
			pTargetAddr[dwCount] = FALSE;
		dwCount++;
	}
}