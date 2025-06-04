#include "stdafx.h"
#include "ExtDllState.h"


#define OUTPUTFILENAME 
CExtDllState::CExtDllState()
{
	m_hInsOld = AfxGetResourceHandle();

#ifdef DEBUG
	m_strDllName = _T("NX_KEYPAD_D.dll");
#else
	m_strDllName = _T("NX_KEYPAD.dll");
#endif

	AfxSetResourceHandle(::GetModuleHandle(m_strDllName));

}


CExtDllState::~CExtDllState(void)
{
	AfxSetResourceHandle(m_hInsOld);
}
