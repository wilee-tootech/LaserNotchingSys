// ExceptionHandler.cpp: implementation of the CExceptionHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExceptionHandler.h"

#include "pch.h"
#include "BugslayerUtil.h"
#include "CrashHandler.h"

#pragma comment(lib, "UnhandledException/BugslayerUtil.lib")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

LONG __stdcall CrashHandlerExceptionFilter( EXCEPTION_POINTERS* pExPtrs);

IExceptionHandler* CExceptionHandler::m_pOuter = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExceptionHandler::CExceptionHandler()
{
	SetUnhandledExceptionFilter(CrashHandlerExceptionFilter);

}

CExceptionHandler::~CExceptionHandler()
{

}


//*****************************************************************************
// CrashHandlerExceptionFilter()
// Purpose : [ ���α׷��� �浹���� ��, ������ �����ϱ� ���ؼ� ȣ��˴ϴ�. ]
// Parameters :	
// [pExPtrs] :
// Returns :	LONG __stdcall
// Last Update : 2001-06-13
//*****************************************************************************
LONG __stdcall CrashHandlerExceptionFilter( EXCEPTION_POINTERS* pExPtrs)
{
	LONG lRet;

// ����� ��� �϶����� �߰� ������ �������� �ʰ�
// EXCEPTION_CONTINUE_SEARCH  ���� ���������ν�
// ���α׷��Ӱ� ����� �� �� �ֵ��� �մϴ�.
#ifdef _DEBUG
	lRet = EXCEPTION_CONTINUE_SEARCH ;
	return lRet;
#else
	lRet = EXCEPTION_EXECUTE_HANDLER;
#endif

	char strText[500] = {'\0',};

	// �� �׾����� �˾Ƴ����� �մϴ�.
	CString strReason;
	strReason.Format("%s",GetFaultReason(pExPtrs));

	CString strTemp;
	strTemp.Format("\n\n - Registers\n\n%s", GetRegisterString(pExPtrs));
	strReason += strTemp;

	CExceptionHandler::m_pOuter->ExceptionInformation(strReason);

	return lRet;
}

