#pragma once


// CDlgOnlineCheck ��ȭ �����Դϴ�.

class CDlgOnlineCheck : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOnlineCheck)

public:
	CDlgOnlineCheck(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgOnlineCheck();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_OFFLINE_MSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
