// DebugConsole.h: interface for the CDebugConsole class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEBUGCONSOLE_H__3B5D2E8A_9ED0_4B29_90C5_26D61234ABCA__INCLUDED_)
#define AFX_DEBUGCONSOLE_H__3B5D2E8A_9ED0_4B29_90C5_26D61234ABCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////
// data : 2002/7/4
// written by nocut98
//
// [����]
// 1. ������Ʈ�� debugconsole.h �� debugconsole.cpp�� �����Ѵ�.
// 2. #include "debugconsole.h" 
// 3. CONSOLE("ȭ�� �����̳�~\n");

// unreferenced too many actual parameters for macro 'CONSOLE'
// #pragma warning(disable:4002)



/*
#if defined(DEBUG) | defined(_DEBUG)
#define CONSOLE CDebugConsole::getConsole().print
#else
#define CONSOLE(x)
#endif
*/
#define CONSOLE CDebugConsole::getConsole().print
class CDebugConsole
{
public:
	void print(TCHAR* tszMsg, ...);
	virtual ~CDebugConsole();
	static CDebugConsole& getConsole()
	{
		static CDebugConsole gt;
		return gt;
	}
private:
	CDebugConsole();
	HANDLE m_hOut;
};

#endif // !defined(AFX_DEBUGCONSOLE_H__3B5D2E8A_9ED0_4B29_90C5_26D61234ABCA__INCLUDED_)
