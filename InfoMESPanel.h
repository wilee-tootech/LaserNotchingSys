#pragma once

#include "ProjectBaseView.h"
#include "afxwin.h"
#include "DlgMES.h"

// CInfoMESPanel �� ���Դϴ�.

class CInfoMESPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CInfoMESPanel)

public:
	CInfoMESPanel();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


