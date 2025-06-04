#pragma once


#include "ProjectBaseView.h"
#include "afxwin.h"
// CInforMCStatusPanel �� ���Դϴ�.

#include "InforSetup_IOPanel.h" 
#include "DustCollector.h"

class CInforMCStatusPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CInforMCStatusPanel)

protected:
	CInforMCStatusPanel();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CInforMCStatusPanel();

public:
	enum { IDD = IDD_INFORMCSTATUSPANEL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	//
	CBitmap m_background;

	CInforSetup_IOPanel*	m_pInforSetup_IOPanel;
	CDustCollector*			m_pDustCollector;
public:
	CRect m_rect;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	afx_msg void OnStnClickedStaticRect();
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushIo();
	void ClickCtpushOthers();
};


