#pragma once

#include "ProjectBaseView.h"
#include "./Include/EXTERN/ctpush.h"

// CCmdOperationPanel �� ���Դϴ�.

class CCmdOperationPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CCmdOperationPanel)

protected:
	CCmdOperationPanel();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CCmdOperationPanel();

public:
	enum { IDD = IDD_CMDOPERATIONPANEL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	//
	CBitmap m_background;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CctPush m_btnStart;
	CctPush m_btnStop;
	CctPush m_btnReset;
	CctPush m_btnInit;




	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushctrlOperationStart();
	void ClickCtpushctrlOperationReset();
	void ClickCtpushctrlOperationStop();
	void ClickCtpushctrlOperationInit();
	void ClickCtpushctrlStatusClear();
	void SetActiveButton(int nBtnID);
//	void ClickCtbuttonMinimum();
//	void ClickCtpushctrlMinimum();
	afx_msg void OnBnClickedButton1();
};


