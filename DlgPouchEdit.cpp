#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgPouchEdit.h"
#include "LoadString.h"
#include "MainFrm.h"
#include <direct.h>
#include "MKObjectApproacher.h"
#include "MKObjectApproacher.h"
#include "MKObjectHandler.h"
#include "PointerContainer.h"

#include "FieldParameter.h"
#include "TransUnit.h"
#include "Util.h"
#include "Vector.h"
#include "InitialTable.h"
#include "MathUtil.h"
#include "IniUtil.h"

#include "PointerContainer.h"
#include "NX_KEYPAD\NumberKeyPad.h"
#include "WriteLog.h"
#include "Defines.h"

#include "Include\EXTERN\cttextctrl.h"
#include "../Include/EXTERN/CColorDefine.h"

IMPLEMENT_DYNAMIC(CDlgPouchEdit, CUserDialogEx)

CDlgPouchEdit::CDlgPouchEdit(CWnd *pParent /*=NULL*/)
	: CUserDialogEx(CDlgPouchEdit::IDD, pParent), m_ModeValue(0)
{
}

CDlgPouchEdit::~CDlgPouchEdit()
{
}

void CDlgPouchEdit::UpDatePattern(CString strRecipe)
{
	_POCKET_TMP_DATA_ parameterData = GetParameterData();

	_iniUtil.SetRecipe(strRecipe);

	CString patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);
	CString optionsPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);

	_iniUtil.SavePouchPatternIni(_T("Parameter"), patternPath, parameterData);

	UpdateData(TRUE);

	_iniUtil.SavePouchOptionsIni(_T("Settings"), optionsPath, m_ModeValue);
}

void CDlgPouchEdit::LoadValue()
{
	SheetInIt();

	m_NotchingWidthViewer.ShowWindow(SW_HIDE);
	Sleep(1);
	m_NotchingWidthViewer.ShowWindow(SW_SHOW);

	UpdateData(FALSE);
}

void CDlgPouchEdit::SheetInIt()
{
	CString patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);
	CString optionsPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);

	_iniUtil.LoadPouchPatternIni(_T("Parameter"), patternPath, m_Pouch_Parameter_Data);

	_iniUtil.LoadPouchOptionsIni(_T("Settings"), optionsPath, m_ModeValue);

	m_NotchingWidthViewer.SetColWidth(1, 8);
	m_NotchingWidthViewer.SetCol(1);
	m_NotchingWidthViewer.SetRow(0);
	m_NotchingWidthViewer.SetRowHeight(0, 30);
	m_NotchingWidthViewer.SetText(_T("기준값"));

	m_NotchingWidthViewer.SetColWidth(2, 7);
	m_NotchingWidthViewer.SetCol(2);
	m_NotchingWidthViewer.SetRow(0);
	m_NotchingWidthViewer.SetText(_T("간격값"));

	m_NotchingWidthViewer.SetColWidth(3, 7);
	m_NotchingWidthViewer.SetCol(3);
	m_NotchingWidthViewer.SetRow(0);
	m_NotchingWidthViewer.SetText(_T("옵셋값"));

	m_NotchingWidthViewer.SetColWidth(4, 8);
	m_NotchingWidthViewer.SetCol(4);
	m_NotchingWidthViewer.SetRow(0);
	m_NotchingWidthViewer.SetText(_T("적용\n기준값"));

	m_NotchingWidthViewer.SetColWidth(5, 7);
	m_NotchingWidthViewer.SetCol(5);
	m_NotchingWidthViewer.SetRow(0);
	m_NotchingWidthViewer.SetText(_T("적용\n간격값"));

	m_NotchingWidthViewer.SetColWidth(6, 7);
	m_NotchingWidthViewer.SetCol(6);
	m_NotchingWidthViewer.SetRow(0);
	m_NotchingWidthViewer.SetText(_T("1회\n탭옵셋"));

	m_NotchingWidthViewer.SetColWidth(7, 7);
	m_NotchingWidthViewer.SetCol(7);
	m_NotchingWidthViewer.SetRow(0);
	m_NotchingWidthViewer.SetText(_T("연동\n탭옵셋"));

	m_NotchingWidthViewer.SetMaxRows(m_Pouch_Parameter_Data.dTabCount);

	UpdateSpread();

	UpdateData(FALSE);
}

