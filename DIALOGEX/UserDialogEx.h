#pragma once
#include "../Resource.h"

// CUserDialogEx 대화 상자입니다.

class CUserDialogEx : public CDialogEx
{
	DECLARE_DYNAMIC(CUserDialogEx)
private:
	//
	CBitmap m_background;
public:
	
	CUserDialogEx(CWnd* pParent = NULL);   // 표준 생성자입니다.
	CUserDialogEx( int IDD, CWnd* pParent = NULL);
	virtual ~CUserDialogEx();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_USERDIALOGEX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnNcPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedOk();
};
