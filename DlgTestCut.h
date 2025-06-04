#pragma once

#include "BtnST.h"

// CDlgTestCut 대화 상자입니다.

class CDlgTestCut : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTestCut)

public:

	CButtonST	m_btnCancel;
	CButtonST	m_btnOk;

	CDlgTestCut(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgTestCut();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_TESTCUTTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonMannualCut();
	afx_msg void OnBnClickedButtonFlagCut();
	afx_msg void OnBnClickedLgsamplegut();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int getAbit(unsigned short x, int n);
	afx_msg void OnBnClickedCheckGuide1();
	

	afx_msg void OnBnClickedOk();
};
