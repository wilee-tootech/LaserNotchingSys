#pragma once


// CDlgEditPocket 대화 상자입니다.

class CDlgEditPocket : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgEditPocket)

public:
	CDlgEditPocket(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgEditPocket();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_TMP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
