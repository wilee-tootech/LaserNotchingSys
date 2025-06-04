#ifndef _CMD_LOG_PANEL_H_
#define _CMD_LOG_PANEL_H_

#pragma once
#include "ProjectBaseView.h"


// CCmdLogPanel �� ���Դϴ�.

class CCmdLogPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CCmdLogPanel)

protected:
	CCmdLogPanel();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CCmdLogPanel();

public:

	enum ENUM_CMD_LOG_SELECT
	{
		ENUM_CMD_LOG_LOG,
		ENUM_CMD_LOG_JAM
	};

	enum { IDD = IDD_CMDLOGPANEL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	//
	CBitmap m_background;

public:
	void Init(void);
	void SetBtnState(ENUM_CMD_LOG_SELECT eSel, BOOL bChangeViewCall = TRUE);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushctrlCmdLog();
	void ClickCtpushctrlCmdJam();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
};
#endif

