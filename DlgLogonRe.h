#pragma once


// CDlgLogonRe 대화 상자입니다.

class CDlgLogonRe : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLogonRe)

public:
	CDlgLogonRe(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgLogonRe();

// 대화 상자 데이터입니다.
	enum { 
		IDD = IDD_DLG_FAIL_LOGIN,
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void FailContentTextPutIt();
	void SuccContentTextPutIt();
};
