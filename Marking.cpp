// Marking.cpp: implementation of the CMarking class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "Marking.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "DataTransmitter.h"

CMarking::CMarking()
{

}

CMarking::~CMarking()
{

}

CMarking* CMarking::m_pMarking = 0;
CMarking* CMarking::GetInstance()
{
	if (m_pMarking == 0) {
		m_pMarking = new CDataTransmitter; // 현재는 Data Trans
	}
	return m_pMarking;
}

/* #define MRK_PAUSE	0  // #define MRK_AUTO	1 //  #define MRK_MANUAL	2 */
void CMarking::SetMarkFlag(int iMarkFlag)
{
	m_iMarkFlag = iMarkFlag;
}

int CMarking::GetMarkFlag()
{
	return m_iMarkFlag;
}

/* 시간을 현재 시간으로 Setting */
void CMarking::InitialTime()
{
	::GetSystemTime(&m_iMarkingTime);
}

/* Setting 된 시간으로부터 지금까지 시간 Return */
int CMarking::GetTime()
{
	SYSTEMTIME sysTime;
	DWORD timeSpan;

	::GetSystemTime(&sysTime);
	timeSpan = sysTime.wMilliseconds - m_iMarkingTime.wMilliseconds;
	timeSpan = timeSpan + (sysTime.wSecond  - m_iMarkingTime.wSecond) * 1000;
	timeSpan = timeSpan + (sysTime.wMinute  - m_iMarkingTime.wMinute) * 1000 * 60;
	timeSpan = timeSpan + (sysTime.wHour	- m_iMarkingTime.wHour) * 1000 * 60 * 60;
	
	return timeSpan;	
}