#pragma once

#include "ProjectBaseView.h"
#include "../DIALOGEX/UserTabCtrl.h"
#include "../DIALOGEX/UserDialogEx.h"

// CInforParaPanel 폼 뷰입니다.
#include "DlgDualScannerParameter.h"
#include "DlgFieldParameter.h"

class CInforParaPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CInforParaPanel)

protected:
	CInforParaPanel();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CInforParaPanel();

public:
	enum { IDD = IDD_INFOPARA };

	enum E_MES_FORM_TAB 
	{
		E_MES_PARA,
		E_MES_FIELD_SET,
	};

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	CUserTabCtrl  m_tabCtrl;
	void UpdateInfo();

private:
	//
	CBitmap m_background;
	CWnd* m_pCurWnd;
	void Init(void);


	CDlgDualScannerParameter m_TabDualScannerParameter;
	CDlgFieldParameter		 m_TabFieldParameter;	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTcnSelchangeTabCtrl(NMHDR *pNMHDR, LRESULT *pResult);
};


