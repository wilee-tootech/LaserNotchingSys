#ifndef _CMD_MANUAL_PANEL_H_
#define _CMD_MANUAL_PANEL_H_

#pragma once

#include "../ProjectBaseView.h"

// CCmdManualPanel �� ���Դϴ�.

class CCmdManualPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CCmdManualPanel)

protected:
	CCmdManualPanel();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CCmdManualPanel();

public:
	enum { IDD = IDD_CMDMANUALPANEL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	enum ENUM_CMD_MANUAL_SELECT
	{
		ENUM_CMD_MANUAL_MOTION,
		ENUM_CMD_MANUAL_VISION,
		ENUM_CMD_MANUAL_LASER,
		ENUM_CMD_MANUAL_SCANNER
	};

private:
	//
	CBitmap m_background;

public:
	void SetBtnState(ENUM_CMD_MANUAL_SELECT eSel, BOOL bChangeViewCall = TRUE);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushctrlManualMotion();
	void ClickCtpushctrlManualVision();
	void ClickCtpushctrlManualLaser();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	void ClickCtpushctrlManualScanner();
};
#endif

