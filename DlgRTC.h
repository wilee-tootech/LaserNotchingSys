#pragma once

#include "../DIALOGEX/UserDialogEx.h"
// CDlgRTC ��ȭ �����Դϴ�.

class CDlgRTC : public CUserDialogEx
{
	DECLARE_DYNAMIC(CDlgRTC)

public:
	CDlgRTC(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgRTC();
	void OutPut(int nPortNum);
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_RTC };

	CButtonST	m_btnCancel;
	CButtonST	m_btnOk;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	void DisplayIO(int nID, int bStatus);
	afx_msg void OnBnClickedButtonScannerTest();
	afx_msg void OnBnClickedCheck0();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedCheck9();
	afx_msg void OnBnClickedCheck10();
	afx_msg void OnBnClickedCheck11();
	afx_msg void OnBnClickedCheck12();
	afx_msg void OnBnClickedCheck13();
	afx_msg void OnBnClickedCheck14();
	afx_msg void OnBnClickedCheck15();
};
