#pragma once


// CDlgWaitForMES 대화 상자입니다.

class CDlgWaitForMES : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWaitForMES)

public:
	CDlgWaitForMES(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgWaitForMES();

	void OnTimer(UINT_PTR nIDEvent);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_WAITMES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	BOOL OnInitDialog();
};
