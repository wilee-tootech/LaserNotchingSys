//---------------------------------------------------------------------------

#ifndef ThreadManagerH
#define ThreadManagerH

#pragma once
#include "Thread.h"
#include "ThreadInterfaceHeader.h"

#include <string>
#include <iterator>
#include <map>

#ifdef NX_THREAD_DLL_BUILD 
	#define DLL_THREAD_EXPORTS	__declspec( dllexport )
#else 
	#define DLL_THREAD_EXPORTS	__declspec( dllimport )
#endif

//---------------------------------------------------------------------------
class  DLL_THREAD_EXPORTS CThreadMgr
{
// Attribute
public:
	CThreadMgr(void);
	virtual ~CThreadMgr( void );
private:
	std::map< std::string, CInterfaceThread * > m_pmapThreadObj;

private:
	bool __stdcall Initialize( void );
	bool __stdcall Destroy( void );

public:
	
	bool __stdcall RemoveThread( std::string strKey );
	CInterfaceThread* __stdcall GetThreadObject( std::string strKey );
#ifndef _WIN64
	template <class TT>
	bool __stdcall AddThread( std::string strKey ,TT *Owner, void(__cdecl TT::*pExecute)(), int nDelay, int Resolution )
	{
		std::map< std::string, CInterfaceThread* >::iterator  itr;
		CInterfaceThread * pThread=NULL; //= new CTimerThread( pExecute, nDelay, Resolution);

		if( pThread == NULL )
			return false;

		itr = m_pmapThreadObj.find(strKey);

		if( itr != m_pmapThreadObj.end())
			return false;

		//if( pThread->Initialize() == FALSE)
		//	return false;

		std::pair < std::map<std::string, CInterfaceThread*>::iterator, bool> pr;
		pr = m_pmapThreadObj.insert( std::make_pair(strKey, pThread) );

		if( pr.second == false)
		{
			if( pr.second == false )
			{
				pThread->Destory();
				delete pThread;
				pThread = NULL;
				return false;
			}
		}
		return true;
	}
	template <class TT>
	bool __stdcall AddThread( std::string strKey ,TT *Owner, void(__stdcall  TT::*pExecute)(), int nDelay, int Resolution )
	{
		std::map< std::string, CInterfaceThread* >::iterator  itr;
		CInterfaceThread * pThread=new CTimerThread(nDelay, Resolution,Owner,pExecute);

		if( pThread == NULL )
			return false;

		itr = m_pmapThreadObj.find(strKey);

		if( itr != m_pmapThreadObj.end())
			return false;

		//if( pThread->Initialize() == FALSE)
		//	return false;

		std::pair < std::map<std::string, CInterfaceThread*>::iterator, bool> pr;
		pr = m_pmapThreadObj.insert( std::make_pair(strKey, pThread) );

		if( pr.second == false)
		{
			if( pr.second == false )
			{
				pThread->Destory();
				delete pThread;
				pThread = NULL;
				return false;
			}
		}
		return true;
	}
	template <class TT>
	bool __stdcall AddThread( std::string strKey ,TT *Owner, void(__thiscall   TT::*pExecute)(), int nDelay, int Resolution )
	{
		std::map< std::string, CInterfaceThread* >::iterator  itr;
		CInterfaceThread * pThread=new CTimerThread(nDelay, Resolution,Owner,pExecute);

		if( pThread == NULL )
			return false;

		itr = m_pmapThreadObj.find(strKey);

		if( itr != m_pmapThreadObj.end())
			return false;

		//if( pThread->Initialize() == FALSE)
		//	return false;

		std::pair < std::map<std::string, CInterfaceThread*>::iterator, bool> pr;
		pr = m_pmapThreadObj.insert( std::make_pair(strKey, pThread) );

		if( pr.second == false)
		{
			if( pr.second == false )
			{
				pThread->Destory();
				delete pThread;
				pThread = NULL;
				return false;
			}
		}
		return true;
	}
	template <class TT>
	bool __stdcall AddThread( std::string strKey ,TT *Owner, void(__cdecl   *pExecute)(), int nDelay, int Resolution )
	{
		std::map< std::string, CInterfaceThread* >::iterator  itr;
		CInterfaceThread * pThread=new CTimerThread(nDelay, Resolution,Owner,pExecute);

		if( pThread == NULL )
			return false;

		itr = m_pmapThreadObj.find(strKey);

		if( itr != m_pmapThreadObj.end())
			return false;

		//if( pThread->Initialize() == FALSE)
		//	return false;

		std::pair < std::map<std::string, CInterfaceThread*>::iterator, bool> pr;
		pr = m_pmapThreadObj.insert( std::make_pair(strKey, pThread) );

		if( pr.second == false)
		{
			if( pr.second == false )
			{
				pThread->Destory();
				delete pThread;
				pThread = NULL;
				return false;
			}
		}
		return true;
	}
	template <class TT>
	bool __stdcall AddThread( std::string strKey ,TT *Owner, void(__stdcall   *pExecute)(), int nDelay, int Resolution )
	{
		std::map< std::string, CInterfaceThread* >::iterator  itr;
		CInterfaceThread * pThread=new CTimerThread(nDelay, Resolution,Owner,pExecute);

		if( pThread == NULL )
			return false;

		itr = m_pmapThreadObj.find(strKey);

		if( itr != m_pmapThreadObj.end())
			return false;

		//if( pThread->Initialize() == FALSE)
		//	return false;

		std::pair < std::map<std::string, CInterfaceThread*>::iterator, bool> pr;
		pr = m_pmapThreadObj.insert( std::make_pair(strKey, pThread) );

		if( pr.second == false)
		{
			if( pr.second == false )
			{
				pThread->Destory();
				delete pThread;
				pThread = NULL;
				return false;
			}
		}
		return true;
	}

