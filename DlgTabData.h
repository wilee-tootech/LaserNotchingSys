#pragma once



// CDlgTabData ��ȭ �����Դϴ�.

class CDlgTabData : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTabData)

public:
	CDlgTabData(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgTabData();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_TABDATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	
	BOOL m_bUseReverse;
	double m_dTabPosition;
	double m_dOffset;
	afx_msg void OnClose();
	virtual void OnOK();
	
};