BOOL CDlgPouchEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SheetInIt();
	return TRUE;
}

void CDlgPouchEdit::DoDataExchange(CDataExchange *pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_CTTEXT_TOTAL_WIDTH, m_Pouch_Parameter_Data.dTotalWidth);
	DDX_Text(pDX, IDC_CTTEXT_TOTAL_HEIGHT, m_Pouch_Parameter_Data.dTotalHeight);
	DDX_Text(pDX, IDC_CTTEXT_CUT_WIDTH, m_Pouch_Parameter_Data.dCuttingWidth);
	DDX_Text(pDX, IDC_CTTEXT_CUT_HEIGHT, m_Pouch_Parameter_Data.dCuttingHeight);
	DDX_Text(pDX, IDC_CTTEXT_CUT_OFFSET, m_Pouch_Parameter_Data.dCuttingOffset);
	DDX_Text(pDX, IDC_CTTEXT_ARC_IN_X, m_Pouch_Parameter_Data.dArcInXPos);
	DDX_Text(pDX, IDC_CTTEXT_ARC_IN_Y, m_Pouch_Parameter_Data.dArcInYPos);
	DDX_Text(pDX, IDC_CTTEXT_ARC_OUT_X, m_Pouch_Parameter_Data.dArcOutXPos);
	DDX_Text(pDX, IDC_CTTEXT_ARC_OUT_Y, m_Pouch_Parameter_Data.dArcOutYPos);
	DDX_Text(pDX, IDC_CTTEXT_ARC_DEGREE, m_Pouch_Parameter_Data.dArcDegree);
	DDX_Text(pDX, IDC_CTTEXT_TAB_COUNT, m_Pouch_Parameter_Data.dTabCount);

	DDX_Control(pDX, IDC_FPSPREAD_NOTCHING_DATA, m_NotchingWidthViewer);
}

BEGIN_MESSAGE_MAP(CDlgPouchEdit, CDialogEx)
END_MESSAGE_MAP()

// DlgPouchEdit 메시지 처리기입니다.
BEGIN_EVENTSINK_MAP(CDlgPouchEdit, CDialogEx)
ON_EVENT(CDlgPouchEdit, IDC_CTTEXT_CUT_HEIGHT, DISPID_CLICK, CDlgPouchEdit::OnClickCttextCutHeight, VTS_NONE)
ON_EVENT(CDlgPouchEdit, IDC_CTTEXT_CUT_WIDTH, DISPID_CLICK, CDlgPouchEdit::OnClickCttextCutWidth, VTS_NONE)
ON_EVENT(CDlgPouchEdit, IDC_CTTEXT_CUT_OFFSET, DISPID_CLICK, CDlgPouchEdit::OnClickCttextCutOffset, VTS_NONE)
ON_EVENT(CDlgPouchEdit, IDC_CTTEXT_TOTAL_HEIGHT, DISPID_CLICK, CDlgPouchEdit::OnClickCttextTotalHeight, VTS_NONE)
ON_EVENT(CDlgPouchEdit, IDC_CTTEXT_TOTAL_WIDTH, DISPID_CLICK, CDlgPouchEdit::OnClickCttextTotalWidth, VTS_NONE)
ON_EVENT(CDlgPouchEdit, IDC_CTTEXT_ARC_DEGREE, DISPID_CLICK, CDlgPouchEdit::OnClickCttextArcDegree, VTS_NONE)
ON_EVENT(CDlgPouchEdit, IDC_CTTEXT_ARC_IN_X, DISPID_CLICK, CDlgPouchEdit::OnClickCttextArcInX, VTS_NONE)
ON_EVENT(CDlgPouchEdit, IDC_CTTEXT_ARC_IN_Y, DISPID_CLICK, CDlgPouchEdit::OnClickCttextArcInY, VTS_NONE)
ON_EVENT(CDlgPouchEdit, IDC_CTTEXT_ARC_OUT_X, DISPID_CLICK, CDlgPouchEdit::OnClickCttextArcOutX, VTS_NONE)
ON_EVENT(CDlgPouchEdit, IDC_CTTEXT_ARC_OUT_Y, DISPID_CLICK, CDlgPouchEdit::OnClickCttextArcOutY, VTS_NONE)
ON_EVENT(CDlgPouchEdit, IDC_CTTEXT_TAB_COUNT, DISPID_CLICK, CDlgPouchEdit::ClickCttextTabCount, VTS_NONE)
ON_EVENT(CDlgPouchEdit, IDC_FPSPREAD_NOTCHING_DATA, 5, CDlgPouchEdit::ClickFpspreadNotchingData, VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

void CDlgPouchEdit::OnClickCttextCutHeight()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0, 9900.0, m_Pouch_Parameter_Data.dCuttingHeight);

	if (numberdlg.DoModal() == IDOK)
	{
		CWriteLog *log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("[CDlgPouchEdit][OnClickCttextCutHeight] Pouch Cutting Height %lf -> %lf"), m_Pouch_Parameter_Data.dCuttingHeight, numberdlg.GetResultDouble()));
		m_Pouch_Parameter_Data.dCuttingHeight = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}

