#pragma once

#include "ProjectBaseView.h"
#include "./Include/EXTERN/ctpush.h"

// CCmdOperationPanel 폼 뷰입니다.

class CCmdOperationPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CCmdOperationPanel)

protected:
	CCmdOperationPanel();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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


