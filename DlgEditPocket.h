#pragma once


// CDlgEditPocket ��ȭ �����Դϴ�.

class CDlgEditPocket : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgEditPocket)

public:
	CDlgEditPocket(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgEditPocket();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_TMP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
