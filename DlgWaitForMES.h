#pragma once


// CDlgWaitForMES ��ȭ �����Դϴ�.

class CDlgWaitForMES : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWaitForMES)

public:
	CDlgWaitForMES(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgWaitForMES();

	void OnTimer(UINT_PTR nIDEvent);

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_WAITMES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	BOOL OnInitDialog();
};
