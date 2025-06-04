// TimeChecker.cpp: implementation of the CTimeChecker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "TimeChecker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define CHECKIT

CTimeChecker::CTimeChecker()
{
	m_CPUMHZ = 2666;
	DWORD dwThread;
	m_hThread = CreateThread(0,0,TimeThread,this,0,&dwThread);
}

CTimeChecker::~CTimeChecker()
{
	if( WaitForSingleObject(m_hThread,5) == WAIT_TIMEOUT )
	{
		TerminateThread(m_hThread,0);
	}
}

__int64 CTimeChecker::GetCPUTimeStamp()
{

	__int64 stamp;
    __asm
	{
			rdtsc
			lea ebx, stamp
			mov [ebx], eax
			mov [ebx+4], edx
	}
	return stamp;
	
}

void CTimeChecker::Clear()
{
#ifdef CHECKIT
	m_TimeList.RemoveAll();

#endif
}
void CTimeChecker::Check()
{
#ifdef CHECKIT

	__int64 iTime = GetCPUTimeStamp();

	m_TimeList.AddTail(iTime);
#endif

}

CString CTimeChecker::GetResult()
{

	CString strTemp, strTotal;
	__int64 iTime, iTimePrev;
	unsigned int iInterval;
	
	float fMilliSecond;

	strTotal = _T("");
	POSITION pos;

	pos = m_TimeList.GetHeadPosition();
	if( pos !=NULL)
		iTimePrev = m_TimeList.GetNext(pos);
	int i=0;

	while( pos != NULL)
	{
		iTime = m_TimeList.GetNext(pos);
		iInterval = (DWORD)(iTime - iTimePrev);
		fMilliSecond = ((float)( (iTime-iTimePrev)/m_CPUMHZ)  / (float)1000);

		//strTemp.Format("%.2f",(fMilliSecond*0.9)/1000);
		strTemp.Format("%.2f(초) ",fMilliSecond/1000);
		i++;
//		iTimePrev = iTime;
		strTotal=strTemp;		
	}
    
	
	return strTotal;
	
}

void CTimeChecker::SetCPUMHZ(int mhz)
{
	m_CPUMHZ=mhz;
}

DWORD WINAPI CTimeChecker::TimeThread(LPVOID lparam)
{
	CTimeChecker *pMother = (CTimeChecker *)lparam;
	__int64 st,en;
	st = pMother->GetCPUTimeStamp();  // TimeStamp측정시작
	Sleep(2000);
	en = pMother->GetCPUTimeStamp();  // 측정 끝 
	pMother->SetCPUMHZ(int(float(en - st) / float(2000000) ));  // 몇 Mhz 인지 알아낸다.
	return 0;
}

CTimeChecker &CTimeChecker::Instance()
{
	static CTimeChecker TimeChecker;
	return TimeChecker;
}
