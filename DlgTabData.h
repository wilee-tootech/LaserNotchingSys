#pragma once



// CDlgTabData 대화 상자입니다.

class CDlgTabData : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTabData)

public:
	CDlgTabData(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgTabData();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_TABDATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	
	BOOL m_bUseReverse;
	double m_dTabPosition;
	double m_dOffset;
	afx_msg void OnClose();
	virtual void OnOK();
	
};
