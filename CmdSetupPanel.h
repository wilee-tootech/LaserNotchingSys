#ifndef _CMD_SETUP_PANEL_H_
#define _CMD_SETUP_PANEL_H_

#pragma once

#include "../ProjectBaseView.h"

// CCmdSetupPanel 폼 뷰입니다.

class CCmdSetupPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CCmdSetupPanel)

protected:
	CCmdSetupPanel();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CCmdSetupPanel();

public:
	enum { IDD = IDD_CMDSETUPPANEL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	enum ENUM_CMD_SETUP_SELECT
	{
		ENUM_CMD_SETUP_TEACHING		,
		ENUM_CMD_SETUP_LASER		,
		ENUM_CMD_SETUP_IO			,
		ENUM_CMD_SETUP_CYL_MODULE	,
		ENUM_CMD_SETUP_MOTION		,
		ENUM_CMD_SETUP_VISION
	};

private:
	//
	CBitmap m_background;

public:
	void Init(void);
	void SetBtnState(ENUM_CMD_SETUP_SELECT eSel, BOOL bChangeViewCall = TRUE);
	void SetEnable(void);
	void UserLoginUpdata(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushctrlCmdSetupTeaching();
	void ClickCtpushctrlCmdSetupIo();
	void ClickCtpushctrlCmdSetupCylModule();
	void ClickCtpushctrlCmdSetupLaser();
	void ClickCtpushctrlCmdSetupMotion();
	void ClickCtpushctrlCmdSetupVision();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#endif