void CDlgPouchEdit::OnClickCttextCutWidth()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0, 9900.0, m_Pouch_Parameter_Data.dCuttingWidth);

	if (numberdlg.DoModal() == IDOK)
	{
		CWriteLog *log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("[CDlgPouchEdit][OnClickCttextCutWidth] Pouch Cutting Width %lf -> %lf"), m_Pouch_Parameter_Data.dCuttingWidth, numberdlg.GetResultDouble()));
		m_Pouch_Parameter_Data.dCuttingWidth = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}

void CDlgPouchEdit::OnClickCttextCutOffset()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0, 9900.0, m_Pouch_Parameter_Data.dCuttingOffset);

	if (numberdlg.DoModal() == IDOK)
	{
		CWriteLog *log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("[CDlgPouchEdit][OnClickCttextCutOffset] Pouch Cutting Offset %lf -> %lf"), m_Pouch_Parameter_Data.dCuttingOffset, numberdlg.GetResultDouble()));
		m_Pouch_Parameter_Data.dCuttingOffset = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}

void CDlgPouchEdit::OnClickCttextTotalHeight()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0, 9900.0, m_Pouch_Parameter_Data.dTotalHeight);

	if (numberdlg.DoModal() == IDOK)
	{
		CWriteLog *log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("[CDlgPouchEdit][OnClickCttextTotalHeight] Pouch Total Height %lf -> %lf"), m_Pouch_Parameter_Data.dTotalHeight, numberdlg.GetResultDouble()));
		m_Pouch_Parameter_Data.dTotalHeight = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}

void CDlgPouchEdit::OnClickCttextTotalWidth()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0, 9900.0, m_Pouch_Parameter_Data.dTotalWidth);

	if (numberdlg.DoModal() == IDOK)
	{
		CWriteLog *log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("[CDlgPouchEdit][OnClickCttextTotalWidth] Pouch Total Width %lf -> %lf"), m_Pouch_Parameter_Data.dTotalWidth, numberdlg.GetResultDouble()));
		m_Pouch_Parameter_Data.dTotalWidth = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}

void CDlgPouchEdit::OnClickCttextArcDegree()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0, 9900.0, m_Pouch_Parameter_Data.dArcDegree);

	if (numberdlg.DoModal() == IDOK)
	{
		CWriteLog *log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("[CDlgPouchEdit][OnClickCttextArcDegree] Pouch Arc Degree %lf -> %lf"), m_Pouch_Parameter_Data.dArcDegree, numberdlg.GetResultDouble()));
		m_Pouch_Parameter_Data.dArcDegree = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}

void CDlgPouchEdit::OnClickCttextArcInX()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0, 9900.0, m_Pouch_Parameter_Data.dArcInXPos);

	if (numberdlg.DoModal() == IDOK)
	{
		CWriteLog *log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("[CDlgPouchEdit][OnClickCttextArcInX] Pouch Arc In X Pos %lf -> %lf"), m_Pouch_Parameter_Data.dArcInXPos, numberdlg.GetResultDouble()));
		m_Pouch_Parameter_Data.dArcInXPos = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}

