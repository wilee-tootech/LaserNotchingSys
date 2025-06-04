#pragma once
#include "afxwin.h"
#include "TabPageSSL.h"
#include "ctlistctrl_log.h"
// CTabLog 대화 상자입니다.

class CTabLog : public CTabPageSSL
{
	DECLARE_DYNAMIC(CTabLog)

public:
	CTabLog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTabLog();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TAB_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CCtlistctrl_log m_LogList;
};
