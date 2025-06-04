// TimeChecker.h: interface for the CTimeChecker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMECHECKER_H__6ADFC905_91A7_4CA2_A2E3_7269FCE67987__INCLUDED_)
#define AFX_TIMECHECKER_H__6ADFC905_91A7_4CA2_A2E3_7269FCE67987__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <AFXTEMPL.H>

#define TC		CTimeChecker::Instance()

class CTimeChecker  
{
public:
	void SetCPUMHZ(int mhz);
	__int64 GetCPUTimeStamp();
	void Clear();
	void Check();
	CString GetResult();

	
	CList<__int64,__int64> m_TimeList;

	CTimeChecker();
	virtual ~CTimeChecker();

	int m_CPUMHZ;  //P4 2Ghz ÀÇ °æ¿ì 2000
	
	static DWORD WINAPI TimeThread(LPVOID lparam);
	static CTimeChecker &Instance();
	HANDLE m_hThread;


};

#endif // !defined(AFX_TIMECHECKER_H__6ADFC905_91A7_4CA2_A2E3_7269FCE67987__INCLUDED_)