void CDlgPouchEdit::OnClickCttextArcInY()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0, 9900.0, m_Pouch_Parameter_Data.dArcInYPos);

	if (numberdlg.DoModal() == IDOK)
	{
		CWriteLog *log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("[CDlgPouchEdit][OnClickCttextArcInY] Pouch Arc In Y Pos %lf -> %lf"), m_Pouch_Parameter_Data.dArcInYPos, numberdlg.GetResultDouble()));
		m_Pouch_Parameter_Data.dArcInYPos = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}

void CDlgPouchEdit::OnClickCttextArcOutX()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0, 9900.0, m_Pouch_Parameter_Data.dArcOutXPos);

	if (numberdlg.DoModal() == IDOK)
	{
		CWriteLog *log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("[CDlgPouchEdit][OnClickCttextArcOutX] Pouch Arc Out X Pos %lf -> %lf"), m_Pouch_Parameter_Data.dArcOutXPos, numberdlg.GetResultDouble()));
		m_Pouch_Parameter_Data.dArcOutXPos = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}

void CDlgPouchEdit::OnClickCttextArcOutY()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0, 9900.0, m_Pouch_Parameter_Data.dArcOutYPos);

	if (numberdlg.DoModal() == IDOK)
	{
		CWriteLog *log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("[CDlgPouchEdit][OnClickCttextArcOutY] Pouch Out Y Pos %lf -> %lf"), m_Pouch_Parameter_Data.dArcOutYPos, numberdlg.GetResultDouble()));
		m_Pouch_Parameter_Data.dArcOutYPos = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}

void CDlgPouchEdit::ClickCttextTabCount()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0, 9900.0, m_Pouch_Parameter_Data.dTabCount);

	if (numberdlg.DoModal() == IDOK)
	{
		CWriteLog *log = NULL;
		m_Pouch_Parameter_Data.dTabCount = numberdlg.GetResultDouble();
		m_NotchingWidthViewer.SetMaxRows(numberdlg.GetResultDouble());

		UpdateData(FALSE);
	}
}

