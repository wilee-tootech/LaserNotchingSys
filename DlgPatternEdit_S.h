#pragma once
#include "BtnST.h"
#include "Resource.h"
#include "FileTreeCtrl2.h"
#include "FileListCtrl2.h"
#include "afxwin.h"
#include "./Include/EXTERN/FileMgr.h"
#include "FieldParameter.h"
#include "IniUtil.h"
#include "../DIALOGEX/UserDialogEx.h"

// CDlgPatternEdit_S 대화 상자입니다.

class CDlgPatternEdit_S : public CUserDialogEx
{
	DECLARE_DYNAMIC(CDlgPatternEdit_S)

public:
	CDlgPatternEdit_S(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgPatternEdit_S();

	_SDI_NOTCH_PATTERN_DATA GetHEAD1Data() const { return m_stSDIPatternHEAD1;}
	_SDI_NOTCH_PATTERN_DATA GetHEAD2Data() const { return m_stSDIPatternHEAD2;}

	_SDI_NOTCH_PATTERN_DATA m_stSDIPatternHEAD1;
	_SDI_NOTCH_PATTERN_DATA m_stSDIPatternHEAD2;

	CComboBox m_cbFlipHEAD1;
	CComboBox m_cbFlipHEAD2;

	CString m_strHEAD1Name;
	
	_NOTCH_PATTERN_DATA m_stPatternDataOfHEAD1;
	_NOTCH_PATTERN_DATA m_stPatternDataOfHEAD2;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SDI_PATTERN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void UpDatePattern(CString strRecipe);
	IniUtil _iniUtil;
	void LoadFromIniFile(CString dataSection, _NOTCH_PATTERN_DATA& stPatternData);
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	void LoadValue();
	DECLARE_EVENTSINK_MAP()
	void ClickCttextHead1Tabwidth1();
	void ClickCttextHead1Tabwidth2();
	void ClickCttextHead1Tabwidth3();
	void ClickCttextHead1Tabwidth4();
	void ClickCttextHead1Tabwidth5();
	void ClickCttextHead1Tabwidth6();
	void ClickCttextHead2Tabwidth1();
	void ClickCttextHead2Tabwidth2();
	void ClickCttextHead2Tabwidth3();
	void ClickCttextHead2Tabwidth4();
	void ClickCttextHead2Tabwidth5();
	void ClickCttextHead2Tabwidth6();
	void ClickCttextHead1CuttingHeight();
	void ClickCttextHead2CuttingHeight();
	void ClickCttextHead1NotchingAngle();
	void ClickCttextHead2NotchingAngle();
	void ClickCttextHead1Nochingwidth();
	void ClickCttextHead2Nochingwidth();
	void ClickCttextHead1NochingOffset();
	void ClickCttextHead2NochingOffset();
	void ClickCttextHead1CuttingAngle();
	void ClickCttextHead2CuttingAngle();
	void ClickCttextHead1NochingOutpos();
	void ClickCttextHead2NochingOutpos();
	void ClickCttextHead1CuttingCount1();
	void ClickCttextHead1CuttingCount2();
	void ClickCttextHead1CuttingCount3();
	void ClickCttextHead1CuttingCount4();
	void ClickCttextHead1CuttingCount5();
	void ClickCttextHead1CuttingCount6();
	void ClickCttextHead2CuttingCount1();
	void ClickCttextHead2CuttingCount2();
	void ClickCttextHead2CuttingCount3();
	void ClickCttextHead2CuttingCount4();
	void ClickCttextHead2CuttingCount5();
	void ClickCttextHead2CuttingCount6();
	void ClickCttextHead1Totalwidth();
	void ClickCttextHead2Totalwidth();
	afx_msg void OnBnClickedCancel();

	
};
