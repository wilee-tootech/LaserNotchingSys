//---------------------------------------------------------------------------
#include "stdafx.h"
#include "Thread.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")
//---------------------------------------------------------------------------

CTimerThread::CTimerThread(UINT uDelay, UINT uResolution) : m_uDelay(uDelay), m_uResolution(uResolution)
{
	m_hThread 			= NULL;
	m_iThreadID 		= FALSE;
	m_uTimerID 			= FALSE;
	m_uTimeOut			= uDelay*5;
	m_pExecute 			= NULL;
	m_bRun				= false;
	m_hEventID 			= CreateEvent(NULL, FALSE, FALSE, NULL);
	InitializeCriticalSection(&m_cs);
}
CTimerThread::~CTimerThread()
{
	DeleteCriticalSection(&m_cs);

	if( m_hEventID != NULL )
	{
		CloseHandle( (void*) m_hEventID );
		m_hEventID = NULL;
	}

	Stop();

	
	if( m_pExecute )
	{
		delete m_pExecute;
		m_pExecute = NULL;
	}
}
bool __stdcall CTimerThread::Start(void)
{
	return Initialize();
}
bool __stdcall CTimerThread::IsRunning(void)
{
	return m_bRun;
}
bool __stdcall CTimerThread::Stop(void)
{	
	return Destory();
}
bool __stdcall CTimerThread::Initialize(void)
{
	if(m_hThread==NULL)
	{
		m_bRun=true;
		m_hThread = CreateThread(NULL, 0, CTimerThread::_ThreadTask, this, 0, &m_iThreadID);

		if( m_hThread != NULL)
		{
			return CreateMMTimer();
		}
	
	}
   return false;
}
bool __stdcall CTimerThread::Destory()
{
	timeKillEvent( m_uTimerID );

	m_bRun = false;
	WaitForSingleObject( &m_hThread, INFINITE );

	CloseHandle( m_hThread );
	m_hThread = NULL;
	return true;
}
void __stdcall CTimerThread::ThreadTask ()
{
	if( m_pExecute )
		m_pExecute->Run();

}
DWORD WINAPI CTimerThread::_ThreadTask(LPVOID temp)
{
	CTimerThread* pThread = ( CTimerThread* )(temp);
	if( pThread != NULL)
	{
		while(pThread->m_bRun)
		{
			if(WAIT_TIMEOUT != WaitForSingleObject( (void*)pThread->m_hEventID, pThread->m_uTimeOut) )
			{
				EnterCriticalSection(&pThread->m_cs);
				pThread->ThreadTask();
				LeaveCriticalSection(&pThread->m_cs);
			}
		}
	}
	ResetEvent(pThread->m_hThread);
	return 0L;
}
bool __stdcall CTimerThread::CreateMMTimer(void)
{
	m_uTimerID = timeSetEvent( m_uDelay, m_uResolution, CTimerThread::TimerCallback, DWORD(this), TIME_PERIODIC);

	if( m_uTimerID != NULL)
		return true;

		
	return false;
}
void __stdcall CTimerThread::TimerCallback(UINT TimerID, UINT Message, DWORD_PTR User, DWORD_PTR dw1, DWORD_PTR dw2)
{
	CTimerThread* pThread = ( CTimerThread* )(User);	

	if( pThread != NULL && pThread->m_bRun )
		SetEvent(( void* )pThread->m_hEventID);
}
//=====================================  ThreadMag =========================

