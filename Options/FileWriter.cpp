// FileWriter.cpp: implementation of the CFileWriter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileWriter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define UNITSIZE 12

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CFileWriter::CFileWriter() 
: m_dwTableSize(0), m_dwDataSize(0), m_dwUsedTableSize(0), m_dwUsedDataSize(0)
{
	m_dwTableGrow = 2048;
	m_dwDataGrow = 2048;
	m_dwAllocFlag=0;
	m_pTable = NULL;
	m_pData = NULL;

	DWORD dwRet;
	if( m_dwAllocFlag == 0)
	{
		dwRet = CheckAlloc();
	}
}

CFileWriter::CFileWriter(DWORD dwTableGrow, DWORD dwDataGrow) 
: m_dwTableSize(0), m_dwDataSize(0), m_dwUsedTableSize(0), m_dwUsedDataSize(0)
{
	m_dwTableGrow = dwTableGrow;
	m_dwDataGrow = dwDataGrow;
	m_dwAllocFlag=0;
	m_pTable = NULL;
	m_pData = NULL;
	CheckAlloc();
}

CFileWriter::~CFileWriter()
{
	ClearData();
}

UINT CFileWriter::Add(DWORD dwID, DWORD dwSize, const void *pData)
{
	return AddData(dwID , dwSize ,  m_dwUsedDataSize, (char *)pData); 
}

char *CFileWriter::GetTotalData(DWORD &dwTotalDataSize)
{
	char *strTotalData = new char [m_dwUsedTableSize + m_dwUsedDataSize+ sizeof(DWORD) ]; 

	DWORD dwTableSize = (m_dwUsedTableSize+sizeof(DWORD));

	memcpy(strTotalData, &dwTableSize,sizeof(DWORD) );
	memcpy(strTotalData+sizeof(DWORD),m_pTable,m_dwUsedTableSize);
	memcpy(strTotalData+m_dwUsedTableSize+sizeof(DWORD), m_pData, m_dwUsedDataSize);

	dwTotalDataSize = m_dwUsedTableSize + m_dwUsedDataSize+ sizeof(DWORD);

	return strTotalData;
}

UINT CFileWriter::ClearData()
{
	if(m_pTable != NULL)
		delete [] m_pTable;
	if(m_pData != NULL)
		delete [] m_pData;

	m_pTable = NULL;
	m_pData  = NULL;
	m_dwAllocFlag=0;
	
	m_dwTableSize = 0;
	m_dwDataSize = 0;
	m_dwUsedTableSize = 0;
	m_dwUsedDataSize = 0;

	return TRUE;
}

void CFileWriter::SetBufferGrow(DWORD dwTableGrow, DWORD dwDataGrow)
{
	m_dwTableGrow = dwTableGrow;
	m_dwDataGrow = dwDataGrow;
}

void CFileWriter::WriteDWORD(char *desBuf,DWORD dwValue)
{
	ASSERT( FALSE==IsBadReadPtr(desBuf,sizeof(DWORD) ));
	memcpy(desBuf,&dwValue,sizeof(DWORD) );
}

UINT CFileWriter::CheckAlloc()
{
	if( m_pTable == NULL)
	{
		m_pTable = new char[m_dwTableGrow];
		ASSERT(m_pTable != NULL);
		if(m_pTable == NULL ) return FALSE;
		m_dwTableSize = m_dwTableGrow;
		m_dwAllocFlag++;
	}

	if( m_pData == NULL)
	{
		m_pData = new char[m_dwDataGrow];
		ASSERT(m_pData != NULL);
		if(m_pData == NULL ) return FALSE;
		m_dwDataSize = m_dwDataGrow;
		m_dwAllocFlag++;
	}
	
	return TRUE;
}

UINT CFileWriter::CheckRealloc(DWORD dwSize)
{
	if( m_dwUsedTableSize + UNITSIZE > m_dwTableSize )
	{
		char *strTmp1;
		
		strTmp1 = new char[ m_dwTableSize + m_dwTableGrow ];
		ASSERT( strTmp1!=NULL );
		memcpy(strTmp1,m_pTable,m_dwTableSize);
		delete [] m_pTable;
		
		m_pTable = strTmp1;
		
		ASSERT( m_pTable != NULL);
		if( m_pTable == NULL ) return FALSE;
		m_dwTableSize += m_dwTableGrow;
	}
	if( m_dwUsedDataSize + dwSize > m_dwDataSize )
	{
		char *strTmp2;
		
		if( m_dwUsedDataSize + dwSize < m_dwUsedDataSize+m_dwDataGrow )
		{
			strTmp2 = new char[m_dwDataSize + m_dwDataGrow];
			memcpy(strTmp2,m_pData,m_dwDataSize);
			delete [] m_pData;
			m_pData = strTmp2;
			ASSERT( m_pData != NULL);
			if( m_pData == NULL ) return FALSE;
			m_dwDataSize += m_dwDataGrow;
		}
		else
		{
			strTmp2 = new char[m_dwDataSize + dwSize];
			memcpy(strTmp2,m_pData,m_dwDataSize);
			delete [] m_pData;
			m_pData =strTmp2;
			ASSERT( m_pData != NULL);
			if( m_pData == NULL) return FALSE;
			m_dwDataSize+=dwSize;
		}
	}
	return TRUE;
}

void CFileWriter::WriteData(char *pData, DWORD dwSize, DWORD dwPos)
{
	ASSERT(  FALSE == IsBadReadPtr(pData,dwSize) );
	memcpy( m_pData + dwPos, pData, dwSize );
}

UINT CFileWriter::AddData(DWORD dwID, DWORD dwSize, DWORD dwPos, char *pData)
{
	DWORD dwRet;
	
	if ( (dwRet = CheckRealloc(dwSize)) != TRUE )
	{
		return dwRet;
	}
	
	WriteDWORD(m_pTable+m_dwUsedTableSize,dwID);
	WriteDWORD(m_pTable+m_dwUsedTableSize+4,dwSize);
	WriteDWORD(m_pTable+m_dwUsedTableSize+8,dwPos);
	m_dwUsedTableSize += UNITSIZE;
	WriteData(pData,dwSize,dwPos);
	m_dwUsedDataSize += dwSize;
	
	return TRUE;
}

