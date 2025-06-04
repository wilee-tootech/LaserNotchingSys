 // MKFileWriter.cpp: implementation of the CMKFileWriter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MKFileWriter.h"
#include "Return.h"

#include "TimeChecker.h"



//15887288

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define UNITSIZE 12         //�ϳ��� ����Ÿ ������ 12����Ʈ�̴�.

//  : ȭ�Ϸ� ����Ǳ� ����  [ID][SIZE][POS] �������� ������ִ� Ŭ����
// ���̺� �ڿ��� �׿� �ش��ϴ� ����Ÿ ����� ����´�.
// realloc�׽�Ʈ �Ϸ�  2003.11.04

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/* ũ�� ���� 
  [ Table  ][ Data ]�� �������� �Ǿ��ִ�. */


CMKFileWriter::CMKFileWriter() 
: m_dwTableSize(0), m_dwDataSize(0), m_dwUsedTableSize(0), m_dwUsedDataSize(0)
{
	m_dwTableGrow = 2048; //���� Table�� �����ϴ� ����
	m_dwDataGrow = 2048; //����Ÿ�� �����ϴ� ����. //������ũ�⿡�� ���� ������. ReallocȽ�� �δ�� �ʱ� �Ҵ��� �δ㰣�� ��ȭ �ʿ�.
	m_dwAllocFlag=0;    // �̷��� �޸� Ǯ�� �ý����� �����ؾ������� �𸣰ڴ�. ���߿� �ӵ��� �����ȴٸ�..
	m_pTable = NULL;    // 6000�� ���� �ε��.. 0.03�� �ҿ�.  1.1MB����Ÿȭ�� �ε�� 1.3��.(�����ʹ� 4����Ʈ �� 40����Ʈ ��� �����ִ� ��)
	m_pData = NULL;


	DWORD dwRet;
	
	if( m_dwAllocFlag == 0)
	{
	   
		dwRet = CheckAlloc();  //�� ó�� �Ҵ��� ���ش�.  m_pData, m_pTable
	   
	}
}
//�Ϲ������� m_dwTableGrow�� �����ϴ� ����Ÿ ���� * 12�� �Ѹ�ŭ���� ���ִ°� ���� ������.
//SetBufferGrow�� ������ ũ�⸦ ����������.



CMKFileWriter::CMKFileWriter(DWORD dwTableGrow, DWORD dwDataGrow) 
: m_dwTableSize(0), m_dwDataSize(0), m_dwUsedTableSize(0), m_dwUsedDataSize(0)
{
	m_dwTableGrow = dwTableGrow;
	m_dwDataGrow = dwDataGrow;
	m_dwAllocFlag=0;
	m_pTable = NULL;
	m_pData = NULL;
	CheckAlloc();
		
}



CMKFileWriter::~CMKFileWriter()
{
	ClearData();  //�޸� ����
}



UINT CMKFileWriter::Add(DWORD dwID, DWORD dwSize, const void *pData)
{
	
	return AddData(dwID , dwSize ,  m_dwUsedDataSize, (char *)pData); 
	// �ܺο��� Data������ �󸶳� ���������� ���ʿ䰡 �����Ƿ� ĸ��ȭ
}



char *CMKFileWriter::GetTotalData(DWORD &dwTotalDataSize)  // TotalDataSize�޴°Ŵ�. ũ��.
{
	char *strTotalData = new char [m_dwUsedTableSize + m_dwUsedDataSize+ sizeof(DWORD) ]; 
	   //4����Ʈ�� �� ���� ����� TableSize�� ���Խ��Ѿ� �Ѵ�.

	DWORD dwTableSize = (m_dwUsedTableSize+sizeof(DWORD));

	memcpy(strTotalData, &dwTableSize,sizeof(DWORD) ); //Table�� ũ�⸦ ��� (����Ÿ �Ǿ� 4����Ʈ)
	memcpy(strTotalData+sizeof(DWORD),m_pTable,m_dwUsedTableSize); //���̺� ������
	memcpy(strTotalData+m_dwUsedTableSize+sizeof(DWORD), m_pData, m_dwUsedDataSize); // ����Ÿ�� ���

	dwTotalDataSize = m_dwUsedTableSize + m_dwUsedDataSize+ sizeof(DWORD);

	return strTotalData;
}



UINT CMKFileWriter::ClearData()
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


	return R_DEFAULT;

}
	


void CMKFileWriter::SetBufferGrow(DWORD dwTableGrow, DWORD dwDataGrow) //���Ҵ�� �����ϴ� ũ���̴�.
{
	m_dwTableGrow = dwTableGrow;
	m_dwDataGrow = dwDataGrow;

}



void CMKFileWriter::WriteDWORD(char *desBuf,DWORD dwValue)
{
	ASSERT( FALSE==IsBadReadPtr(desBuf,sizeof(DWORD) ));
	
	memcpy(desBuf,&dwValue,sizeof(DWORD) );
}



