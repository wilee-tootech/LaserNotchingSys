#pragma once


// CInsertFail ��ȭ �����Դϴ�.

class CInsertFail : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertFail)

public:
	CInsertFail(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CInsertFail();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_FAIL_INSERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void SetFailText(const CString& text);
};
