#pragma once
#pragma once
#include "NX_KEYPAD\NumberKeyPad.h"
#include "../DIALOGEX/UserDialogEx.h"
#include "FieldParameter.h"
#include "BtnST.h"


#define M_PI		3.1415926535897932384626433832795
// CDlgPatternEdit 대화 상자입니다.

class CDlgPatternEdit : public CUserDialogEx
{
	DECLARE_DYNAMIC(CDlgPatternEdit)

public:

	CButtonST	m_btnCancel;
	CButtonST	m_btnOk;

	CDlgPatternEdit(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgPatternEdit();

	_NOTCH_PATTERN_DATA m_stPatternDataOfHEAD2;
	_NOTCH_PATTERN_DATA m_stPatternDataOfHEAD1;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_PATTERN_EDIT };



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	void ClickCttextTabCountHEAD2();
	void ClickCttextNontabLengthHEAD2();
	void ClickCttextT1CountHEAD2();
	void ClickCttextTnCountHEAD2();
	void ClickCttextTaLengthHEAD2();
	void ClickCttextTabWidthHEAD2();
	void ClickCttextTabPitchHEAD2();
	void ClickCttextTabAngleHEAD2();
	void ClickCttextTabHeightHEAD2();
	void ClickCttextNontabLengthHEAD1();
	void ClickCttextTabCountHEAD1();
	void ClickCttextT1CountHEAD1();
	void ClickCttextTnCountHEAD1();
	void ClickCttextTaLengthHEAD1();
	void ClickCttextTabWidthHEAD1();
	void ClickCttextTabPitchHEAD1();
//	void ClickCttextTabAngleHEAD1();
	void ClickCttextTabHeightHEAD1();
	void ClickCttextTabRAngleHEAD2();
	void ClickCttextTabRAngleHEAD1();
	void ClickCttextTabLAngleHEAD1();
	void UpdateTabData(void);
	void ClickCttextTabLengthHEAD2();
};
