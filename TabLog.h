#pragma once
#include "afxwin.h"
#include "TabPageSSL.h"
#include "ctlistctrl_log.h"
// CTabLog ��ȭ �����Դϴ�.

class CTabLog : public CTabPageSSL
{
	DECLARE_DYNAMIC(CTabLog)

public:
	CTabLog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabLog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TAB_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CCtlistctrl_log m_LogList;
};
