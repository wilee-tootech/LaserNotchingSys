#pragma once


// CDlgRecipeDeleteCheck ��ȭ �����Դϴ�.

class CDlgRecipeDeleteCheck : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRecipeDeleteCheck)

public:
	CDlgRecipeDeleteCheck(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgRecipeDeleteCheck();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_RECIPE_DELETE_CHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSelectRecipe;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	BOOL DeleteRecipe();
	virtual BOOL OnInitDialog();

};
