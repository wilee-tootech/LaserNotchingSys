#ifndef _CADJMODULE_H
#define _CADJMODULE_H
#pragma once
#include <NX_THREAD/Thread.h>

#pragma region FuctionPointorDefine
class FunctionRun
{
public:
	FunctionRun(){}
	virtual ~FunctionRun(){}
public:
	//	virtual ~Callback()=0; 
	virtual void Run(double fValue)=0;
	virtual void Run(double fObject1,double fObject2)=0;
};

template<typename ClassName>
class Function1DoubleFactor : public FunctionRun
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
	void  (__stdcall ClassName::*StdCallFuntion)(double fVoltage);
	void  (__cdecl ClassName::*CallFuntion)(double fVoltage);
	void  (__thiscall ClassName::*ThisCallFuntion)(double fVoltage);
	void  (__stdcall * NoClassStdCall)(double fVoltage);
	void  (__cdecl * NoClassCall)(double fVoltage);
	void  (__thiscall * NoClassThisCall)(double fVoltage);
#else
	void  (* NoClassX64Call)(double fVoltage);
	void  ( ClassName::*ClassX64Call)(double fVoltage);
#endif
	CallFuncMethod CallbackFuncType;
	int Value;
#ifndef _WIN64
	Function1DoubleFactor(ClassName * OwnerClassName,void (__stdcall ClassName::*Func)(double fVoltage)):Onwer(OwnerClassName),
		StdCallFuntion(Func),CallFuntion(NULL),ThisCallFuntion(NULL),
		NoClassStdCall(NULL),NoClassCall(NULL),NoClassThisCall(NULL)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_STDCALL;
	}

	Function1DoubleFactor(ClassName * OwnerClassName,void (__cdecl ClassName:: *Func)(double fVoltage)):Onwer(OwnerClassName),
		StdCallFuntion(NULL),CallFuntion(Func),ThisCallFuntion(NULL),
		NoClassStdCall(NULL),NoClassCall(NULL),NoClassThisCall(NULL)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_CALL;
	}

	Function1DoubleFactor(ClassName * OwnerClassName,void (__thiscall ClassName::*Func)(double fVoltage)):Onwer(OwnerClassName),
		StdCallFuntion(NULL),CallFuntion(NULL),ThisCallFuntion(Func),
		NoClassStdCall(NULL),NoClassCall(NULL),NoClassThisCall(NULL)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_THISCALL;
	}
	Function1DoubleFactor(ClassName * OwnerClassName,	void  (__stdcall * Func)(double fVoltage)):Onwer(OwnerClassName),
		StdCallFuntion(NULL),CallFuntion(NULL),ThisCallFuntion(NULL),
		NoClassStdCall(Func),NoClassCall(NULL),NoClassThisCall(NULL)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_STDCALL;
	}
	Function1DoubleFactor(ClassName * OwnerClassName,	void  (__cdecl* Func)(double fVoltage)):Onwer(OwnerClassName),
		StdCallFuntion(NULL),CallFuntion(NULL),ThisCallFuntion(NULL),
		NoClassStdCall(NULL),NoClassCall(Func),NoClassThisCall(NULL)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_CALL;
	}

	Function1DoubleFactor(ClassName * OwnerClassName,	void  (__thiscall* Func)(double fVoltage)):Onwer(OwnerClassName),
		StdCallFuntion(NULL),CallFuntion(NULL),ThisCallFuntion(NULL),
		NoClassStdCall(NULL),NoClassCall(NULL),NoClassThisCall(Func)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_THISCALL;
	}
#else
	Function1DoubleFactor(ClassName * OwnerClassName,	void  (ClassName::* Func)(double fVoltage)):Onwer(OwnerClassName),
		ClassX64Call(Func),NoClassX64Call(NULL)
	{

		CallbackFuncType=CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_X64;
	}
	Function1DoubleFactor(ClassName * OwnerClassName,	void  (* Func)(double fVoltage)):Onwer(OwnerClassName),
		ClassX64Call(NULL),NoClassX64Call(Func)

	{

		CallbackFuncType=CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_X64;
	}
