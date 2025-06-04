#pragma once

#include "resource.h"

// CNXDialogEx 대화 상자입니다.

class AFX_EXT_CLASS CNXDialogEx : public CDialogEx
{
	DECLARE_DYNAMIC(CNXDialogEx)

public:
	CNXDialogEx(CWnd* pParent = NULL);   // 표준 생성자입니다.
	CNXDialogEx( int IDD, CWnd* pParent = NULL);
	virtual ~CNXDialogEx();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_NXDIALOGEX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	CBitmap m_background;

public:
	void ResourceThemeInit(HWND a_hwnd, LPCWSTR a_pszSubAppName = _T(""), LPCWSTR a_pszSubLdList = _T("") );

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnNcPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
