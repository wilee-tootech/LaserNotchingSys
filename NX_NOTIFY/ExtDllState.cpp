#include "stdafx.h"
#include "ExtDllState.h"


#define OUTPUTFILENAME 
CExtDllState::CExtDllState()
{
	m_hInsOld = AfxGetResourceHandle();

#ifdef _DEBUG
	m_strDllName = _T("NX_NOTIFY.dll");
#else
	m_strDllName = _T("NX_NOTIFY.dll");
#endif

	AfxSetResourceHandle(::GetModuleHandle(m_strDllName));

}
HINSTANCE CExtDllState::GetCurrentMouduleHandle()
{

#ifdef _DEBUG
	m_strDllName = _T("NX_NOTIFY.dll");
#else
	m_strDllName = _T("NX_NOTIFY.dll");
#endif

	return ::GetModuleHandle(m_strDllName);
}

CExtDllState::~CExtDllState(void)
{
	AfxSetResourceHandle(m_hInsOld);
}
