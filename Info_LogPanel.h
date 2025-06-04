#ifndef _INFOR_LOG_LOG_PANEL_H_
#define _INFOR_LOG_LOG_PANEL_H_

#pragma once

#include "ProjectBaseView.h"
#include "./Include/EXTERN/fpspread8.h"
#include <locale>


// CInfo_LogPanel �� ���Դϴ�.

class CInfo_LogPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CInfo_LogPanel)

protected:
	CInfo_LogPanel();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CInfo_LogPanel();

public:
	enum { IDD = IDD_INFO_LOGPANEL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	//
	CBitmap m_background;

private:
	void Init(void);
	void Open(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CFpspread8 m_spreadLog;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	afx_msg void OnMcnSelectMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult);
};
#endif

