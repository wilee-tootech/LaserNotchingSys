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

#define UNITSIZE 12         //하나의 데이타 유닛이 12바이트이다.

//  : 화일로 저장되기 전에  [ID][SIZE][POS] 형식으로 만들어주는 클래스
// 테이블 뒤에는 그에 해당하는 데이타 블록이 따라온다.
// realloc테스트 완료  2003.11.04

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/* 크게 보면 
  [ Table  ][ Data ]의 형식으로 되어있다. */


CMKFileWriter::CMKFileWriter() 
: m_dwTableSize(0), m_dwDataSize(0), m_dwUsedTableSize(0), m_dwUsedDataSize(0)
{
	m_dwTableGrow = 2048; //앞의 Table가 증가하는 단위
	m_dwDataGrow = 2048; //데이타가 증가하는 단위. //적당한크기에서 가장 빠르다. Realloc횟수 부담과 초기 할당의 부담간에 조화 필요.
	m_dwAllocFlag=0;    // 이레서 메모리 풀링 시스템을 도입해야할지도 모르겠다. 나중에 속도가 문제된다면..
	m_pTable = NULL;    // 6000개 유닛 로드시.. 0.03초 소요.  1.1MB데이타화일 로드시 1.3초.(데이터는 4바이트 와 40바이트 블록 섞여있는 것)
	m_pData = NULL;


	DWORD dwRet;
	
	if( m_dwAllocFlag == 0)
	{
	   
		dwRet = CheckAlloc();  //맨 처음 할당을 해준다.  m_pData, m_pTable
	   
	}
}
//일반적으로 m_dwTableGrow는 저장하는 데이타 갯수 * 12를 한만큼으로 써주는게 가장 빠르다.
//SetBufferGrow로 적당한 크기를 설정해주자.



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
	ClearData();  //메모리 해제
}



UINT CMKFileWriter::Add(DWORD dwID, DWORD dwSize, const void *pData)
{
	
	return AddData(dwID , dwSize ,  m_dwUsedDataSize, (char *)pData); 
	// 외부에선 Data영역이 얼마나 씌여졌는지 알필요가 없으므로 캡슐화
}



char *CMKFileWriter::GetTotalData(DWORD &dwTotalDataSize)  // TotalDataSize받는거다. 크기.
{
	char *strTotalData = new char [m_dwUsedTableSize + m_dwUsedDataSize+ sizeof(DWORD) ]; 
	   //4바이트는 맨 앞의 헤더에 TableSize를 포함시켜야 한다.

	DWORD dwTableSize = (m_dwUsedTableSize+sizeof(DWORD));

	memcpy(strTotalData, &dwTableSize,sizeof(DWORD) ); //Table의 크기를 기록 (데이타 맨앞 4바이트)
	memcpy(strTotalData+sizeof(DWORD),m_pTable,m_dwUsedTableSize); //테이블 내용기록
	memcpy(strTotalData+m_dwUsedTableSize+sizeof(DWORD), m_pData, m_dwUsedDataSize); // 데이타를 기록

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
	


void CMKFileWriter::SetBufferGrow(DWORD dwTableGrow, DWORD dwDataGrow) //재할당시 증가하는 크기이다.
{
	m_dwTableGrow = dwTableGrow;
	m_dwDataGrow = dwDataGrow;

}



void CMKFileWriter::WriteDWORD(char *desBuf,DWORD dwValue)
{
	ASSERT( FALSE==IsBadReadPtr(desBuf,sizeof(DWORD) ));
	
	memcpy(desBuf,&dwValue,sizeof(DWORD) );
}



UINT CMKFileWriter::CheckAlloc() // Alloc을 해야하는지 안해야하는지 체크를 하고 필요시 한다.
{
	
	if( m_pTable == NULL) // 아직 테이블 포인터에 메모리가 할당되지 않은 경우
	{
		
		m_pTable = new char[m_dwTableGrow];
		ASSERT(m_pTable != NULL);
		if(m_pTable == NULL ) return R_MALLOC_FAILED;
		m_dwTableSize = m_dwTableGrow;
		m_dwAllocFlag++;
	}
	if( m_pData == NULL) // 아직 데이타 포인터에 메모리가 할당되지 않은 경우
	{
		m_pData = new char[m_dwDataGrow];
		ASSERT(m_pData != NULL);
		if(m_pData == NULL ) return R_MALLOC_FAILED;
		m_dwDataSize = m_dwDataGrow;
		m_dwAllocFlag++;
	}
	

	return R_DEFAULT;

}

UINT CMKFileWriter::CheckRealloc(DWORD dwSize) //Realloc을 해야하는지 않해야하는지 체크하고 필요시 한다.
{
	
	if( m_dwUsedTableSize + UNITSIZE > m_dwTableSize )// 현재 할당된 메모리 블럭보다 더큰 메모리 블록을 요구할때
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
	if( m_dwUsedDataSize + dwSize > m_dwDataSize )// 현재 할당된 메모리 블럭보다 더큰 메모리 블록을 요구할때
	{
		char *strTmp2;

		if( m_dwUsedDataSize + dwSize < m_dwUsedDataSize+m_dwDataGrow ) //DataGrow보다 dwSize가 작으면..
		{
			strTmp2 = new char[m_dwDataSize + m_dwDataGrow];/////////////
		    memcpy(strTmp2,m_pData,m_dwDataSize);
		    delete [] m_pData;
		    m_pData = strTmp2;
			ASSERT( m_pData != NULL);
			if( m_pData == NULL ) return R_REALLOC_FAILED;
			m_dwDataSize += m_dwDataGrow;
		}
		else  //DataGrow보다 Data자체가 더커버리면.. DataGrow를 조정해야맞는게 아닐까~? -_-아니다.그게아니지!!!
		{ //예외적인경우이므로 딱 크기만큼 증가시킬까? ... . 으.으..
			//딱크기만큼 증가시키자 ㅡ.,ㅡ 에라이!!
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
	ASSERT(  FALSE == IsBadReadPtr(pData,dwSize) ); // 잘못된 포인터인지 아닌지 확인.

	memcpy( m_pData + dwPos, pData, dwSize );
}

UINT CMKFileWriter::AddData(DWORD dwID, DWORD dwSize, DWORD dwPos, char *pData)
{
	DWORD dwRet;
	

	if ( (dwRet = CheckRealloc(dwSize)) != R_DEFAULT ) // 재할당이 필요한가?
	{
		return dwRet;  //재할당이 실패한 경우
	}

	
		WriteDWORD(m_pTable+m_dwUsedTableSize,dwID); //아이디 값을 쓴다.



		WriteDWORD(m_pTable+m_dwUsedTableSize+4,dwSize); //데이타의 크기를 쓴다.



		WriteDWORD(m_pTable+m_dwUsedTableSize+8,dwPos); // 데이타의 위치를 쓴다.
	

		
		m_dwUsedTableSize += UNITSIZE;    // 12만큼 증가.(각 4바이트씩)
	
		WriteData(pData,dwSize,dwPos); // 실제 데이타를 기록한다 데이타영역시작+dwPos위치에 기록한다.
	

	
		m_dwUsedDataSize += dwSize; // 사용한 만큼 영역 사용을 표시한다.

	
		
	

	
	return R_DEFAULT;

}