#endif
	inline ~Function1DoubleFactor()
	{
#ifndef _WIN64
		StdCallFuntion=NULL,ThisCallFuntion=NULL,CallFuntion=NULL,
			NoClassStdCall=NULL,NoClassCall=NULL,NoClassThisCall=NULL;
#else
		ClassX64Call=NULL ,NoClassX64Call=NULL;
#endif
		CallbackFuncType=CallFuncMethod::CallFuncMethod_NONE;
	}

	void Run(double fValue)
	{
		switch(CallbackFuncType)
		{
#ifndef _WIN64
		case CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_STDCALL:
			(Onwer->*StdCallFuntion)(fValue);
			break;
		case CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_CALL:
			(Onwer->*CallFuntion)(fValue);
			break;

		case CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_THISCALL:
			(Onwer->*ThisCallFuntion)(fValue);
			break;


		case CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_STDCALL:
			(*NoClassStdCall)(fValue);
			break;
		case CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_CALL:
			(*NoClassCall)(fValue);
			break;
		case CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_THISCALL:
			(*NoClassThisCall)(fValue);
			break;
#else
		case CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_X64:
			(*NoClassX64Call)(fValue);
			break;
		case CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_X64:
			(Onwer->*ClassX64Call)(fValue);
			break;
#endif
		}
	}
	void Run(double fObject1,double fObject2)//No Use
	{

	}
};

template<typename ClassName>
class Function2DoubleFactor : public FunctionRun
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
	void  (__stdcall ClassName::*StdCallFuntion)(double ,double);
	void  (__cdecl ClassName::*CallFuntion)(double ,double);
	void  (__thiscall ClassName::*ThisCallFuntion)(double, double);
	void  (__stdcall * NoClassStdCall)(double, double);
	void  (__cdecl * NoClassCall)(double, double);
	void  (__thiscall * NoClassThisCall)(double, double);
#else
	void  (* NoClassX64Call)(double, double);
	void  ( ClassName::*ClassX64Call)(double, double);
#endif
	CallFuncMethod CallbackFuncType;
	int Value;
#ifndef _WIN64
	Function2DoubleFactor(ClassName * OwnerClassName,void (__stdcall ClassName::*Func)(double, double)):Onwer(OwnerClassName),
		StdCallFuntion(Func),CallFuntion(NULL),ThisCallFuntion(NULL),
		NoClassStdCall(NULL),NoClassCall(NULL),NoClassThisCall(NULL)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_STDCALL;
	}

	Function2DoubleFactor(ClassName * OwnerClassName,void (__cdecl ClassName:: *Func)(double, double)):Onwer(OwnerClassName),
		StdCallFuntion(NULL),CallFuntion(Func),ThisCallFuntion(NULL),
		NoClassStdCall(NULL),NoClassCall(NULL),NoClassThisCall(NULL)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_CALL;
	}

	Function2DoubleFactor(ClassName * OwnerClassName,void (__thiscall ClassName::*Func)(double, double)):Onwer(OwnerClassName),
		StdCallFuntion(NULL),CallFuntion(NULL),ThisCallFuntion(Func),
		NoClassStdCall(NULL),NoClassCall(NULL),NoClassThisCall(NULL)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_THISCALL;
	}
	Function2DoubleFactor(ClassName * OwnerClassName,	void  (__stdcall * Func)(double, double)):Onwer(OwnerClassName),
		StdCallFuntion(NULL),CallFuntion(NULL),ThisCallFuntion(NULL),
		NoClassStdCall(Func),NoClassCall(NULL),NoClassThisCall(NULL)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_STDCALL;
	}
	Function2DoubleFactor(ClassName * OwnerClassName,	void  (__cdecl* Func)(double, double)):Onwer(OwnerClassName),
		StdCallFuntion(NULL),CallFuntion(NULL),ThisCallFuntion(NULL),
		NoClassStdCall(NULL),NoClassCall(Func),NoClassThisCall(NULL)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_CALL;
	}

	Function2DoubleFactor(ClassName * OwnerClassName,	void  (__thiscall* Func)(double, double)):Onwer(OwnerClassName),
		StdCallFuntion(NULL),CallFuntion(NULL),ThisCallFuntion(NULL),
		NoClassStdCall(NULL),NoClassCall(NULL),NoClassThisCall(Func)
	{
		CallbackFuncType=CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_THISCALL;
	}
#else
	Function2DoubleFactor(ClassName * OwnerClassName,	void  (ClassName::* Func)(double, double)):Onwer(OwnerClassName),
		ClassX64Call(Func),NoClassX64Call(NULL)
	{

		CallbackFuncType=CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_X64;
	}
	Function2DoubleFactor(ClassName * OwnerClassName,	void  (* Func)(double, double)):Onwer(OwnerClassName),
		ClassX64Call(NULL),NoClassX64Call(Func)

	{

		CallbackFuncType=CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_X64;
	}
