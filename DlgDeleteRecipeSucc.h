#pragma once


// CDlgDeleteRecipeSucc ��ȭ �����Դϴ�.

class CDlgDeleteRecipeSucc : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDeleteRecipeSucc)

public:
	CDlgDeleteRecipeSucc(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgDeleteRecipeSucc();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_SUCC_DELETE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
