#pragma once

#include "BtnST.h"

// CDlgTestCut ��ȭ �����Դϴ�.

class CDlgTestCut : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTestCut)

public:

	CButtonST	m_btnCancel;
	CButtonST	m_btnOk;

	CDlgTestCut(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgTestCut();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_TESTCUTTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
