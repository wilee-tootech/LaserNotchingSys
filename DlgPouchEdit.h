#pragma once
#include "Control\fpspread8.h"
#include "BtnST.h"
#include "Resource.h"
#include "FileTreeCtrl2.h"
#include "FileListCtrl2.h"
#include "afxwin.h"
#include "IniUtil.h"
#include "../DIALOGEX/UserDialogEx.h"

class CDlgPouchEdit : public CUserDialogEx
{
	DECLARE_DYNAMIC(CDlgPouchEdit)

public:
	CDlgPouchEdit(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgPouchEdit();

	CFpspread8 m_NotchingWidthViewer;

	_POCKET_TMP_DATA_ GetParameterData() const { return m_Pouch_Parameter_Data; } 
	_POCKET_TMP_DATA_ m_Pouch_Parameter_Data;

	BOOL m_bProgramStartCheck;

	int m_ModeValue;

	IniUtil _iniUtil;

	void LoadValue();
	void UpDatePattern(CString strRecipe);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_POUCH_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:

	DECLARE_EVENTSINK_MAP()

	void SheetInIt();
	void UpdateSpread();
	void SetNotchingAccWidth(int index, double dChangeValue);
	void SetNotchingAccOffset(int index, double dChangeValue);
	void SetNotchingWidth(int index, double dChangeValue);
	void GetNotchingWidthOffset(int index, double dChangeValue);
	void OnClickCttextCutHeight();
	void OnClickCttextCutWidth();
	void OnClickCttextCutOffset();
	void OnClickCttextTotalHeight();
	void OnClickCttextTotalWidth();
	void OnClickCttextArcDegree();
	void OnClickCttextArcInX();
	void OnClickCttextArcInY();
	void OnClickCttextArcOutX();
	void OnClickCttextArcOutY();
	void ClickCttextTabCount();
	void ClickFpspreadNotchingData(long Col, long Row);
};
