#pragma once


// CRecipeChangeFail 대화 상자입니다.

class CRecipeChangeFail : public CDialogEx
{
	DECLARE_DYNAMIC(CRecipeChangeFail)

public:
	CRecipeChangeFail(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRecipeChangeFail();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RECIPE_CHANGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
