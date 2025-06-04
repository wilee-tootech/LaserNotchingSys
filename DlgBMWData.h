#pragma once
#include "NX_KEYPAD\NumberKeyPad.h"
#include "FieldParameter.h"

// CDlgBMWData 대화 상자입니다.

class CDlgBMWData : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBMWData)

public:
	CDlgBMWData(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgBMWData();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_BMW_DATA };



public:
	//double dGraphiteHeight;
	_BMW_DATA_ m_bmwData;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	DECLARE_EVENTSINK_MAP()
	void ClickCttextGraphiteheight();
	virtual BOOL OnInitDialog();



	void SetTextControls();
	void SetStaticTextControl();


	void ClickCttextEndsegmentHeight();
	void ClickCttextEndsegmentLength();
	void ClickCttextFlagCount();
	void ClickCttextInsertsegmentLength();
	void ClickCttextInsertsegmentDeepheight();
	void ClickCttextInsertsegmentHeight();
	void ClickCttextFlagHeight();
	void ClickCttextFlagWaitlength();
	void ClickCttextFlagDeeplength();
	void ClickCttextFlagInoutlegnth();
	afx_msg void OnBnClickedOk();
	void ClickCttextTotalHeight();
	afx_msg void OnBnClickedOk2();
};
