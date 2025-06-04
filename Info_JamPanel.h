#ifndef _INFOR_LOG_JAM_PANEL_H_
#define _INFOR_LOG_JAM_PANEL_H_

#pragma once

#include "ProjectBaseView.h"
#include "./Include/EXTERN/fpspread8.h"


// CInfo_JamPanel �� ���Դϴ�.

class CInfo_JamPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CInfo_JamPanel)

protected:
	CInfo_JamPanel();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CInfo_JamPanel();

public:
	enum { IDD = IDD_INFO_JAMPANEL };
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

public:
	void Display(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CFpspread8 m_spreadJam;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
};

#endif


