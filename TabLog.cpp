// TabLog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "TabLog.h"
#include "afxdialogex.h"


// CTabLog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTabLog, CTabPageSSL)

CTabLog::CTabLog(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CTabLog::IDD, pParent)
{

}

CTabLog::~CTabLog()
{
}

void CTabLog::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CTLISTCTRL_LOG, m_LogList);
}


BEGIN_MESSAGE_MAP(CTabLog, CTabPageSSL)
END_MESSAGE_MAP()


// CTabLog 메시지 처리기입니다.