#endif
	inline ~Function2DoubleFactor()
	{
#ifndef _WIN64
		StdCallFuntion=NULL,ThisCallFuntion=NULL,CallFuntion=NULL,
			NoClassStdCall=NULL,NoClassCall=NULL,NoClassThisCall=NULL;
#else
		ClassX64Call=NULL ,NoClassX64Call=NULL;
#endif
		CallbackFuncType=CallFuncMethod::CallFuncMethod_NONE;
	}

	void Run(double fValue)//No Use
	{

	}
	void Run(double fObject1,double fObject2)
	{
		switch(CallbackFuncType)
		{
#ifndef _WIN64
		case CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_STDCALL:
			(Onwer->*StdCallFuntion)(fObject1,fObject2);
			break;
		case CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_CALL:
			(Onwer->*CallFuntion)(fObject1,fObject2);
			break;

		case CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_THISCALL:
			(Onwer->*ThisCallFuntion)(fObject1,fObject2);
			break;


		case CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_STDCALL:
			(*NoClassStdCall)(fObject1,fObject2);
			break;
		case CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_CALL:
			(*NoClassCall)(fObject1,fObject2);
			break;
		case CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_THISCALL:
			(*NoClassThisCall)(fObject1,fObject2);
			break;
#else
		case CallFuncMethod::CallFuncMethod_NOEXISTCLASSNAME_X64:
			(*NoClassX64Call)(fObject1,fObject2);
			break;
		case CallFuncMethod::CallFuncMethod_EXISTCLASSNAME_X64:
			(Onwer->*ClassX64Call)(fObject1,fObject2);
			break;
#endif
		}
	}
};
#pragma endregion FuctionPointorDefine

#pragma region BufferClass

class  CDoubleBuffer
{
public:
	CDoubleBuffer();
	CDoubleBuffer(size_t nSize);
	virtual ~CDoubleBuffer();
public:
	bool AllocDataBuffer(size_t nSize);
	void FreefDataBuffer();
	size_t GetDataBufferSize();
	double * GetDataBufferPointor();
	double * GetTimeBufferPointor();
	bool SetData(size_t nIndex,double fData,double fTime);
protected:
	double * m_pfAOIDataBuffer;
	double * m_pfAOITimeDataBuffer;
	size_t   m_fDataBufferSize;

};

#pragma endregion

class CADJModule
{
public:

	#ifndef _WIN64
    template <class TT>
    CADJModule(double fMinVoltage,double fMaxVoltage,TT *Owner, void(__cdecl TT::*pAIVoltage)(double),void(__cdecl TT::*pAIVoltageRange)(double,double)  ) 
	{
		m_pAOValueSetFunc 		= new Function1DoubleFactor<TT> (Owner,pAIVoltage);
		m_pAOVoltRangeFunc		= new Function2DoubleFactor<TT> (Owner,pAIVoltageRange);
		m_pAOValueSetFunc->Run(0.0);
		m_pAOVoltRangeFunc->Run(fMinVoltage,fMaxVoltage);
		m_pTimerThread=new CTimerThread(1,1,this,&CADJModule::Execute);
		m_bLaserSeqRunning = FALSE;
	}
  
    template <class TT>
	CADJModule(double fMinVoltage,double fMaxVoltage,TT *Owner, void(__stdcall TT:: *pAIVoltage)(double),void(__stdcall TT:: *pAIVoltageRange)(double,double)) 
	{
		m_pAOValueSetFunc 		= new Function1DoubleFactor<TT> (Owner,pAIVoltage);
		m_pAOVoltRangeFunc		= new Function2DoubleFactor<TT> (Owner,pAIVoltageRange);
		m_pAOValueSetFunc->Run(0.0);
		m_pAOVoltRangeFunc->Run(fMinVoltage,fMaxVoltage);
		m_pTimerThread=new CTimerThread(1,1,this,&CADJModule::Execute);
		m_bLaserSeqRunning = FALSE;
	}

