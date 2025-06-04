#pragma once


// CDlgQMSFail 대화 상자입니다.

class CDlgQMSFail : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgQMSFail)

public:
	CDlgQMSFail(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgQMSFail();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_QMS_FAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
