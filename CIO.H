// IO.h: interface for the Module class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IO_H__8CE6E915_3EE7_4528_A506_C450B3A67F19__INCLUDED_)
#define AFX_IO_H__8CE6E915_3EE7_4528_A506_C450B3A67F19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <AFXTEMPL.H>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")	


/////////////////////////////////////////////////////////////////////////////
//
//	<<	Ajin USE >>
//
	#pragma comment(lib, "Library\\Axtlib.lib")	

	// Base Board에 관련된 함수들.
	#include "include\\Azin\\Axtlib.h"
	// Motion Module에 관련된 함수들.
	#include "include\\Azin\\Axtcamc5M.h"
	// IO Module에 관련된 함수들.
	#include "include\\Azin\\axtdio.h"
	// AIO Module에 관련된 함수들.
	#include "include\\Azin\\AxtAIO.h"

//
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// IO Module

#define ON		1
#define on		1
#define OFF		0
#define off		0

#define DI32	0x97	// Digital IN  32점
#define DO32	0x98	// Digital OUT 32점
#define DB32	0x99	// Digital IN 16점 / OUT 16점

/////////////////////////////////////////////////////////////////////////////
//
// CIOParent class
//
class CIOParent
{

public:
	////////////////////////////////////////////////
	// IO Initialize & End
	virtual void InitIO();
	virtual void EndIO();

public:
	////////////////////////////////////////////////
	virtual BOOL	Inp(WORD nAdr);		// Input

	////////////////////////////////////////////////
	virtual void	Outp(WORD nAdr, BOOL onoff);	// Output

	////////////////////////////////////////////////
	virtual BOOL	IsOutp(WORD nAdr);	// Output Status

public:
	virtual void	Write_Outport_dword(INT16 nModuleMo, UINT16 offset, UINT32 lValue);

public:
	virtual void	rSetRepeatMode(BOOL bRepeat);
	virtual void	rSetRepeatIO(int nModuleNo, int nBits);
	virtual BOOL	rIsRepeatIO(int nModuleNo, int nBits);
	virtual void	rRepeatIOOutput();
	CString m_strErrorMessage;

protected:
	BOOL	m_bRepeatMode;	// 반복모드냐..
	BOOL**	m_ppRepeatAdr;	// 반복할 출력의 플래그.

	UINT*	m_pIOModuleType;// 입출력 모듈 타입.
	int		m_nIOModuleSu;	// 입출력 모듈 갯수.

// Construction
public:
	CIOParent();
	virtual ~CIOParent();
};

#endif // !defined(AFX_IO_H__8CE6E915_3EE7_4528_A506_C450B3A67F19__INCLUDED_)
