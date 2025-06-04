#pragma once


// CDlgRecipeDeleteFail 대화 상자입니다.

class CDlgRecipeDeleteFail : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRecipeDeleteFail)

public:
	CDlgRecipeDeleteFail(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgRecipeDeleteFail();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_FAIL_DELETE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
