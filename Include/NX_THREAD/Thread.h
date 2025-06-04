//---------------------------------------------------------------------------
#ifndef ThreadH
#define ThreadH

#pragma once
#include <windows.h>
#include "ThreadInterfaceHeader.h"
//---------------------------------------------------------------------------

typedef void ( __stdcall *ThreadAddr)();
class Callback;
class  DLL_THREAD_EXPORTS CTimerThread : public CInterfaceThread
{
private:
	CRITICAL_SECTION m_cs;

public:
	// Start
	virtual bool __stdcall Start(void);
	// Stop
	virtual bool __stdcall Stop(void);

	virtual bool __stdcall IsRunning(void);
	// Terminate
	virtual bool __stdcall Destory(void);
	// Initialize
	virtual bool __stdcall Initialize(void);

protected:
	static DWORD WINAPI _ThreadTask(LPVOID temp);
	void __stdcall ThreadTask ();
	static void __stdcall TimerCallback(UINT TimerID, UINT Message, DWORD_PTR User, DWORD_PTR dw1, DWORD_PTR dw2);
	bool __stdcall CreateMMTimer(void);


private:
	HANDLE	m_hEventID;
	HANDLE  m_hThread;
	DWORD	m_iThreadID;
	UINT	m_uTimerID;
	UINT 	m_uDelay;
	UINT	m_uResolution;
	bool 	m_bRun;
	UINT	m_uTimeOut;
	Callback * m_pExecute;

public:
	// Create & Destroy

	CTimerThread(UINT uDelay, UINT uResolution);
#ifndef _WIN64
   template <class TT>
   CTimerThread(UINT uDelay, UINT uResolution,TT *Owner, void(__cdecl TT::*pExecute)()) : m_uDelay(uDelay), m_uResolution(uResolution)
	{
		m_hThread 			= NULL;
		m_iThreadID 		= FALSE;
		m_uTimerID 			= FALSE;
		m_uTimeOut			= uDelay*5;
		m_bRun				= false;
		m_pExecute 			= new ThreadFunc<TT> (Owner,pExecute);
		m_hEventID 			= CreateEvent(NULL, FALSE, FALSE, NULL);
		InitializeCriticalSection(&m_cs);
	}
  
