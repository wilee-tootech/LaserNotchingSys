#pragma once


// CDlgLogonRe ��ȭ �����Դϴ�.

class CDlgLogonRe : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLogonRe)

public:
	CDlgLogonRe(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgLogonRe();

// ��ȭ ���� �������Դϴ�.
	enum { 
		IDD = IDD_DLG_FAIL_LOGIN,
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void FailContentTextPutIt();
	void SuccContentTextPutIt();
};
