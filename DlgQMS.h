#pragma once
#include "Control\fpspread8.h"
#include "Communicate.h"
#include "DualScannerParameter.h"
#include "Control\ControlHeader.h"
#include "Dsp.h"


class CDlgQMS : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgQMS)

public:
	CDlgQMS(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgQMS();
	CFpspread8		m_SpreadQms;
	static CDlgQMS* GetInstance();
	void SetQMS(CDlgQMS *pDlgQMS);
	void TitleChange(CString title);

	CString strTitle;

private:
	static CDlgQMS* m_pDlgQMS;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_QMS};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void GetTitle(CString strFilePath);
	DECLARE_EVENTSINK_MAP()
	void ClickOk();
	void ClickCancel();
};