    template <class TT>
	CTimerThread(UINT uDelay, UINT uResolution,TT *Owner, void(__stdcall TT:: *pExecute)()) : m_uDelay(uDelay), m_uResolution(uResolution)
	{
		m_hThread 			= NULL;
		m_iThreadID 		= FALSE;
		m_uTimerID 			= FALSE;
		m_uTimeOut			= uDelay*5;
		m_bRun				= false;
		m_pExecute 			= new ThreadFunc<TT> (Owner,pExecute);
		m_hEventID 			= CreateEvent(NULL, FALSE, FALSE, NULL);
	    InitializeCriticalSection(&m_cs);
	}
	/*template <class TT>
	CTimerThread(UINT uDelay, UINT uResolution,TT *Owner, void(__fastcall TT:: *pExecute)()) : m_uDelay(uDelay), m_uResolution(uResolution)
	{
		m_hThread 			= NULL;
		m_iThreadID 		= FALSE;
		m_uTimerID 			= FALSE;
		m_uTimeOut			= uDelay*5;
		m_pExecute 			= new ThreadFunc<TT> (Owner,pExecute);
		m_hEventID 			= CreateEvent(NULL, FALSE, FALSE, NULL);
		InitializeCriticalSection(&m_cs);
	}*/
	template <class TT>
	CTimerThread(UINT uDelay, UINT uResolution,TT *Owner, void(__thiscall TT::*pExecute)()) : m_uDelay(uDelay), m_uResolution(uResolution)
	{
		m_hThread 			= NULL;
		m_iThreadID 		= FALSE;
		m_uTimerID 			= FALSE;
		m_uTimeOut			= uDelay*5;
		m_bRun				= false;
		m_pExecute 			= new ThreadFunc<TT> (Owner,pExecute);
		m_hEventID 			= CreateEvent(NULL, FALSE, FALSE, NULL);
		InitializeCriticalSection(&m_cs);
	}
	template <class TT>
	CTimerThread(UINT uDelay, UINT uResolution,TT * Owner,void(__cdecl *pExecute)()) : m_uDelay(uDelay), m_uResolution(uResolution)
	{
		m_hThread 			= NULL;
		m_iThreadID 		= FALSE;
		m_uTimerID 			= FALSE;
		m_uTimeOut			= uDelay*5;
		m_bRun				= false;
		m_pExecute 			= new ThreadFunc<TT> (NULL,pExecute);
		m_hEventID 			= CreateEvent(NULL, FALSE, FALSE, NULL);
		InitializeCriticalSection(&m_cs);
	}
	template <class TT>
	CTimerThread(UINT uDelay, UINT uResolution,TT * Owner, void(__stdcall *pExecute)()) : m_uDelay(uDelay), m_uResolution(uResolution)
	{
		m_hThread 			= NULL;
		m_iThreadID 		= FALSE;
		m_uTimerID 			= FALSE;
		m_uTimeOut			= uDelay*5;
		m_bRun				= false;
		m_pExecute 			= new ThreadFunc<TT> (NULL,pExecute);
		m_hEventID 			= CreateEvent(NULL, FALSE, FALSE, NULL);
		InitializeCriticalSection(&m_cs);
	}
	template <class TT>
	CTimerThread(UINT uDelay, UINT uResolution,TT * Owner, void(__thiscall *pExecute)()) : m_uDelay(uDelay), m_uResolution(uResolution)
	{
		m_hThread 			= NULL;
		m_iThreadID 		= FALSE;
		m_uTimerID 			= FALSE;
		m_uTimeOut			= uDelay*5;
		m_bRun				= false;
		m_pExecute 			= new ThreadFunc<TT> (NULL,pExecute);
		m_hEventID 			= CreateEvent(NULL, FALSE, FALSE, NULL);
		InitializeCriticalSection(&m_cs);
	}
#else
	template <class TT>
	CTimerThread(UINT uDelay, UINT uResolution,TT * Owner, void(*pExecute)()) : m_uDelay(uDelay), m_uResolution(uResolution)
	{
		m_hThread 			= NULL;
		m_iThreadID 		= FALSE;
		m_uTimerID 			= FALSE;
		m_uTimeOut			= uDelay*5;
		m_bRun				= false;
		m_pExecute 			= new ThreadFunc<TT> (NULL,pExecute);
		m_hEventID 			= CreateEvent(NULL, FALSE, FALSE, NULL);
		InitializeCriticalSection(&m_cs);
	}	
	template <class TT>
	CTimerThread(UINT uDelay, UINT uResolution,TT * Owner, void(TT::*pExecute)()) : m_uDelay(uDelay), m_uResolution(uResolution)
	{
		m_hThread 			= NULL;
		m_iThreadID 		= FALSE;
		m_uTimerID 			= FALSE;
		m_uTimeOut			= uDelay*5;
		m_bRun				= false;
		m_pExecute 			= new ThreadFunc<TT> (NULL,pExecute);
		m_hEventID 			= CreateEvent(NULL, FALSE, FALSE, NULL);
		InitializeCriticalSection(&m_cs);
	}
#endif
	virtual~CTimerThread();
};

class Callback
{
public:
	Callback(){}
	virtual ~Callback(){}
public:
	//	virtual ~Callback()=0; 
	virtual void Run()=0;

};

