#pragma once


// CRecipeChangeFail ��ȭ �����Դϴ�.

class CRecipeChangeFail : public CDialogEx
{
	DECLARE_DYNAMIC(CRecipeChangeFail)

public:
	CRecipeChangeFail(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRecipeChangeFail();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RECIPE_CHANGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
