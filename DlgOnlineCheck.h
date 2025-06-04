#pragma once


// CDlgOnlineCheck 대화 상자입니다.

class CDlgOnlineCheck : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOnlineCheck)

public:
	CDlgOnlineCheck(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgOnlineCheck();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OFFLINE_MSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
