#pragma once


// CDlgRecipeDeleteFail ��ȭ �����Դϴ�.

class CDlgRecipeDeleteFail : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRecipeDeleteFail)

public:
	CDlgRecipeDeleteFail(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgRecipeDeleteFail();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_FAIL_DELETE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
