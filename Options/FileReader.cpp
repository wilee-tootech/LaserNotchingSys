#include "stdafx.h"
#include "FileReader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CFileReader::CFileReader()
:m_dwTableSize(0), m_dwCurPos(4), m_dwReadingPos(0)
{
}

CFileReader::~CFileReader()
{
}

char *CFileReader::GetAt(const char *srcData, DWORD dwFindID, DWORD &dwGetSize, DWORD &dwGetID)
{
	char *strReturnData;
	DWORD dwID, dwSize, dwPos;

	m_dwReadingPos=0;
	m_dwTableSize = GetDWORD(srcData + m_dwReadingPos);
	m_dwReadingPos+=4;
	
	while ( m_dwReadingPos < m_dwTableSize )
	{
		dwID = GetDWORD( srcData + m_dwReadingPos );
		if( dwID == dwFindID )
		{
			dwSize = GetDWORD(srcData + m_dwReadingPos + 4);
			dwPos  = GetDWORD(srcData + m_dwReadingPos + 8);
			strReturnData = new char[dwSize];
			memcpy(strReturnData, srcData+m_dwTableSize+dwPos, dwSize);
			dwGetID = dwID;
			dwGetSize = dwSize;
			
			break;
		}
		else
		{
			m_dwReadingPos = m_dwReadingPos + 12;
		}
	}
	if( dwID == dwFindID )
	{
		return strReturnData;
	}
	else
	{
		return NULL;
	}
}

UINT CFileReader::GetAt(const char *srcData, DWORD dwFindID, void *GetData)
{
	DWORD dwID=0;
	char *pData;
	DWORD dwGetSize;
	pData = GetAt(srcData, dwFindID, dwGetSize, dwID);
	if( pData != NULL)
	{
		memcpy(GetData,pData,dwGetSize);
		delete [] pData;
		return FALSE;
	}
	else
	{
		return FALSE;
	}
}

char *CFileReader::GetNext(const char *srcData,  DWORD &dwGetID, DWORD &dwGetSize)
{
	char *strReturnData;
	DWORD dwID, dwSize, dwPos;


	m_dwTableSize = GetDWORD(srcData);
	
	if( m_dwCurPos < m_dwTableSize )
	{
		dwID = GetDWORD( srcData + m_dwCurPos );
		dwSize = GetDWORD(srcData + m_dwCurPos + 4);
		dwPos  = GetDWORD(srcData + m_dwCurPos + 8);
		strReturnData = new char[dwSize];
		memcpy(strReturnData, srcData+m_dwTableSize+dwPos, dwSize);
		dwGetID = dwID;
		dwGetSize = dwSize;
		m_dwCurPos +=12;

		return strReturnData;
	}
	else
		return NULL;
}

void CFileReader::SeekInit()
{
	m_dwCurPos = 4;
}

DWORD CFileReader::GetDWORD(const char *srcData)
{
	DWORD dwRetValue;
	memcpy( &dwRetValue, srcData, sizeof(DWORD) );
	return dwRetValue;
}
