#pragma once


// CInsertFail 대화 상자입니다.

class CInsertFail : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertFail)

public:
	CInsertFail(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInsertFail();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_FAIL_INSERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void SetFailText(const CString& text);
};