	template <class TT>
	CADJModule(double fMinVoltage,double fMaxVoltage,TT *Owner, void(__thiscall TT::*pAIVoltage)(double),void(__thiscall TT:: *pAIVoltageRange)(double,double))
	{
		
		m_pAOValueSetFunc 			= new Function1DoubleFactor<TT> (Owner,pAIVoltage);
		m_pAOVoltRangeFunc			= new Function2DoubleFactor<TT> (Owner,pAIVoltageRange);
		m_pAOValueSetFunc->Run(0.0);
		m_pAOVoltRangeFunc->Run(fMinVoltage,fMaxVoltage);
		m_pTimerThread=new CTimerThread(1,1,this,&CADJModule::Execute);
		m_bLaserSeqRunning = FALSE;
	}
	template <class TT>
	CADJModule(double fMinVoltage,double fMaxVoltage,void(__cdecl *pAIVoltage)(double),void(__cdecl *pAIVoltageRange)(double,double))
	{
	
		m_pAOValueSetFunc 			= new Function1DoubleFactor<TT> (NULL,pAIVoltage);
		m_pAOVoltRangeFunc			= new Function2DoubleFactor<TT> (NULL,pAIVoltageRange);
		m_pAOValueSetFunc->Run(0.0);
		m_pAOVoltRangeFunc->Run(fMinVoltage,fMaxVoltage);
		m_pTimerThread=new CTimerThread(1,1,this,&CADJModule::Execute);
		m_bLaserSeqRunning = FALSE;
	}
	template <class TT>
	CADJModule(double fMinVoltage,double fMaxVoltage,void(__stdcall *pAIVoltage)(double),void(__stdcall *pAIVoltageRange)(double,double))
	{
	
		m_pAOValueSetFunc 			= new Function1DoubleFactor<TT> (NULL,pAIVoltage);
		m_pAOVoltRangeFunc			= new Function2DoubleFactor<TT> (NULL,pAIVoltageRange);
		m_pAOValueSetFunc->Run(0.0);
		m_pAOVoltRangeFunc->Run(fMinVoltage,fMaxVoltage);
		m_pTimerThread=new CTimerThread(1,1,this,&CADJModule::Execute);
		m_bLaserSeqRunning = FALSE;

	}
	template <class TT>
	CADJModule(double fMinVoltage,double fMaxVoltage,void(__thiscall *pAIVoltage)(double),void(__thiscall *pAIVoltageRange)(double,double)) 
	{
		m_pAOValueSetFunc 			= new Function1DoubleFactor<TT> (NULL,pAIVoltage);
		m_pAOVoltRangeFunc			= new Function2DoubleFactor<TT> (NULL,pAIVoltageRange);
		m_pAOValueSetFunc->Run(0.0);
		m_pAOVoltRangeFunc->Run(fMinVoltage,fMaxVoltage);
		m_pTimerThread=new CTimerThread(1,1,this,&CADJModule::Execute);
		m_bLaserSeqRunning = FALSE;
	}
#else
	template <class TT>
	CADJModule(double fMinVoltage,double fMaxVoltage,void(*pAIVoltage)(double),void(*pAIVoltageRange)(double,double)) 
	{
	
		m_pAOValueSetFunc 			= new Function1DoubleFactor<TT> (NULL,pAIVoltage);
		m_pAOVoltRangeFunc			= new Function2DoubleFactor<TT> (NULL,pAIVoltageRange);
		m_pAOValueSetFunc->Run(0.0);
		m_pAOVoltRangeFunc->Run(fMinVoltage,fMaxVoltage);
		m_pTimerThread=new CTimerThread(1,1,this,&CADJModule::Execute);
		m_bLaserSeqRunning = FALSE;
	}	
	template <class TT>
	CADJModule(double fMinVoltage,double fMaxVoltage,TT * Owner, void(TT::*pAIVoltage)(double),void(TT::*pAIVoltageRange)(double,double)) 
	{
		m_pAOValueSetFunc 			= new Function1DoubleFactor<TT> (Owner,pAIVoltage);
		m_pAOVoltRangeFunc			= new Function2DoubleFactor<TT> (Owner,pAIVoltageRange);
		m_pAOValueSetFunc->Run(0.0);
		m_pAOVoltRangeFunc->Run(fMinVoltage,fMaxVoltage);
		m_pTimerThread=new CTimerThread(1,1,this,&CADJModule::Execute);
		m_bLaserSeqRunning = FALSE;
	}
#endif
	virtual ~CADJModule(void);

protected:
	int			 m_iStartIndex;
	double		 m_fTmpTime;
	CDoubleBuffer m_fADJBuffer;
	BOOL				m_bLaserSeqRunning;
	
public:


public:
	void StartOutput();
	bool IsRunning();
    void StopOutput();
	bool AllocADJDataBuffer(size_t nSize);
	bool SetADJData(size_t nIndex,double fVoltage,double fOnTime);
	size_t GetADJDataBufferSize();

	double * GetDataBufferPointor();
	double * GetTimeBufferPointor();

	BOOL   GetLaserSeqRunning();

protected:
	inline double TIME_GetQueryTime()
	{
		DWORD_PTR oldMask;
		LARGE_INTEGER freq;
		LARGE_INTEGER cnt;
		QueryPerformanceFrequency(&freq);
		oldMask = SetThreadAffinityMask(GetCurrentThread(), 0);
		QueryPerformanceCounter(&cnt);
		SetThreadAffinityMask(GetCurrentThread(), oldMask);
		double now = (double)cnt.QuadPart / (double)freq.QuadPart;
		return now;// Sec
	}
private:
	void Execute();

private:
	CTimerThread * m_pTimerThread;
	FunctionRun  * m_pAOValueSetFunc;
	FunctionRun  * m_pAOVoltRangeFunc;
};
#endif

