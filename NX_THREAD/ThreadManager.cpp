

//#pragma hdrstop
#include "stdafx.h"
#include "ThreadManager.h"

CThreadMgr* ThreadMgr = NULL;
//---------------------------------------------------------------------------


bool __stdcall CThreadMgr::Initialize( void )
{
	Destroy();
	m_pmapThreadObj.clear();
	return true;
}
bool __stdcall CThreadMgr::Destroy( void )
{
	std::map< std::string, CInterfaceThread * >::iterator  iter;
	CInterfaceThread* pThread = NULL;

	for( iter = m_pmapThreadObj.begin(); iter != m_pmapThreadObj.end(); ++iter)
	{
		pThread = iter->second;

		if( pThread == NULL)	continue;

		pThread->Stop();
		delete pThread;
		pThread = NULL;
	}
	return true;
}

bool __stdcall CThreadMgr::RemoveThread( std::string strKey )
{
	std::map< std::string, CInterfaceThread* >::iterator  itr;
	itr = m_pmapThreadObj.find(strKey);

	if( itr == m_pmapThreadObj.end() )	return false;
	CInterfaceThread* pThread;
	pThread = itr->second;

	if( pThread == NULL)
		return false;

	pThread->Stop();
	pThread->Destory();

	delete pThread;
	pThread = NULL;
	return true;
}
CInterfaceThread* __stdcall CThreadMgr::GetThreadObject( std::string strKey )
{
	std::map< std::string, CInterfaceThread* >::iterator  itr;
	itr = m_pmapThreadObj.find(strKey);

	if( itr == m_pmapThreadObj.end() )	return NULL;
	return itr->second;
}
CThreadMgr::CThreadMgr( void )
{
	Initialize();
}
CThreadMgr::~CThreadMgr( void )
{
	Destroy();
}



