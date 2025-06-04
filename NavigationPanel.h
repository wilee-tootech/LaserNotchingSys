#ifndef _NAVIGATION_PANEL_H_
#define _NAVIGATION_PANEL_H_

#pragma once

#include "ProjectBaseView.h"

//#include "../FORM/MapDetailPopupDlg.h"

// CNavigationPanel �� ���Դϴ�.

class CNavigationPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CNavigationPanel)

protected:
	CNavigationPanel();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

public:

	std::vector<CRect> m_originalRects; // ��Ʈ�� ���� ��ġ �����
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



