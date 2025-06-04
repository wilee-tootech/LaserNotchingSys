#pragma once

#include "ProjectBaseView.h"
#include "afxwin.h"
#include "DlgIPGDualLaser.h"

// CInforSetupPanel �� ���Դϴ�.

class CInforSetupPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CInforSetupPanel)

protected:
	CInforSetupPanel();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushLaser();
};


