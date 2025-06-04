#pragma once

#include "ProjectBaseView.h"
#include "afxwin.h"
#include "DlgMES.h"

// CInfoMESPanel 폼 뷰입니다.

class CInfoMESPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CInfoMESPanel)

public:
	CInfoMESPanel();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CInfoMESPanel();

public:
	enum { IDD = IDD_INFORMESPANEL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	//
	CBitmap m_background;

	

public:
	static CInfoMESPanel* GetInstance() {
        static CInfoMESPanel instance;
        return &instance;
    }

	CRect m_rect;
	CDlgMES*	m_pMES;
	CDlgMES *GetDlgMES() const { return m_pMES; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