void CDlgPouchEdit::ClickFpspreadNotchingData(long Col, long Row)
{
	VARIANT varOriginOffset, varNotchingWidth;
	CString optionsPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);

	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	SingleScannerParameter HEAD1ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD1Parameter();
	CString PramPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
	_iniUtil.LoadParameterIni(_T("HEAD1"), PramPath, HEAD1ScannerParameter);

	CString ModeValue = _T("");
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"), _T("Mode"), sitePath, ModeValue);
	_POCKET_TMP_DATA_ stPocketData;

	stPocketData = pFieldParameter->GetPocketPatternParameterData();

	const int nTabCnt = stPocketData.dTabCount;
	double dCuttingTotalWidth = 0.0;
	// 마지막탭 기준값 + 커팅 폭 + Arc 길이 -> 이후 무지부 센싱 가능
	dCuttingTotalWidth = stPocketData.dNotchingWidth[nTabCnt - 1] + stPocketData.dCuttingWidth + stPocketData.dArcOutXPos;

	double dSensorCheckLeng = stPocketData.dTotalWidth - dCuttingTotalWidth - HEAD1ScannerParameter.dNGSensorLeng;

	// 　옵셋값일　경우 - 클릭한 열의 노칭값과 그 다음 노칭값을 건드려야 함
	if (Col == 3 && Row != 0)
	{
		m_NotchingWidthViewer.GetText(Col, Row, &varOriginOffset);
		CString tmpNum(varOriginOffset);
		VariantClear(&varOriginOffset);

		CNumberKeyPad nKeypadDlg;
		nKeypadDlg.SetRange(-999.0, dSensorCheckLeng, _ttof(tmpNum));
		if (nKeypadDlg.DoModal() == IDOK)
		{
			CString strGetText = _T("");
			double dOffsetValue = nKeypadDlg.GetResultDouble();
			m_NotchingWidthViewer.SetCol(Col);
			m_NotchingWidthViewer.SetRow(Row);
			strGetText.Format("%.2f", dOffsetValue);
			m_NotchingWidthViewer.SetText(strGetText);

			GetNotchingWidthOffset(Row, dOffsetValue); // 옵셋값만 저장
		}
	}
	else if (Col == 1 && Row != 0) // 노칭 길이 클릭 시
	{
		m_NotchingWidthViewer.GetText(Col, Row, &varNotchingWidth);
		CString tmpNum(varNotchingWidth);
		VariantClear(&varNotchingWidth);

		CNumberKeyPad nKeypadDlg;
		nKeypadDlg.SetRange(0.0, 9999.0, _ttof(tmpNum));
		if (nKeypadDlg.DoModal() == IDOK)
		{
			CString strGetText = _T("");
			double dNotchingValue = nKeypadDlg.GetResultDouble();
			m_NotchingWidthViewer.SetCol(Col);
			m_NotchingWidthViewer.SetRow(Row);
			strGetText.Format("%.2f", dNotchingValue);
			m_NotchingWidthViewer.SetText(strGetText);

			// 이 값을 레시피에 적용되도록 수정
			SetNotchingWidth(Row, dNotchingValue);
		}
	}
	else if (Col == 6 && Row != 0) // 탭 옵셋
	{
		m_NotchingWidthViewer.GetText(Col, Row, &varNotchingWidth);
		CString tmpNum(varNotchingWidth);
		VariantClear(&varNotchingWidth);

		CNumberKeyPad nKeypadDlg;
		nKeypadDlg.SetRange(0.0, 11.0, _ttof(tmpNum));
		if (nKeypadDlg.DoModal() == IDOK)
		{
			CString strGetText = _T("");
			double dNotchingValue = nKeypadDlg.GetResultDouble();

			m_NotchingWidthViewer.SetCol(Col);
			m_NotchingWidthViewer.SetRow(Row);
			strGetText.Format("%.2f", dNotchingValue);
			m_NotchingWidthViewer.SetText(strGetText);

			SetNotchingAccWidth(Row, dNotchingValue);
		}
	}
	else if (Col == 7 && Row != 0) // 탭 옵셋
	{
		m_NotchingWidthViewer.GetText(Col, Row, &varNotchingWidth);
		CString tmpNum(varNotchingWidth);
		VariantClear(&varNotchingWidth);

		CNumberKeyPad nKeypadDlg;
		nKeypadDlg.SetRange(0.0, 11.0, _ttof(tmpNum));
		if (nKeypadDlg.DoModal() == IDOK)
		{
			CString strGetText = _T("");
			double dNotchingValue = nKeypadDlg.GetResultDouble();

			m_NotchingWidthViewer.SetCol(Col);
			m_NotchingWidthViewer.SetRow(Row);
			strGetText.Format("%.2f", dNotchingValue);
			m_NotchingWidthViewer.SetText(strGetText);

			SetNotchingAccOffset(Row, dNotchingValue);
		}
	}
}

void CDlgPouchEdit::SetNotchingAccWidth(int index, double dChangeValue)
{
	if (index < 1 || index > MAX_SPREAD_ROW)
		return; // 유효 범위 체크

	int idx = index - 1; // 배열 인덱스 변환

	m_Pouch_Parameter_Data.dNotchingAccWidth[idx] = dChangeValue;

	UpdateSpread();
}

void CDlgPouchEdit::SetNotchingAccOffset(int index, double dChangeValue)
{
	if (index < 1 || index > MAX_SPREAD_ROW)
		return; // 유효 범위 체크

	int idx = index - 1; // 배열 인덱스 변환

	m_Pouch_Parameter_Data.dNotchingAccOffset[idx] = dChangeValue;

	UpdateSpread();
}

void CDlgPouchEdit::SetNotchingWidth(int index, double dChangeValue)
{
	if (index < 1 || index > MAX_SPREAD_ROW)
		return; // 유효 범위 체크

	int idx = index - 1; // 배열 인덱스 변환

	m_Pouch_Parameter_Data.dNotchingWidth[idx] = dChangeValue;
	m_Pouch_Parameter_Data.dNotchingRealWidth[idx] = dChangeValue + m_Pouch_Parameter_Data.dNotchingWidthOffset[idx];

	UpdateSpread();
}