	template <class TT>
	bool __stdcall AddThread( std::string strKey ,TT *Owner, void(__thiscall   *pExecute)(), int nDelay, int Resolution )
	{
		std::map< std::string, CInterfaceThread* >::iterator  itr;
		CInterfaceThread * pThread= new CTimerThread(nDelay, Resolution,Owner,pExecute);

		if( pThread == NULL )
			return false;

		itr = m_pmapThreadObj.find(strKey);

		if( itr != m_pmapThreadObj.end())
			return false;

		//if( pThread->Initialize() == FALSE)
		//	return false;

		std::pair < std::map<std::string, CInterfaceThread*>::iterator, bool> pr;
		pr = m_pmapThreadObj.insert( std::make_pair(strKey, pThread) );

		if( pr.second == false)
		{
			if( pr.second == false )
			{
				pThread->Destory();
				delete pThread;
				pThread = NULL;
				return false;
			}
		}
		return true;
	}
#else

template <class TT>
bool __stdcall AddThread( std::string strKey ,TT *Owner, void( *pExecute)(), int nDelay, int Resolution )
{
	std::map< std::string, CInterfaceThread* >::iterator  itr;
	CInterfaceThread * pThread= new CTimerThread(nDelay, Resolution,Owner,pExecute);

	if( pThread == NULL )
		return false;

	itr = m_pmapThreadObj.find(strKey);

	if( itr != m_pmapThreadObj.end())
		return false;

	//if( pThread->Initialize() == FALSE)
	//	return false;

	std::pair < std::map<std::string, CInterfaceThread*>::iterator, bool> pr;
	pr = m_pmapThreadObj.insert( std::make_pair(strKey, pThread) );

	if( pr.second == false)
	{
		if( pr.second == false )
		{
			pThread->Destory();
			delete pThread;
			pThread = NULL;
			return false;
		}
	}
	return true;
}
template <class TT>
bool __stdcall AddThread( std::string strKey ,TT *Owner, void(TT:: *pExecute)(), int nDelay, int Resolution )
{
	std::map< std::string, CInterfaceThread* >::iterator  itr;
	CInterfaceThread * pThread= new CTimerThread(nDelay, Resolution,Owner,pExecute);

	if( pThread == NULL )
		return false;

	itr = m_pmapThreadObj.find(strKey);

	if( itr != m_pmapThreadObj.end())
		return false;

	//if( pThread->Initialize() == FALSE)
	//	return false;

	std::pair < std::map<std::string, CInterfaceThread*>::iterator, bool> pr;
	pr = m_pmapThreadObj.insert( std::make_pair(strKey, pThread) );

	if( pr.second == false)
	{
		if( pr.second == false )
		{
			pThread->Destory();
			delete pThread;
			pThread = NULL;
			return false;
		}
	}
	return true;
}
#endif
// Constructor & Destructor
};
#endif
extern DLL_THREAD_EXPORTS CThreadMgr* ThreadMgr;

