#pragma once
#include "../Resource.h"

// CUserDialogEx ��ȭ �����Դϴ�.

class CUserDialogEx : public CDialogEx
{
	DECLARE_DYNAMIC(CUserDialogEx)
private:
	//
	CBitmap m_background;
public:
	
	CUserDialogEx(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	CUserDialogEx( int IDD, CWnd* pParent = NULL);
	virtual ~CUserDialogEx();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_USERDIALOGEX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnNcPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedOk();
};