void CDlgPouchEdit::GetNotchingWidthOffset(int index, double dChangeValue)
{
	m_Pouch_Parameter_Data.dNotchingWidthOffset[index - 1] = dChangeValue;
	m_Pouch_Parameter_Data.dNotchingRealWidth[index - 1] = m_Pouch_Parameter_Data.dNotchingWidth[index - 1] + dChangeValue;

	UpdateSpread();
	UpdateData(FALSE);
}

void CDlgPouchEdit::UpdateSpread()
{
	CString strTmpWidth;
	CString strGabWidth;
	CString strTmpOffset;
	CString strTmpRealWidth;
	CString strTmpAccWidth;
	int nTabCount = m_Pouch_Parameter_Data.dTabCount;

	double dNotchingGabWidth[MAX_SPREAD_ROW] = { 0.0, }; // 노칭길이 배열
	double dTotalWidth = 0.0;
	for (size_t i = 0; i < nTabCount && i < MAX_SPREAD_ROW; i++)
	{
		dNotchingGabWidth[i] = m_Pouch_Parameter_Data.dNotchingWidth[i] - dTotalWidth;
		dTotalWidth += dNotchingGabWidth[i] + m_Pouch_Parameter_Data.dCuttingWidth;
	}

	double dNotchingWidth[MAX_SPREAD_ROW] = { 0.0, }; // 노칭길이 배열
	dTotalWidth = 0.0;
	for (size_t i = 0; i < nTabCount && i < MAX_SPREAD_ROW; i++)
	{
		dNotchingWidth[i] = m_Pouch_Parameter_Data.dNotchingRealWidth[i] - dTotalWidth;
		dTotalWidth += dNotchingWidth[i] + m_Pouch_Parameter_Data.dCuttingWidth;
	}

	for (size_t i = 0; i < nTabCount && i < MAX_SPREAD_ROW; i++)
	{
		m_NotchingWidthViewer.SetCol(1);
		m_NotchingWidthViewer.SetRow(i + 1);
		strTmpWidth.Format("%0.2f", m_Pouch_Parameter_Data.dNotchingWidth[i]);
		m_NotchingWidthViewer.SetText(strTmpWidth);

		m_NotchingWidthViewer.SetCol(2);
		m_NotchingWidthViewer.SetRow(i + 1);
		m_NotchingWidthViewer.SetRowHeight(i + 1, 20);
		strGabWidth.Format("%0.2f", dNotchingGabWidth[i]);
		m_NotchingWidthViewer.SetText(strGabWidth);

		m_NotchingWidthViewer.SetCol(3);
		m_NotchingWidthViewer.SetRow(i + 1);
		strTmpOffset.Format("%0.2f", m_Pouch_Parameter_Data.dNotchingWidthOffset[i]);
		m_NotchingWidthViewer.SetText(strTmpOffset);

		m_NotchingWidthViewer.SetCol(4);
		m_NotchingWidthViewer.SetRow(i + 1);
		strTmpRealWidth.Format("%0.2f", m_Pouch_Parameter_Data.dNotchingRealWidth[i]);
		m_NotchingWidthViewer.SetText(strTmpRealWidth);

		m_NotchingWidthViewer.SetCol(5);
		m_NotchingWidthViewer.SetRow(i + 1);
		m_NotchingWidthViewer.SetRowHeight(i + 1, 20);
		strTmpOffset.Format("%0.2f", dNotchingWidth[i]);
		m_NotchingWidthViewer.SetText(strTmpOffset);

		m_NotchingWidthViewer.SetCol(6);
		m_NotchingWidthViewer.SetRow(i + 1);
		strTmpAccWidth.Format("%0.2f", m_Pouch_Parameter_Data.dNotchingAccWidth[i]);
		m_NotchingWidthViewer.SetText(strTmpAccWidth);

		m_NotchingWidthViewer.SetCol(7);
		m_NotchingWidthViewer.SetRow(i + 1);
		strTmpAccWidth.Format("%0.2f", m_Pouch_Parameter_Data.dNotchingAccOffset[i]);
		m_NotchingWidthViewer.SetText(strTmpAccWidth);
	}
}