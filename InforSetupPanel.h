#pragma once

#include "ProjectBaseView.h"
#include "afxwin.h"
#include "DlgIPGDualLaser.h"

// CInforSetupPanel 폼 뷰입니다.

class CInforSetupPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CInforSetupPanel)

protected:
	CInforSetupPanel();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CInforSetupPanel();


public:
	enum { IDD = IDD_INFORSETUPPANEL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	//
	CBitmap m_background;
	//CDlgIPGDualLaser*	m_pDlgIPGDualLaser;


public:
	CRect m_rect;
	CDlgIPGDualLaser*	m_pDlgIPGDualLaser;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushLaser();
};


