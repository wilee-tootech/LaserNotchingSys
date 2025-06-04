#ifndef __Thread_Interface_Header_H__2007_06_20__10_34__
#define __Thread_Interface_Header_H__2007_06_20__10_34__
//
/*
class CInterfaceThreadExecute
{
public:
	virtual void __stdcall Execute() = 0;
};
*/


#ifdef NX_THREAD_DLL_BUILD 
#define DLL_THREAD_EXPORTS	__declspec( dllexport )
#else 
#define DLL_THREAD_EXPORTS	__declspec( dllimport )
#endif
class DLL_THREAD_EXPORTS CInterfaceThread
{
public:

	CInterfaceThread(){}
	virtual ~CInterfaceThread(){}
	// Initialize
	virtual bool __stdcall Initialize(void) = 0;

	// Terminate
	virtual bool __stdcall Destory(void) = 0;

	// Start
	virtual bool __stdcall Start(void) = 0;

	virtual bool __stdcall IsRunning(void)=0;
	// Stop
	virtual bool __stdcall Stop(void) = 0;

	// Set Execute Continuous Mode or Once Mode
	//virtual bool __stdcall SetContinuousMode(bool bContinuousMode) = 0;

	// Supsended
	//virtual bool __stdcall IsSuspended(void) = 0;
};
#endif
