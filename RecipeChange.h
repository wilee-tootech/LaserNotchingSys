#pragma once


// CRecipeChange ��ȭ �����Դϴ�.

class CRecipeChange : public CDialogEx
{
	DECLARE_DYNAMIC(CRecipeChange)

public:
	CRecipeChange(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRecipeChange();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RECIPE_CHANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
