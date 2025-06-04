#ifndef _NAVIGATION_PANEL_H_
#define _NAVIGATION_PANEL_H_

#pragma once

#include "ProjectBaseView.h"

//#include "../FORM/MapDetailPopupDlg.h"

// CNavigationPanel 폼 뷰입니다.

class CNavigationPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CNavigationPanel)

protected:
	CNavigationPanel();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CNavigationPanel();

public:
	enum { IDD = IDD_NAVIGATIONPANEL };

public:
	enum ENUM_NAVIGATION_SELECT
	{
		ENUM_NAVIGATION_MAIN,
		ENUM_NAVIGATION_RECIPE,
		ENUM_NAVIGATION_MES,
		ENUM_NAVIGATION_PARA,
		ENUM_NAVIGATION_SETUP,
		ENUM_NAVIGATION_MCSTATUS,
		ENUM_NAVIGATION_LOG
	};

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	//
	CBitmap m_background;

	//CMapDetailPopupDlg*	m_pDlgMapDetail;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

public:

	std::vector<CRect> m_originalRects; // 컨트롤 원래 위치 저장용
	CRect m_originalDlgRect;

	int GetControlCount();
	void ResizeControls(float scale);
	void Init(void);
	void SetBtnState(ENUM_NAVIGATION_SELECT eSel, BOOL bChangeViewCall = TRUE);
	void SetEnable(void);
	void UserLoginUpdata(void);

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();

	void ClickCtpushctrlNaviMain();
	void ClickCtpushctrlNaviRecipe();
	void ClickCtpushctrlNaviMes();
	void ClickCtpushctrlNaviPara();
	void ClickCtpushctrlNaviSetup();
	void ClickCtpushctrlNaviMcstatus();
	void ClickCtpushctrlNaviLogin();
	void ClickCtpushctrlNaviExit();

	void ClickCtpushctrlNaviLog();
};
#endif



