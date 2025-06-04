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

//GetAt을 자동화하자!!!!!



// 테이블 형식 : [TableSize][ID][Size][Pos][ID][Size][Pos][ID][Size][Pos]....
// Pos 는 테이블이 끝난 지점부터의 오프셋이다.
// 즉 데이타를 찾을때는 TableSize+Pos만큼 더해서 찾아야한다.


//읽은 데이타를 고대로 돌려준다. 리턴값이 읽은 값.dwGetSize에 byte단위로 몇바이트인지 알려줌.
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
		if( dwID == dwFindID )  // 찾고자 하는 아이디를 찾으면
		{
			dwSize = GetDWORD(srcData + m_dwReadingPos + 4);
			dwPos  = GetDWORD(srcData + m_dwReadingPos + 8);
			strReturnData = new char[dwSize];
			memcpy(strReturnData, srcData+m_dwTableSize+dwPos, dwSize);  // 찾은 데이타를 카피해놓는다.
			dwGetID = dwID;
			dwGetSize = dwSize;
			
			break;
		}
		else
		{
			m_dwReadingPos = m_dwReadingPos + 12;
		}
	}
	if( dwID == dwFindID ) //제대로 찾아서 완료된 상태이면.
	{
		return strReturnData;
	}
	else    //찾지 못한 경우.
	{
		return NULL;
	}
}

// 사용 편의를 위해 void형으로 무조건 데이타를 읽어서 반환해준다. 못찾으면 R_NOTFOUND가 리턴된다.
// 미리 해당 ID의 저장할 공간 크기를 알고 있는경우 이함수를 사용하고 모르면 윗함수를 사용한다.
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

//srcData는 화일 통째의 데이타이던지 혹은 화일중에 어떤 특정 데이타가 또 이와같은
//구조를 가질 경우 그 데이타 통째이다. 즉 맨처음에 [TableSize]가 나와야 한다. 
// 처음부터 검색하고자 할때에는 반드시 SeekInit를 해준다.
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
		memcpy(strReturnData, srcData+m_dwTableSize+dwPos, dwSize);  // 찾은 데이타를 카피해놓는다.
		dwGetID = dwID;
		dwGetSize = dwSize;
		m_dwCurPos +=12;

		return strReturnData;
	}
	else
		return NULL;
}

// 해주는게 좋다. 4부터 찾는다. GetNext할시엔 꼭 해주자!! 안해줘도 한번은 제대로 동작한다.
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
// 얻은 데이타는 해당하는 오브젝트에 바로 던져준다.
