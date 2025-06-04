#include "stdafx.h"
#include "TimeCounter.h"


CTimeCounter::CTimeCounter(void)
{
	Init();
}


CTimeCounter::~CTimeCounter(void)
{
}

void CTimeCounter::Init(void)
{
	m_fStartTime	= 0.0;
	m_fEndTime		= 0.0;
	m_bStartTime    = FALSE;
	m_strTime		= _T("");

}

void CTimeCounter::SetTime(ENUM_TIME_COUNTER_MODE a_eMode)
{
	Init();
	LARGE_INTEGER lpPerformanceCount;
	LARGE_INTEGER lpFrequency;

	double fFrequency;
	double fElapsed;

	DWORD_PTR oldMask;


	if(a_eMode == ENUM_TIME_COUNTER_MODE_GETTICK)
	{
		m_fStartTime = GetTickCount();
	}
	else
	{
		QueryPerformanceFrequency(&lpFrequency);

		oldMask = SetThreadAffinityMask(GetCurrentThread(), 0);
		QueryPerformanceCounter(&lpPerformanceCount);
		SetThreadAffinityMask(GetCurrentThread(), oldMask);
		

		fFrequency = 1.0 / lpFrequency.QuadPart; //1초당 진동수
		fElapsed = lpPerformanceCount.QuadPart * fFrequency;
		m_fStartTime = fElapsed;
	}

	m_bStartTime = TRUE;
}

double CTimeCounter::GetDelayTime(ENUM_TIME_COUNTER_MODE a_eMode , ENUM_TIME_COUNTER_UNIT a_eUnit, int a_nDigit)
{
	if(!m_bStartTime) return 0;

	LARGE_INTEGER lpPerformanceCount;
	LARGE_INTEGER lpFrequency;
	DWORD_PTR oldMask;

	double fFrequency;
	double fElapsed;	
	CString strFormat = _T("");
	m_strTime = _T("");

	if(a_eMode == ENUM_TIME_COUNTER_MODE_GETTICK)
	{
		m_fEndTime = GetTickCount() - m_fStartTime;

		switch (a_eUnit)
		{
		case ENUM_TIME_COUNTER_UNIT_usec:
			m_fEndTime *= 1000;
			break;
		case ENUM_TIME_COUNTER_UNIT_msec:
			break;
		case ENUM_TIME_COUNTER_UNIT_sec:
			m_fEndTime /= 1000;
			break;
		}
	}
	else
	{
		QueryPerformanceFrequency(&lpFrequency);

		oldMask = SetThreadAffinityMask(GetCurrentThread(), 0);
		QueryPerformanceCounter(&lpPerformanceCount);
		SetThreadAffinityMask(GetCurrentThread(), oldMask);

		fFrequency = 1.0 / lpFrequency.QuadPart;//1초당 진동 수.
		fElapsed = lpPerformanceCount.QuadPart * fFrequency;
		m_fEndTime = fElapsed;

		m_fEndTime = m_fEndTime - m_fStartTime;

		switch (a_eUnit)
		{
		case ENUM_TIME_COUNTER_UNIT_usec:
			m_fEndTime *= 1000000;
			break;
		case ENUM_TIME_COUNTER_UNIT_msec:
			m_fEndTime *= 1000;
			break;
		case ENUM_TIME_COUNTER_UNIT_sec:
			break;
		}

	}

	switch(a_eUnit)
	{
	case ENUM_TIME_COUNTER_UNIT_usec:
		if(a_nDigit > 0) strFormat.Format(_T("%%.%df usec"), a_nDigit);
		break;
	case ENUM_TIME_COUNTER_UNIT_msec:
		strFormat.Format(_T("%%.%df msec"), a_nDigit,m_fEndTime);
		break;
	case ENUM_TIME_COUNTER_UNIT_sec:
		strFormat.Format(_T("%%.%df sec"), a_nDigit,m_fEndTime);
		break;
	}
	
	m_strTime.Format(strFormat,m_fEndTime);

	return m_fEndTime;

}


