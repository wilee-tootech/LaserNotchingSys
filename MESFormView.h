#pragma once

#include "ProjectBaseView.h"
#include "../DIALOGEX/UserTabCtrl.h"
#include "../DIALOGEX/UserDialogEx.h"


#include "TabSetting.h"
#include "TabPowermeter.h"


// CMESFormView �� ���Դϴ�.

class CMESFormView : public CProjectBaseView
{
	DECLARE_DYNCREATE(CMESFormView)

protected:
	

public:
	CMESFormView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMESFormView();

	enum { IDD = IDD_MESFORMVIEW };

	enum E_MES_FORM_TAB 
	{
		E_MES_SETTING,
		E_MES_SETTING2,
	};

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	CUserTabCtrl  m_tabCtrl;

private:
	//
	CBitmap m_background;
	CTabSetting m_TabSetting;
	CTabPowermeter m_TabPowermeter;

	CWnd* m_pCurWnd;
	void Init(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	//virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedOk();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTcnSelchangeTabCtrl(NMHDR *pNMHDR, LRESULT *pResult);
};



