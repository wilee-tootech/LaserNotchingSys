#include "stdafx.h"

#include "MKFileReader.h"
#include "Return.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



CMKFileReader::CMKFileReader()
:m_dwTableSize(0), m_dwCurPos(4), m_dwReadingPos(0)
{
	

}

CMKFileReader::~CMKFileReader()
{


}

//GetAt�� �ڵ�ȭ����!!!!!



// ���̺� ���� : [TableSize][ID][Size][Pos][ID][Size][Pos][ID][Size][Pos]....
// Pos �� ���̺��� ���� ���������� �������̴�.
// �� ����Ÿ�� ã������ TableSize+Pos��ŭ ���ؼ� ã�ƾ��Ѵ�.


//���� ����Ÿ�� ���� �����ش�. ���ϰ��� ���� ��.dwGetSize�� byte������ �����Ʈ���� �˷���.
char *CMKFileReader::GetAt(const char *srcData, DWORD dwFindID, DWORD &dwGetSize, DWORD &dwGetID)
{
	char *strReturnData = NULL;
	DWORD dwID, dwSize, dwPos;

	m_dwReadingPos=0;
	m_dwTableSize = GetDWORD(srcData + m_dwReadingPos);
	m_dwReadingPos+=4;
	
	while ( m_dwReadingPos < m_dwTableSize )
	{
		dwID = GetDWORD( srcData + m_dwReadingPos );
		if( dwID == dwFindID )  // ã���� �ϴ� ���̵� ã����
		{
			dwSize = GetDWORD(srcData + m_dwReadingPos + 4);
			dwPos  = GetDWORD(srcData + m_dwReadingPos + 8);
			strReturnData = new char[dwSize];
			memcpy(strReturnData, srcData+m_dwTableSize+dwPos, dwSize);  // ã�� ����Ÿ�� ī���س��´�.
			dwGetID = dwID;
			dwGetSize = dwSize;
			
			break;
		}
		else
		{
			m_dwReadingPos = m_dwReadingPos + 12;
		}
	}
	if( dwID == dwFindID ) //����� ã�Ƽ� �Ϸ�� �����̸�.
	{
		return strReturnData;
	}
	else    //ã�� ���� ���.
	{
		return NULL;
	}
}

// ��� ���Ǹ� ���� void������ ������ ����Ÿ�� �о ��ȯ���ش�. ��ã���� R_NOTFOUND�� ���ϵȴ�.
// �̸� �ش� ID�� ������ ���� ũ�⸦ �˰� �ִ°�� ���Լ��� ����ϰ� �𸣸� ���Լ��� ����Ѵ�.
UINT CMKFileReader::GetAt(const char *srcData, DWORD dwFindID, void *GetData)
{
	DWORD dwID=0;
	char *pData;
	DWORD dwGetSize;
	pData = GetAt(srcData, dwFindID, dwGetSize, dwID);
	if( pData != NULL)
	{
		memcpy(GetData,pData,dwGetSize);
		delete [] pData;
		return R_DEFAULT;
	}
	else
	{
		return R_NOTFOUND;
	}
}

char *CMKFileReader::GetAt(const char *srcData, DWORD dwFindID, DWORD &dwGetSize)
{
	DWORD dwID;
	return GetAt(srcData,dwFindID,dwGetSize,dwID);
}

//srcData�� ȭ�� ��°�� ����Ÿ�̴��� Ȥ�� ȭ���߿� � Ư�� ����Ÿ�� �� �̿Ͱ���
//������ ���� ��� �� ����Ÿ ��°�̴�. �� ��ó���� [TableSize]�� ���;� �Ѵ�. 
// ó������ �˻��ϰ��� �Ҷ����� �ݵ�� SeekInit�� ���ش�.
char *CMKFileReader::GetNext(const char *srcData,  DWORD &dwGetID, DWORD &dwGetSize)
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
		memcpy(strReturnData, srcData+m_dwTableSize+dwPos, dwSize);  // ã�� ����Ÿ�� ī���س��´�.
		dwGetID = dwID;
		dwGetSize = dwSize;
		m_dwCurPos +=12;

		return strReturnData;
	}
	else
		return NULL;
}

// ���ִ°� ����. 4���� ã�´�. GetNext�ҽÿ� �� ������!! �����൵ �ѹ��� ����� �����Ѵ�.
void CMKFileReader::SeekInit()
{
	m_dwCurPos = 4;
}

DWORD CMKFileReader::GetDWORD(const char *srcData)
{
	DWORD dwRetValue;
	memcpy( &dwRetValue, srcData, sizeof(DWORD) );
	return dwRetValue;
}
// ���� ����Ÿ�� �ش��ϴ� ������Ʈ�� �ٷ� �����ش�.
