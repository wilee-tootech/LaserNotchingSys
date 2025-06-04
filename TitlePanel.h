#pragma once

#include "ProjectBaseView.h"

#include "./RUN_MODULE/RunMgr.h"
#include "./Include/EXTERN/TimeCounter.h"
#include "./RUN_MODULE/RunningDefine.h"
#include "./Include/EXTERN/FileMgr.h"


// CTitlePanel 폼 뷰입니다.

class CTitlePanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CTitlePanel)

protected:
	CTitlePanel();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CTitlePanel();

private:
	CTimeCounter m_TimeCounter;

	DWORD m_dwThreadColor;
	BOOL  m_bTwinkel;
	CString m_strRunMode;
	CString m_strUserMode;
	CString m_strTime;
	CString m_strSW_Version;

	CFileMgr m_FileMgr;

	//
	CBitmap m_background;

public:
	enum { IDD = IDD_TITLEPANEL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

public:

	std::vector<CRect> m_originalRects; // 컨트롤 원래 위치 저장용
	CRect m_originalDlgRect;

	void ResizeControls(float scale);
	void Display();
	void UpdateCommStatus(BOOL bMES, BOOL bLASER1, BOOL bLASER2);
	void UpdateEncInfo(CString str);

private:
	void	Init();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_EVENTSINK_MAP()
	void ClickTiltelUsermodeValue();
};


