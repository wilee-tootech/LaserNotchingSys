// Utility.cpp: implementation of the CUtility class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "mk.h"
#include "Utility.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUtility::CUtility()
{

}

CUtility::~CUtility()
{

}

CUtility *CUtility::m_pUtility = 0;
CUtility *CUtility::GetInstance()
{
	if (m_pUtility == 0)
		m_pUtility = new CUtility;

	return m_pUtility;
}

CString CUtility::strRcvData2Char(int nRcvSize, BYTE rcvBuf[4097])
{
	CString strData;
	//--- ���� ������ŭ..
	for( int i=0; i<nRcvSize; i++ )
	{
		strData += rcvBuf[i];
	}
	//--- �� �ڿ��� �ٹٲ�..Edit Box�� �����ٿ� ����ϱ����� 
	strData += _T( "\r\n" );
	//--- ��ȯ�� ���ڿ� �ѱ�.
	return strData;
}



int CUtility::GetNum(char *pData, int startPos, int &endPos)
{
	char *pSearch;
	pSearch=pData + startPos;
	char strNum[6];
	int iCount = 0 ;

    while( (*pSearch <= '9') && (*pSearch >='0'))
	{
		strNum[iCount] = *pSearch; 
		iCount++;
		if(iCount > 5)break;
		pSearch++;
	}
	if( iCount == 0)
	{
	endPos = -1;
	return 0;
	}

	endPos = startPos + (iCount -1);
	strNum[iCount] = NULL;
	return atoi(strNum);
}

CString CUtility::TrimSpaceCharLeftRight(CString strSource) // ��Ʈ�� ������ ���鹮�ڸ� �����ϴ� �Լ� 
{
	int i=0;
	int iResult=0;
	char chOne;

	while(1)
	{
		chOne  = strSource.GetAt(i);
		if( chOne == 0x20)
			iResult++;
		else break;
		i++;
	}
	if( iResult > 0)
		strSource.Delete(0,iResult);
	
	i= strSource.GetLength() -1;
	iResult = 0;
	while(1)
	{
		chOne = strSource.GetAt(i);
		if( chOne == 0x20)
			iResult++;
		else break;
		i--;
	}
	if( iResult >0)
		strSource.Delete(strSource.GetLength() - iResult,iResult);

	return strSource;
}
BOOL CUtility::FindStr(char *pSource,char *pFindData, int iSourceLength, int iFindDataLength)
{
	int i=0;
	int iLength=0;
	char *pFinder;
	pFinder = pSource;


	while (1)
	{
		if( *pFinder == *(pFindData+iLength) ) // ã�� ���ڿ��� �������� �߰ߵǸ�
		{
			iLength++;
			if( iLength == iFindDataLength) // ã�� ���ڿ���ŭ���̰� �Ǹ� ã������
			{
				return TRUE;
			}
			
		}
		else // ã�� ���ϸ� ������ 0���� ���� 
		{
			iLength = 0;

		}
		pFinder++;
		i++;
		if( i >= iSourceLength ) break;

	}
	return FALSE;	


}

BOOL CUtility::FindDeviceInfo(char *pSourceData, int iSourceLength, int &iStartPos)
{
	char *pData = pSourceData;
	int iFoundLength = 0;
	int iInitialPos = 0;

	char strParser[5]="(,)";
	int i=0;
	
	while( 1) 
	{
		if( *pData == strParser[iFoundLength] )
		{
			iFoundLength ++;
			if( iFoundLength == 1)
			{
				iInitialPos = i;
			}
			if( iFoundLength == 3)
			{
				break;
			}
		}
		pData ++;
		i++;
		if( i >= iSourceLength ) break;
		
	}
	if( iFoundLength == 3) // (,)������ ����Ÿ�� ã����� 
	{
		iStartPos = iInitialPos;
		return TRUE;
	}
	else return FALSE;
	


}

void CUtility::SetDelay(UINT isec)
{
	DWORD dwTick = GetTickCount();
	MSG msg;
	while(GetTickCount() - dwTick < isec)
	{					
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