template<typename ClassName>
class ThreadFunc : public Callback
{
public:
	enum CallFuncMethod{
		CallFuncMethod_NONE,
		CallFuncMethod_EXISTCLASSNAME_STDCALL, 
 	    CallFuncMethod_EXISTCLASSNAME_CALL, 
		CallFuncMethod_EXISTCLASSNAME_FASTCALL, 
		CallFuncMethod_EXISTCLASSNAME_THISCALL,
		CallFuncMethod_NOEXISTCLASSNAME_STDCALL, 
		CallFuncMethod_NOEXISTCLASSNAME_CALL, 
		CallFuncMethod_NOEXISTCLASSNAME_FASTCALL, 
		CallFuncMethod_NOEXISTCLASSNAME_THISCALL, 
		CallFuncMethod_EXISTCLASSNAME_X64,
		CallFuncMethod_NOEXISTCLASSNAME_X64,
	};
	ClassName * Onwer;
#ifndef _WIN64
	void  (__stdcall ClassName::*StdCallFuntion)(void);
	void  (__cdecl ClassName::*CallFuntion)(void);
	void  (__thiscall ClassName::*ThisCallFuntion)(void);
	void  (__stdcall * NoClassStdCall)(void);
	void  (__cdecl * NoClassCall)(void);
	void  (__thiscall * NoClassThisCall)(void);
#else
	void  (* NoClassX64Call)(void);
	void  ( ClassName::*ClassX64Call)(void);
#endif
	CallFuncMethod CallbackFuncType;
	int Value;
#ifndef _WIN64
	ThreadFunc(ClassName * OwnerClassName,void (__stdcall ClassName::*Func)(void)):Onwer(OwnerClassName),
		StdCallFuntion(Func),CallFuntion(NULL),ThisCallFuntion(NULL),
		NoClassStdCall(NULL),NoClassCall(NULL),NoClassThisCall(NULL)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_STDCALL;
	}
	
	ThreadFunc(ClassName * OwnerClassName,void (__cdecl ClassName:: *Func)(void)):Onwer(OwnerClassName),
		StdCallFuntion(NULL),CallFuntion(Func),ThisCallFuntion(NULL),
		NoClassStdCall(NULL),NoClassCall(NULL),NoClassThisCall(NULL)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_CALL;
	}
	
	ThreadFunc(ClassName * OwnerClassName,void (__thiscall ClassName::*Func)(void)):Onwer(OwnerClassName),
		StdCallFuntion(NULL),CallFuntion(NULL),ThisCallFuntion(Func),
		NoClassStdCall(NULL),NoClassCall(NULL),NoClassThisCall(NULL)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_THISCALL;
	}
	ThreadFunc(ClassName * OwnerClassName,	void  (__stdcall * Func)(void)):Onwer(OwnerClassName),
		StdCallFuntion(NULL),CallFuntion(NULL),ThisCallFuntion(NULL),
		NoClassStdCall(Func),NoClassCall(NULL),NoClassThisCall(NULL)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_STDCALL;
	}
	ThreadFunc(ClassName * OwnerClassName,	void  (__cdecl* Func)(void)):Onwer(OwnerClassName),
		StdCallFuntion(NULL),CallFuntion(NULL),ThisCallFuntion(NULL),
		NoClassStdCall(NULL),NoClassCall(Func),NoClassThisCall(NULL)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_CALL;
	}
	
	ThreadFunc(ClassName * OwnerClassName,	void  (__thiscall* Func)(void)):Onwer(OwnerClassName),
		StdCallFuntion(NULL),CallFuntion(NULL),ThisCallFuntion(NULL),
		NoClassStdCall(NULL),NoClassCall(NULL),NoClassThisCall(Func)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_THISCALL;
	}
#else
	ThreadFunc(ClassName * OwnerClassName,	void  (ClassName::* Func)(void)):Onwer(OwnerClassName),
			ClassX64Call(Func),NoClassX64Call(NULL)
	{
	
		CallbackFuncType=CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_X64;
	}
	ThreadFunc(ClassName * OwnerClassName,	void  (* Func)(void)):Onwer(OwnerClassName),
		ClassX64Call(NULL),NoClassX64Call(Func)

	{

		CallbackFuncType=CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_X64;
	}
#endif
	inline ~ThreadFunc()
	{
#ifndef _WIN64
		StdCallFuntion=NULL,ThisCallFuntion=NULL,CallFuntion=NULL,
		NoClassStdCall=NULL,NoClassCall=NULL,NoClassThisCall=NULL;
#else
		ClassX64Call=NULL ,NoClassX64Call=NULL;
#endif
		CallbackFuncType=CallFuncMethod::CallFuncMethod_NONE;
	}
	void Run()
	{
		switch(CallbackFuncType)
		{
#ifndef _WIN64
		  case CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_STDCALL:
			(Onwer->*StdCallFuntion)();
			break;
		  case CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_CALL:
			  	(Onwer->*CallFuntion)();
			  break;
		
		  case CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_THISCALL:
			  (Onwer->*ThisCallFuntion)();
			  break;


		 case CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_STDCALL:
			  (*NoClassStdCall)();
			  break;
		 case CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_CALL:
			  (*NoClassCall)();
			  break;
		case CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_THISCALL:
			  (*NoClassThisCall)();
			  break;
#else
		case CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_X64:
			(*NoClassX64Call)();
			break;
		case CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_X64:
			(Onwer->*ClassX64Call)();
			break;
#endif
		}
	
	}
};

#endif

