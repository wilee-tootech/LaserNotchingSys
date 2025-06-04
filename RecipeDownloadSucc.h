#pragma once


// CRecipeDownloadSucc 대화 상자입니다.

class CRecipeDownloadSucc : public CDialogEx
{
	DECLARE_DYNAMIC(CRecipeDownloadSucc)

public:
	CRecipeDownloadSucc(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRecipeDownloadSucc();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SUCC_INSERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
