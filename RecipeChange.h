#pragma once


// CRecipeChange 대화 상자입니다.

class CRecipeChange : public CDialogEx
{
	DECLARE_DYNAMIC(CRecipeChange)

public:
	CRecipeChange(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRecipeChange();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RECIPE_CHANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
