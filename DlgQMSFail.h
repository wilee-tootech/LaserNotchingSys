#pragma once


// CDlgQMSFail ��ȭ �����Դϴ�.

class CDlgQMSFail : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgQMSFail)

public:
	CDlgQMSFail(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgQMSFail();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_QMS_FAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
