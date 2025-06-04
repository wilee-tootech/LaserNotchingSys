#pragma once


// CDlgRecipeDeleteCheck 대화 상자입니다.

class CDlgRecipeDeleteCheck : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRecipeDeleteCheck)

public:
	CDlgRecipeDeleteCheck(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgRecipeDeleteCheck();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_RECIPE_DELETE_CHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSelectRecipe;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	BOOL DeleteRecipe();
	virtual BOOL OnInitDialog();

};
