#pragma once


// CRecipeDownloadSucc ��ȭ �����Դϴ�.

class CRecipeDownloadSucc : public CDialogEx
{
	DECLARE_DYNAMIC(CRecipeDownloadSucc)

public:
	CRecipeDownloadSucc(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRecipeDownloadSucc();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_SUCC_INSERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