UINT CMKFileWriter::CheckAlloc() // Alloc�� �ؾ��ϴ��� ���ؾ��ϴ��� üũ�� �ϰ� �ʿ�� �Ѵ�.
{
	
	if( m_pTable == NULL) // ���� ���̺� �����Ϳ� �޸𸮰� �Ҵ���� ���� ���
	{
		
		m_pTable = new char[m_dwTableGrow];
		ASSERT(m_pTable != NULL);
		if(m_pTable == NULL ) return R_MALLOC_FAILED;
		m_dwTableSize = m_dwTableGrow;
		m_dwAllocFlag++;
	}
	if( m_pData == NULL) // ���� ����Ÿ �����Ϳ� �޸𸮰� �Ҵ���� ���� ���
	{
		m_pData = new char[m_dwDataGrow];
		ASSERT(m_pData != NULL);
		if(m_pData == NULL ) return R_MALLOC_FAILED;
		m_dwDataSize = m_dwDataGrow;
		m_dwAllocFlag++;
	}
	

	return R_DEFAULT;

}

UINT CMKFileWriter::CheckRealloc(DWORD dwSize) //Realloc�� �ؾ��ϴ��� ���ؾ��ϴ��� üũ�ϰ� �ʿ�� �Ѵ�.
{
	
	if( m_dwUsedTableSize + UNITSIZE > m_dwTableSize )// ���� �Ҵ�� �޸� ������ ��ū �޸� ����� �䱸�Ҷ�
	{
			char *strTmp1;
			
		
			strTmp1 = new char[ m_dwTableSize + m_dwTableGrow ];
			ASSERT( strTmp1!=NULL );
			memcpy(strTmp1,m_pTable,m_dwTableSize);
			delete [] m_pTable;

			m_pTable = strTmp1;
			
			ASSERT( m_pTable != NULL);
			if( m_pTable == NULL ) return R_REALLOC_FAILED;
			m_dwTableSize += m_dwTableGrow;
		
		
		
	}
	if( m_dwUsedDataSize + dwSize > m_dwDataSize )// ���� �Ҵ�� �޸� ������ ��ū �޸� ����� �䱸�Ҷ�
	{
		char *strTmp2;

		if( m_dwUsedDataSize + dwSize < m_dwUsedDataSize+m_dwDataGrow ) //DataGrow���� dwSize�� ������..
		{
			strTmp2 = new char[m_dwDataSize + m_dwDataGrow];/////////////
		    memcpy(strTmp2,m_pData,m_dwDataSize);
		    delete [] m_pData;
		    m_pData = strTmp2;
			ASSERT( m_pData != NULL);
			if( m_pData == NULL ) return R_REALLOC_FAILED;
			m_dwDataSize += m_dwDataGrow;
		}
		else  //DataGrow���� Data��ü�� ��Ŀ������.. DataGrow�� �����ؾ߸´°� �ƴұ�~? -_-�ƴϴ�.�װԾƴ���!!!
		{ //�������ΰ���̹Ƿ� �� ũ�⸸ŭ ������ų��? ... . ��.��..
			//��ũ�⸸ŭ ������Ű�� ��.,�� ������!!
			strTmp2 = new char[m_dwDataSize + dwSize];
			memcpy(strTmp2,m_pData,m_dwDataSize);
			delete [] m_pData;
			m_pData =strTmp2;
			ASSERT( m_pData != NULL);
			if( m_pData == NULL) return R_REALLOC_FAILED;
			m_dwDataSize+=dwSize;
		}
	
	}
	return R_DEFAULT;
}
void CMKFileWriter::WriteData(char *pData, DWORD dwSize, DWORD dwPos)
{
	ASSERT(  FALSE == IsBadReadPtr(pData,dwSize) ); // �߸��� ���������� �ƴ��� Ȯ��.

	memcpy( m_pData + dwPos, pData, dwSize );
}

UINT CMKFileWriter::AddData(DWORD dwID, DWORD dwSize, DWORD dwPos, char *pData)
{
	DWORD dwRet;
	

	if ( (dwRet = CheckRealloc(dwSize)) != R_DEFAULT ) // ���Ҵ��� �ʿ��Ѱ�?
	{
		return dwRet;  //���Ҵ��� ������ ���
	}

	
		WriteDWORD(m_pTable+m_dwUsedTableSize,dwID); //���̵� ���� ����.



		WriteDWORD(m_pTable+m_dwUsedTableSize+4,dwSize); //����Ÿ�� ũ�⸦ ����.



		WriteDWORD(m_pTable+m_dwUsedTableSize+8,dwPos); // ����Ÿ�� ��ġ�� ����.
	

		
		m_dwUsedTableSize += UNITSIZE;    // 12��ŭ ����.(�� 4����Ʈ��)
	
		WriteData(pData,dwSize,dwPos); // ���� ����Ÿ�� ����Ѵ� ����Ÿ��������+dwPos��ġ�� ����Ѵ�.
	

	
		m_dwUsedDataSize += dwSize; // ����� ��ŭ ���� ����� ǥ���Ѵ�.

	
		
	

	
	return R_DEFAULT;

}

