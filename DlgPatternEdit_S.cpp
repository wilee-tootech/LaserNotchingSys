// DlgPatternEdit_S.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgPatternEdit_S.h"
#include "afxdialogex.h"
#include "./Include/EXTERN/FileMgr.h"
#include "NX_KEYPAD\NumberKeyPad.h"
#include "NX_KEYPAD\AlphaKeyPad.h"
#include "WriteLog.h"
#include "./Include\EXTERN\cttextctrl.h"



using namespace std;
const CString INI_FILE_PATH = _T(".\\INI\\SettingSDIPatternEdit.ini"); // 각 레시피마다 바뀌어야할듯.

// CDlgPatternEdit_S 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgPatternEdit_S, CUserDialogEx)

CDlgPatternEdit_S::CDlgPatternEdit_S(CWnd* pParent /*=NULL*/)
	: CUserDialogEx(CDlgPatternEdit_S::IDD, pParent)
{

}

CDlgPatternEdit_S::~CDlgPatternEdit_S()
{
}

void CDlgPatternEdit_S::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_HEAD1_FLIP, m_cbFlipHEAD1);
	DDX_Control(pDX, IDC_COMBO_HEAD2_FLIP ,m_cbFlipHEAD2 );

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_TOTALWIDTH,m_stSDIPatternHEAD1.dCuttingTotalWidth);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_TOTALWIDTH,m_stSDIPatternHEAD2.dCuttingTotalWidth);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_NOCHINGWIDTH,m_stSDIPatternHEAD1.dNochingWidth);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_NOCHINGWIDTH,m_stSDIPatternHEAD2.dNochingWidth);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_NOCHING_OFFSET,m_stSDIPatternHEAD1.dNochingHeight);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_NOCHING_OFFSET,m_stSDIPatternHEAD2.dNochingHeight);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_CUTTING_HEIGHT,m_stSDIPatternHEAD1.dCuttingHeight);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_CUTTING_HEIGHT,m_stSDIPatternHEAD2.dCuttingHeight);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_TABWIDTH1,m_stSDIPatternHEAD1.dCuttingTabWidth1);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_TABWIDTH1,m_stSDIPatternHEAD2.dCuttingTabWidth1);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_TABWIDTH2,m_stSDIPatternHEAD1.dCuttingTabWidth2);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_TABWIDTH2,m_stSDIPatternHEAD2.dCuttingTabWidth2);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_TABWIDTH3,m_stSDIPatternHEAD1.dCuttingTabWidth3);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_TABWIDTH3,m_stSDIPatternHEAD2.dCuttingTabWidth3);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_TABWIDTH4,m_stSDIPatternHEAD1.dCuttingTabWidth4);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_TABWIDTH4,m_stSDIPatternHEAD2.dCuttingTabWidth4);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_TABWIDTH5,m_stSDIPatternHEAD1.dCuttingTabWidth5);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_TABWIDTH5,m_stSDIPatternHEAD2.dCuttingTabWidth5);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_TABWIDTH6,m_stSDIPatternHEAD1.dCuttingTabWidth6);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_TABWIDTH6,m_stSDIPatternHEAD2.dCuttingTabWidth6);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_CUTTING_COUNT1,m_stSDIPatternHEAD1.dCuttingCount1);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_CUTTING_COUNT1,m_stSDIPatternHEAD2.dCuttingCount1);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_CUTTING_COUNT2,m_stSDIPatternHEAD1.dCuttingCount2);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_CUTTING_COUNT2,m_stSDIPatternHEAD2.dCuttingCount2);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_CUTTING_COUNT3,m_stSDIPatternHEAD1.dCuttingCount3);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_CUTTING_COUNT3,m_stSDIPatternHEAD2.dCuttingCount3);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_CUTTING_COUNT4,m_stSDIPatternHEAD1.dCuttingCount4);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_CUTTING_COUNT4,m_stSDIPatternHEAD2.dCuttingCount4);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_CUTTING_COUNT5,m_stSDIPatternHEAD1.dCuttingCount5);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_CUTTING_COUNT5,m_stSDIPatternHEAD2.dCuttingCount5);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_CUTTING_COUNT6,m_stSDIPatternHEAD1.dCuttingCount6);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_CUTTING_COUNT6,m_stSDIPatternHEAD2.dCuttingCount6);
	
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_CUTTING_ANGLE,m_stSDIPatternHEAD1.dCuttingAngle);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_CUTTING_ANGLE,m_stSDIPatternHEAD2.dCuttingAngle);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_NOTCHING_ANGLE,m_stSDIPatternHEAD1.dNochingAngle);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_NOTCHING_ANGLE,m_stSDIPatternHEAD2.dNochingAngle);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_NOCHING_OUTPOS,m_stSDIPatternHEAD1.dNochingOutPosWidth);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_NOCHING_OUTPOS,m_stSDIPatternHEAD2.dNochingOutPosWidth);

}


BEGIN_MESSAGE_MAP(CDlgPatternEdit_S, CUserDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgPatternEdit_S::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgPatternEdit_S::OnBnClickedCancel)


END_MESSAGE_MAP()


// CDlgPatternEdit_S 메시지 처리기입니다.

void CDlgPatternEdit_S::UpDatePattern(CString strRecipe)
{
	_iniUtil.SetRecipe(strRecipe);
	CString strTmp;
	GetDlgItemText(IDC_COMBO_HEAD1_FLIP, strTmp);
	if(strTmp == "YES")
	{
		m_stSDIPatternHEAD1.bFlip = TRUE;
	} else
	{
		m_stSDIPatternHEAD1.bFlip = FALSE;
	}

	GetDlgItemText(IDC_COMBO_HEAD2_FLIP, strTmp);
	if(strTmp == "YES")
	{
		m_stSDIPatternHEAD2.bFlip = TRUE;
	} else
	{
		m_stSDIPatternHEAD2.bFlip = FALSE;
	}

	if(IsDlgButtonChecked(IDC_RADIO_OUT_TO_IN))
	{
		m_stSDIPatternHEAD1.nCuttingMode = 0;
	}
	else if(IsDlgButtonChecked(IDC_RADIO_IN_TO_OUT))
	{
		m_stSDIPatternHEAD1.nCuttingMode = 1;
	}
	else if(IsDlgButtonChecked(IDC_RADIO_IN_AND_OUT))
	{
		m_stSDIPatternHEAD1.nCuttingMode = 2;
	}


	if(IsDlgButtonChecked(IDC_RADIO_OUT_TO_IN2))
	{
		m_stSDIPatternHEAD2.nCuttingMode = 0;
	}
	else if(IsDlgButtonChecked(IDC_RADIO_IN_TO_OUT2))
	{
		m_stSDIPatternHEAD2.nCuttingMode = 1;
	}
	else if(IsDlgButtonChecked(IDC_RADIO_IN_AND_OUT2))
	{
		m_stSDIPatternHEAD2.nCuttingMode = 2;
	}

	_SDI_NOTCH_PATTERN_DATA HEAD1Data = GetHEAD1Data();
	_SDI_NOTCH_PATTERN_DATA HEAD2Data = GetHEAD2Data();

	CString patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);
	CString optionsPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);

	_iniUtil.SaveSDIPatternIni(_T("HEAD1"), patternPath, HEAD1Data);
	_iniUtil.SaveSDIPatternIni(_T("HEAD2"), patternPath, HEAD2Data);
}

void CDlgPatternEdit_S::OnBnClickedOk()
{
	_SDI_NOTCH_PATTERN_DATA HEAD1Data = GetHEAD1Data();
	_SDI_NOTCH_PATTERN_DATA HEAD2Data = GetHEAD2Data();

	CString patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);
	CString optionsPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);

	_iniUtil.SaveSDIPatternIni(_T("HEAD1"), patternPath, HEAD1Data);
	_iniUtil.SaveSDIPatternIni(_T("HEAD2"), patternPath, HEAD2Data);

	CUserDialogEx::OnOK();
}

void CDlgPatternEdit_S::LoadFromIniFile(CString dataSection, _NOTCH_PATTERN_DATA& stPatternData) // Anode or Cathode
{
	CFileMgr pFileMgr;

	//// Pattern Edit _ Parameter
	//stPatternData.bYFlip = pFileMgr.ReadBool(dataSection, _T("Flip"), INI_FILE_PATH);
	//stPatternData.nCuttingMode = pFileMgr.ReadInteger(dataSection, _T("CuttingMode"), INI_FILE_PATH);
	//stPatternData.dFlagVariableTotalLength = pFileMgr.ReadDouble(dataSection, _T("CuttingTotalWidth"), INI_FILE_PATH);
	//stPatternData.dBuriedRegion = pFileMgr.ReadDouble(dataSection, _T("NochingWidth"), INI_FILE_PATH);
	//stPatternData.dBuriedHeight = pFileMgr.ReadDouble(dataSection, _T("NochingHeight"), INI_FILE_PATH);
	//stPatternData.dTabHeight = pFileMgr.ReadDouble(dataSection, _T("CuttingHeight"), INI_FILE_PATH);
	//stPatternData.dPitchWidth1 = pFileMgr.ReadDouble(dataSection, _T("CuttingTabWidth1"), INI_FILE_PATH);
	//stPatternData.dPitchWidth2 = pFileMgr.ReadDouble(dataSection, _T("CuttingTabWidth2"), INI_FILE_PATH);
	//stPatternData.dPitchWidth3 = pFileMgr.ReadDouble(dataSection, _T("CuttingTabWidth3"), INI_FILE_PATH);
	//stPatternData.dPitchWidth4 = pFileMgr.ReadDouble(dataSection, _T("CuttingTabWidth4"), INI_FILE_PATH);
	//stPatternData.dPitchWidth5 = pFileMgr.ReadDouble(dataSection, _T("CuttingTabWidth5"), INI_FILE_PATH);
	//stPatternData.dPitchWidth6 = pFileMgr.ReadDouble(dataSection, _T("CuttingTabWidth6"), INI_FILE_PATH);
	//stPatternData.dCuttingCnt1 = pFileMgr.ReadDouble(dataSection, _T("CuttingCount1"), INI_FILE_PATH);
	//stPatternData.dCuttingCnt2 = pFileMgr.ReadDouble(dataSection, _T("CuttingCount2"), INI_FILE_PATH);
	//stPatternData.dCuttingCnt3 = pFileMgr.ReadDouble(dataSection, _T("CuttingCount3"), INI_FILE_PATH);
	//stPatternData.dCuttingCnt4 = pFileMgr.ReadDouble(dataSection, _T("CuttingCount4"), INI_FILE_PATH);
	//stPatternData.dCuttingCnt5 = pFileMgr.ReadDouble(dataSection, _T("CuttingCount5"), INI_FILE_PATH);
	//stPatternData.dCuttingCnt6 = pFileMgr.ReadDouble(dataSection, _T("CuttingCount6"), INI_FILE_PATH);
	//stPatternData.dTabAngle = pFileMgr.ReadDouble(dataSection, _T("CuttingAngle"), INI_FILE_PATH);
	//stPatternData.dNonflagEndWidth = pFileMgr.ReadDouble(dataSection, _T("NochingAngle"), INI_FILE_PATH);
	//stPatternData.dNochingOutPosLeng = pFileMgr.ReadDouble(dataSection, _T("NochingOutPosWidth"), INI_FILE_PATH);
}

BOOL CDlgPatternEdit_S::OnInitDialog()
{
	CUserDialogEx::OnInitDialog();

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    if (screenWidth < 1500)
    {
        // 70% 비율
        double scale = 0.75;

        // 다이얼로그 크기 조정
        CRect dlgRect;
        GetWindowRect(&dlgRect);
        int newWidth = static_cast<int>(dlgRect.Width() * scale);
        int newHeight = static_cast<int>(dlgRect.Height() * scale);
        MoveWindow(dlgRect.left, dlgRect.top, newWidth, newHeight);

        // 내부 컨트롤 크기 조정
        CWnd* pWnd = GetWindow(GW_CHILD);
        while (pWnd)
        {
            CRect rect;
            pWnd->GetWindowRect(&rect);
            ScreenToClient(&rect); // 다이얼로그 좌표로 변환

            int newCtrlWidth = static_cast<int>(rect.Width() * scale);
            int newCtrlHeight = static_cast<int>(rect.Height() * scale);
            int newCtrlX = static_cast<int>(rect.left * scale);
            int newCtrlY = static_cast<int>(rect.top * scale);

            pWnd->MoveWindow(newCtrlX, newCtrlY, newCtrlWidth, newCtrlHeight);

            pWnd = pWnd->GetNextWindow();
        }
    }

	LONG lStyle = GetWindowLong(this->m_hWnd, GWL_STYLE);
    lStyle &= ~(WS_HSCROLL | WS_VSCROLL); // 비트 제거
    SetWindowLong(this->m_hWnd, GWL_STYLE, lStyle);
    SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

	CString patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);
	CString optionsPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);

	_iniUtil.LoadSDIPatternIni(_T("HEAD1"), patternPath, m_stSDIPatternHEAD1);
	_iniUtil.LoadSDIPatternIni(_T("HEAD2"), patternPath, m_stSDIPatternHEAD2);

	if(m_stSDIPatternHEAD2.bFlip)
		m_cbFlipHEAD2.SetCurSel(1);
	else
		m_cbFlipHEAD2.SetCurSel(0);

	if(m_stSDIPatternHEAD1.bFlip)
		m_cbFlipHEAD1.SetCurSel(1);
	else
		m_cbFlipHEAD1.SetCurSel(0);

	CString strTemp;
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingTabWidth1);
	SetDlgItemText(IDC_CTTEXT_HEAD1_START_CUTTINGWIDTH, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingTabWidth6);
	SetDlgItemText(IDC_CTTEXT_HEAD1_END_CUTTINGWIDTH, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingTabWidth1);
	SetDlgItemText(IDC_CTTEXT_HEAD2_START_CUTTINGWIDTH, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingTabWidth6);
	SetDlgItemText(IDC_CTTEXT_HEAD2_END_CUTTINGWIDTH, strTemp);

	UpdateData(FALSE);

	
	if(m_stSDIPatternHEAD1.nCuttingMode == 0)
	{
		((CButton*)GetDlgItem(IDC_RADIO_OUT_TO_IN))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_TO_OUT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_AND_OUT))->SetCheck(FALSE);
	}
	else if(m_stSDIPatternHEAD1.nCuttingMode == 1)

	{
		((CButton*)GetDlgItem(IDC_RADIO_OUT_TO_IN))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_TO_OUT))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_AND_OUT))->SetCheck(FALSE);
	}
	else if(m_stSDIPatternHEAD1.nCuttingMode == 2)
	{
		((CButton*)GetDlgItem(IDC_RADIO_OUT_TO_IN))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_TO_OUT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_AND_OUT))->SetCheck(TRUE);
	}

	if(m_stSDIPatternHEAD2.nCuttingMode == 0)
	{
		((CButton*)GetDlgItem(IDC_RADIO_OUT_TO_IN2))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_TO_OUT2))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_AND_OUT2))->SetCheck(FALSE);
	}
	else if(m_stSDIPatternHEAD2.nCuttingMode == 1)
	{
		((CButton*)GetDlgItem(IDC_RADIO_OUT_TO_IN2))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_TO_OUT2))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_AND_OUT2))->SetCheck(FALSE);
	}
	else if(m_stSDIPatternHEAD2.nCuttingMode == 2)
	{
		((CButton*)GetDlgItem(IDC_RADIO_OUT_TO_IN2))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_TO_OUT2))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_AND_OUT2))->SetCheck(TRUE);
	}

	IniUtil _iniUtil;
	m_strHEAD1Name = _T("");
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("HEAD1NAME"), sitePath, m_strHEAD1Name);

	if(m_strHEAD1Name == "Anode")
	{
		CCttextctrl* cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_TABWIDTH1));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_TABWIDTH2));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_TABWIDTH3));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_TABWIDTH4));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_TABWIDTH5));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_TABWIDTH6));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_TABWIDTH1));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_TABWIDTH2));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_TABWIDTH3));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_TABWIDTH4));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_TABWIDTH5));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_TABWIDTH6));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));



		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_CUTTING_HEIGHT3));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_CUTTING_HEIGHT3));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));


		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_CUTTING_HEIGHT));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_CUTTING_HEIGHT));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));


		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_CUTTING_HEIGHT2));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_CUTTING_HEIGHT2));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_NOTCHING_ANGLE));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_NOTCHING_ANGLE));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));


		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_NOCHINGWIDTH));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_NOCHINGWIDTH));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));


		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_NOCHING_OFFSET));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_NOCHING_OFFSET));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));


		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_CUTTING_ANGLE));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_CUTTING_ANGLE));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));


		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_NOCHING_OUTPOS));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_NOCHING_OUTPOS));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));


		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_START_CUTTINGWIDTH));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_START_CUTTINGWIDTH));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));


		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_END_CUTTINGWIDTH));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_END_CUTTINGWIDTH));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_TOTALWIDTH));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_TOTALWIDTH));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));




		//
		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_CUTTING_COUNT1));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));
		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_CUTTING_COUNT2));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));
		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_CUTTING_COUNT3));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));
		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_CUTTING_COUNT4));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));
		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_CUTTING_COUNT5));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));
		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_CUTTING_COUNT6));
		cttext0->SetBackColor(RGB(255,160,122)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));

		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_CUTTING_COUNT1));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));
		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_CUTTING_COUNT2));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));
		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_CUTTING_COUNT3));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));
		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_CUTTING_COUNT4));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));
		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_CUTTING_COUNT5));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));
		cttext0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_CUTTING_COUNT6));
		cttext0->SetBackColor(RGB(220,220,220)); 
		cttext0->SetForeColor(RGB(  0,  0,  0));
	
		
	} else
	{
	
	}

	//LoadValue();

	return TRUE;
}

void CDlgPatternEdit_S::LoadValue()
{
	/*CString patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);
	CString optionsPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);

	_iniUtil.LoadSDIPatternIni(_T("HEAD1"), patternPath, m_stSDIPatternHEAD1);
	_iniUtil.LoadSDIPatternIni(_T("HEAD2"), patternPath, m_stSDIPatternHEAD2);*/

	CString strTemp;

	if(m_stSDIPatternHEAD2.bFlip)
		m_cbFlipHEAD2.SetCurSel(1);
	else
		m_cbFlipHEAD2.SetCurSel(0);

	if(m_stSDIPatternHEAD1.bFlip)
		m_cbFlipHEAD1.SetCurSel(1);
	else
		m_cbFlipHEAD1.SetCurSel(0);


	if(m_stSDIPatternHEAD1.nCuttingMode == 0)
	{
		((CButton*)GetDlgItem(IDC_RADIO_OUT_TO_IN))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_TO_OUT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_AND_OUT))->SetCheck(FALSE);
	}
	else if(m_stSDIPatternHEAD1.nCuttingMode == 1)

	{
		((CButton*)GetDlgItem(IDC_RADIO_OUT_TO_IN))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_TO_OUT))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_AND_OUT))->SetCheck(FALSE);
	}
	else if(m_stSDIPatternHEAD1.nCuttingMode == 2)
	{
		((CButton*)GetDlgItem(IDC_RADIO_OUT_TO_IN))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_TO_OUT))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_AND_OUT))->SetCheck(TRUE);
	}

	if(m_stSDIPatternHEAD2.nCuttingMode == 0)
	{
		((CButton*)GetDlgItem(IDC_RADIO_OUT_TO_IN2))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_TO_OUT2))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_AND_OUT2))->SetCheck(FALSE);
	}
	else if(m_stSDIPatternHEAD2.nCuttingMode == 1)
	{
		((CButton*)GetDlgItem(IDC_RADIO_OUT_TO_IN2))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_TO_OUT2))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_AND_OUT2))->SetCheck(FALSE);
	}
	else if(m_stSDIPatternHEAD2.nCuttingMode == 2)
	{
		((CButton*)GetDlgItem(IDC_RADIO_OUT_TO_IN2))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_TO_OUT2))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_IN_AND_OUT2))->SetCheck(TRUE);
	}
	

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingTotalWidth);
	SetDlgItemText(IDC_CTTEXT_HEAD1_TOTALWIDTH, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingTotalWidth);
	SetDlgItemText(IDC_CTTEXT_HEAD2_TOTALWIDTH, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dNochingWidth);
	SetDlgItemText(IDC_CTTEXT_HEAD1_NOCHINGWIDTH, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dNochingWidth);
	SetDlgItemText(IDC_CTTEXT_HEAD2_NOCHINGWIDTH, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dNochingHeight);
	SetDlgItemText(IDC_CTTEXT_HEAD1_NOCHING_OFFSET, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dNochingHeight);
	SetDlgItemText(IDC_CTTEXT_HEAD2_NOCHING_OFFSET, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingHeight);
	SetDlgItemText(IDC_CTTEXT_HEAD1_CUTTING_HEIGHT, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingHeight);
	SetDlgItemText(IDC_CTTEXT_HEAD2_CUTTING_HEIGHT, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingTabWidth1);
	SetDlgItemText(IDC_CTTEXT_HEAD1_TABWIDTH1, strTemp);
	SetDlgItemText(IDC_CTTEXT_HEAD1_START_CUTTINGWIDTH, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingTabWidth2);
	SetDlgItemText(IDC_CTTEXT_HEAD1_TABWIDTH2, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingTabWidth3);
	SetDlgItemText(IDC_CTTEXT_HEAD1_TABWIDTH3, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingTabWidth4);
	SetDlgItemText(IDC_CTTEXT_HEAD1_TABWIDTH4, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingTabWidth5);
	SetDlgItemText(IDC_CTTEXT_HEAD1_TABWIDTH5, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingTabWidth1);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingTabWidth6);
	SetDlgItemText(IDC_CTTEXT_HEAD1_TABWIDTH6, strTemp);
	SetDlgItemText(IDC_CTTEXT_HEAD1_START_CUTTINGWIDTH, strTemp);
	SetDlgItemText(IDC_CTTEXT_HEAD1_END_CUTTINGWIDTH, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingTabWidth1);
	SetDlgItemText(IDC_CTTEXT_HEAD2_TABWIDTH1, strTemp);
	SetDlgItemText(IDC_CTTEXT_HEAD2_START_CUTTINGWIDTH, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingTabWidth2);
	SetDlgItemText(IDC_CTTEXT_HEAD2_TABWIDTH2, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingTabWidth3);
	SetDlgItemText(IDC_CTTEXT_HEAD2_TABWIDTH3, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingTabWidth4);
	SetDlgItemText(IDC_CTTEXT_HEAD2_TABWIDTH4, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingTabWidth5);
	SetDlgItemText(IDC_CTTEXT_HEAD2_TABWIDTH5, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingTabWidth6);
	SetDlgItemText(IDC_CTTEXT_HEAD2_TABWIDTH6, strTemp);
	SetDlgItemText(IDC_CTTEXT_HEAD2_END_CUTTINGWIDTH, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingCount1);
	SetDlgItemText(IDC_CTTEXT_HEAD1_CUTTING_COUNT1, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingCount2);
	SetDlgItemText(IDC_CTTEXT_HEAD1_CUTTING_COUNT2, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingCount3);
	SetDlgItemText(IDC_CTTEXT_HEAD1_CUTTING_COUNT3, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingCount4);
	SetDlgItemText(IDC_CTTEXT_HEAD1_CUTTING_COUNT4, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingCount5);
	SetDlgItemText(IDC_CTTEXT_HEAD1_CUTTING_COUNT5, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingCount6);
	SetDlgItemText(IDC_CTTEXT_HEAD1_CUTTING_COUNT6, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingCount1);
	SetDlgItemText(IDC_CTTEXT_HEAD2_CUTTING_COUNT1, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingCount2);
	SetDlgItemText(IDC_CTTEXT_HEAD2_CUTTING_COUNT2, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingCount3);
	SetDlgItemText(IDC_CTTEXT_HEAD2_CUTTING_COUNT3, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingCount4);
	SetDlgItemText(IDC_CTTEXT_HEAD2_CUTTING_COUNT4, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingCount5);
	SetDlgItemText(IDC_CTTEXT_HEAD2_CUTTING_COUNT5, strTemp);
	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingCount6);
	SetDlgItemText(IDC_CTTEXT_HEAD2_CUTTING_COUNT6, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dCuttingAngle);
	SetDlgItemText(IDC_CTTEXT_HEAD1_CUTTING_ANGLE, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dCuttingAngle);
	SetDlgItemText(IDC_CTTEXT_HEAD2_CUTTING_ANGLE, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dNochingAngle);
	SetDlgItemText(IDC_CTTEXT_HEAD1_NOTCHING_ANGLE, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dNochingAngle);
	SetDlgItemText(IDC_CTTEXT_HEAD2_NOTCHING_ANGLE, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD1.dNochingOutPosWidth);
	SetDlgItemText(IDC_CTTEXT_HEAD1_NOCHING_OUTPOS, strTemp);

	strTemp.Format(_T("%.1f"), m_stSDIPatternHEAD2.dNochingOutPosWidth);
	SetDlgItemText(IDC_CTTEXT_HEAD2_NOCHING_OUTPOS, strTemp);

	UpdateData(FALSE);
}
BEGIN_EVENTSINK_MAP(CDlgPatternEdit_S, CUserDialogEx)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_TABWIDTH1, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1Tabwidth1, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_TABWIDTH2, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1Tabwidth2, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_TABWIDTH3, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1Tabwidth3, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_TABWIDTH4, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1Tabwidth4, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_TABWIDTH5, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1Tabwidth5, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_TABWIDTH6, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1Tabwidth6, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_TABWIDTH1, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2Tabwidth1, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_TABWIDTH2, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2Tabwidth2, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_TABWIDTH3, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2Tabwidth3, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_TABWIDTH4, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2Tabwidth4, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_TABWIDTH5, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2Tabwidth5, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_TABWIDTH6, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2Tabwidth6, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_CUTTING_HEIGHT, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1CuttingHeight, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_CUTTING_HEIGHT, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2CuttingHeight, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_NOTCHING_ANGLE, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1NotchingAngle, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_NOTCHING_ANGLE, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2NotchingAngle, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_NOCHINGWIDTH, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1Nochingwidth, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_NOCHINGWIDTH, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2Nochingwidth, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_NOCHING_OFFSET, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1NochingOffset, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_NOCHING_OFFSET, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2NochingOffset, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_CUTTING_ANGLE, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1CuttingAngle, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_CUTTING_ANGLE, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2CuttingAngle, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_NOCHING_OUTPOS, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1NochingOutpos, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_NOCHING_OUTPOS, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2NochingOutpos, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_CUTTING_COUNT1, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1CuttingCount1, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_CUTTING_COUNT2, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1CuttingCount2, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_CUTTING_COUNT3, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1CuttingCount3, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_CUTTING_COUNT4, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1CuttingCount4, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_CUTTING_COUNT5, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1CuttingCount5, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_CUTTING_COUNT6, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1CuttingCount6, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_CUTTING_COUNT1, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2CuttingCount1, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_CUTTING_COUNT2, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2CuttingCount2, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_CUTTING_COUNT3, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2CuttingCount3, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_CUTTING_COUNT4, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2CuttingCount4, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_CUTTING_COUNT5, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2CuttingCount5, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_CUTTING_COUNT6, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2CuttingCount6, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD1_TOTALWIDTH, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead1Totalwidth, VTS_NONE)
	ON_EVENT(CDlgPatternEdit_S, IDC_CTTEXT_HEAD2_TOTALWIDTH, DISPID_CLICK, CDlgPatternEdit_S::ClickCttextHead2Totalwidth, VTS_NONE)
END_EVENTSINK_MAP()


void CDlgPatternEdit_S::ClickCttextHead1Tabwidth1()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,99.0, m_stSDIPatternHEAD1.dCuttingTabWidth1);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Cutting Width 1 %lf -> %lf"),m_stSDIPatternHEAD1.dCuttingTabWidth1 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dCuttingTabWidth1 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth1 * m_stSDIPatternHEAD1.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth2 * m_stSDIPatternHEAD1.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth3 * m_stSDIPatternHEAD1.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth4 * m_stSDIPatternHEAD1.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth5 * m_stSDIPatternHEAD1.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth6 * m_stSDIPatternHEAD1.dCuttingCount6;
		m_stSDIPatternHEAD1.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1Tabwidth2()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,99.0, m_stSDIPatternHEAD1.dCuttingTabWidth2);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Cutting Width 2 %lf -> %lf"),m_stSDIPatternHEAD1.dCuttingTabWidth2 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dCuttingTabWidth2 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth1 * m_stSDIPatternHEAD1.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth2 * m_stSDIPatternHEAD1.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth3 * m_stSDIPatternHEAD1.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth4 * m_stSDIPatternHEAD1.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth5 * m_stSDIPatternHEAD1.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth6 * m_stSDIPatternHEAD1.dCuttingCount6;
		m_stSDIPatternHEAD1.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1Tabwidth3()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,99.0, m_stSDIPatternHEAD1.dCuttingTabWidth3);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Cutting Width 3 %lf -> %lf"),m_stSDIPatternHEAD1.dCuttingTabWidth3 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dCuttingTabWidth3 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth1 * m_stSDIPatternHEAD1.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth2 * m_stSDIPatternHEAD1.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth3 * m_stSDIPatternHEAD1.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth4 * m_stSDIPatternHEAD1.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth5 * m_stSDIPatternHEAD1.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth6 * m_stSDIPatternHEAD1.dCuttingCount6;
		m_stSDIPatternHEAD1.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1Tabwidth4()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,99.0, m_stSDIPatternHEAD1.dCuttingTabWidth4);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Cutting Width 4 %lf -> %lf"),m_stSDIPatternHEAD1.dCuttingTabWidth4 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dCuttingTabWidth4 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth1 * m_stSDIPatternHEAD1.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth2 * m_stSDIPatternHEAD1.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth3 * m_stSDIPatternHEAD1.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth4 * m_stSDIPatternHEAD1.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth5 * m_stSDIPatternHEAD1.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth6 * m_stSDIPatternHEAD1.dCuttingCount6;
		m_stSDIPatternHEAD1.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1Tabwidth5()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,99.0, m_stSDIPatternHEAD1.dCuttingTabWidth5);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Cutting Width 5 %lf -> %lf"),m_stSDIPatternHEAD1.dCuttingTabWidth5 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dCuttingTabWidth5 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth1 * m_stSDIPatternHEAD1.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth2 * m_stSDIPatternHEAD1.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth3 * m_stSDIPatternHEAD1.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth4 * m_stSDIPatternHEAD1.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth5 * m_stSDIPatternHEAD1.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth6 * m_stSDIPatternHEAD1.dCuttingCount6;
		m_stSDIPatternHEAD1.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1Tabwidth6()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,99.0, m_stSDIPatternHEAD1.dCuttingTabWidth6);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Cutting Width 6 %lf -> %lf"),m_stSDIPatternHEAD1.dCuttingTabWidth6 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dCuttingTabWidth6 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth1 * m_stSDIPatternHEAD1.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth2 * m_stSDIPatternHEAD1.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth3 * m_stSDIPatternHEAD1.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth4 * m_stSDIPatternHEAD1.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth5 * m_stSDIPatternHEAD1.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth6 * m_stSDIPatternHEAD1.dCuttingCount6;
		m_stSDIPatternHEAD1.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2Tabwidth1()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,99.0, m_stSDIPatternHEAD2.dCuttingTabWidth1);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Cutting Width 1 %lf -> %lf"),m_stSDIPatternHEAD2.dCuttingTabWidth1 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dCuttingTabWidth1 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth1 * m_stSDIPatternHEAD2.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth2 * m_stSDIPatternHEAD2.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth3 * m_stSDIPatternHEAD2.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth4 * m_stSDIPatternHEAD2.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth5 * m_stSDIPatternHEAD2.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth6 * m_stSDIPatternHEAD2.dCuttingCount6;
		m_stSDIPatternHEAD2.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2Tabwidth2()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,99.0, m_stSDIPatternHEAD2.dCuttingTabWidth2);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Cutting Width 2 %lf -> %lf"),m_stSDIPatternHEAD2.dCuttingTabWidth2 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dCuttingTabWidth2 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth1 * m_stSDIPatternHEAD2.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth2 * m_stSDIPatternHEAD2.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth3 * m_stSDIPatternHEAD2.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth4 * m_stSDIPatternHEAD2.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth5 * m_stSDIPatternHEAD2.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth6 * m_stSDIPatternHEAD2.dCuttingCount6;
		m_stSDIPatternHEAD2.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2Tabwidth3()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,99.0, m_stSDIPatternHEAD2.dCuttingTabWidth3);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Cutting Width 3 %lf -> %lf"),m_stSDIPatternHEAD2.dCuttingTabWidth3 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dCuttingTabWidth3 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth1 * m_stSDIPatternHEAD2.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth2 * m_stSDIPatternHEAD2.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth3 * m_stSDIPatternHEAD2.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth4 * m_stSDIPatternHEAD2.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth5 * m_stSDIPatternHEAD2.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth6 * m_stSDIPatternHEAD2.dCuttingCount6;
		m_stSDIPatternHEAD2.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2Tabwidth4()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,99.0, m_stSDIPatternHEAD2.dCuttingTabWidth4);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Cutting Width 4 %lf -> %lf"),m_stSDIPatternHEAD2.dCuttingTabWidth4 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dCuttingTabWidth4 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth1 * m_stSDIPatternHEAD2.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth2 * m_stSDIPatternHEAD2.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth3 * m_stSDIPatternHEAD2.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth4 * m_stSDIPatternHEAD2.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth5 * m_stSDIPatternHEAD2.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth6 * m_stSDIPatternHEAD2.dCuttingCount6;
		m_stSDIPatternHEAD2.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2Tabwidth5()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,99.0, m_stSDIPatternHEAD2.dCuttingTabWidth5);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Cutting Width 5 %lf -> %lf"),m_stSDIPatternHEAD2.dCuttingTabWidth5 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dCuttingTabWidth5 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth1 * m_stSDIPatternHEAD2.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth2 * m_stSDIPatternHEAD2.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth3 * m_stSDIPatternHEAD2.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth4 * m_stSDIPatternHEAD2.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth5 * m_stSDIPatternHEAD2.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth6 * m_stSDIPatternHEAD2.dCuttingCount6;
		m_stSDIPatternHEAD2.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2Tabwidth6()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,99.0, m_stSDIPatternHEAD2.dCuttingTabWidth6);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Cutting Width 6 %lf -> %lf"),m_stSDIPatternHEAD2.dCuttingTabWidth6 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dCuttingTabWidth6 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth1 * m_stSDIPatternHEAD2.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth2 * m_stSDIPatternHEAD2.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth3 * m_stSDIPatternHEAD2.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth4 * m_stSDIPatternHEAD2.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth5 * m_stSDIPatternHEAD2.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth6 * m_stSDIPatternHEAD2.dCuttingCount6;
		m_stSDIPatternHEAD2.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}

void CDlgPatternEdit_S::ClickCttextHead1CuttingHeight()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,99.0, m_stSDIPatternHEAD1.dCuttingHeight);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Cutting Height %lf -> %lf"),m_stSDIPatternHEAD1.dCuttingHeight ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dCuttingHeight = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2CuttingHeight()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,99.0, m_stSDIPatternHEAD2.dCuttingHeight);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Cutting Height %lf -> %lf"),m_stSDIPatternHEAD2.dCuttingHeight ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dCuttingHeight = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1NotchingAngle()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(-99.0,99.0, m_stSDIPatternHEAD1.dNochingAngle);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Notching Angle %lf -> %lf"),m_stSDIPatternHEAD1.dNochingAngle ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dNochingAngle = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2NotchingAngle()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(-99.0,99.0, m_stSDIPatternHEAD2.dNochingAngle);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Notching Angle %lf -> %lf"),m_stSDIPatternHEAD2.dNochingAngle ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dNochingAngle = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1Nochingwidth()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,9999.0, m_stSDIPatternHEAD1.dNochingWidth);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Notching Width %lf -> %lf"),m_stSDIPatternHEAD1.dNochingWidth ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dNochingWidth = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2Nochingwidth()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,9999.0, m_stSDIPatternHEAD2.dNochingWidth);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Notching Width %lf -> %lf"),m_stSDIPatternHEAD2.dNochingWidth ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dNochingWidth = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1NochingOffset()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(-99.0,99.0, m_stSDIPatternHEAD1.dNochingHeight);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Notching Height %lf -> %lf"),m_stSDIPatternHEAD1.dNochingHeight ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dNochingHeight = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2NochingOffset()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(-99.0,99.0, m_stSDIPatternHEAD2.dNochingHeight);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Notching Height %lf -> %lf"),m_stSDIPatternHEAD2.dNochingHeight ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dNochingHeight = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1CuttingAngle()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(-99.0,99.0, m_stSDIPatternHEAD1.dCuttingAngle);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Notching Angle %lf -> %lf"),m_stSDIPatternHEAD1.dCuttingAngle ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dCuttingAngle = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2CuttingAngle()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(-99.0,99.0, m_stSDIPatternHEAD2.dCuttingAngle);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Notching Angle %lf -> %lf"),m_stSDIPatternHEAD2.dCuttingAngle ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dCuttingAngle = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1NochingOutpos()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,999.0, m_stSDIPatternHEAD1.dNochingOutPosWidth);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Notching Out Pos Width %lf -> %lf"),m_stSDIPatternHEAD1.dNochingOutPosWidth ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dNochingOutPosWidth = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2NochingOutpos()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,999.0, m_stSDIPatternHEAD2.dNochingOutPosWidth);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Notching Out Pos Width %lf -> %lf"),m_stSDIPatternHEAD2.dNochingOutPosWidth ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dNochingOutPosWidth = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1CuttingCount1()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,999.0, m_stSDIPatternHEAD1.dCuttingCount1);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Cutting Count 1 %lf -> %lf"),m_stSDIPatternHEAD1.dCuttingCount1 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dCuttingCount1 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth1 * m_stSDIPatternHEAD1.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth2 * m_stSDIPatternHEAD1.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth3 * m_stSDIPatternHEAD1.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth4 * m_stSDIPatternHEAD1.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth5 * m_stSDIPatternHEAD1.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth6 * m_stSDIPatternHEAD1.dCuttingCount6;
		m_stSDIPatternHEAD1.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1CuttingCount2()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,999.0, m_stSDIPatternHEAD1.dCuttingCount2);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Cutting Count 2 %lf -> %lf"),m_stSDIPatternHEAD1.dCuttingCount2 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dCuttingCount2 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth1 * m_stSDIPatternHEAD1.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth2 * m_stSDIPatternHEAD1.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth3 * m_stSDIPatternHEAD1.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth4 * m_stSDIPatternHEAD1.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth5 * m_stSDIPatternHEAD1.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth6 * m_stSDIPatternHEAD1.dCuttingCount6;
		m_stSDIPatternHEAD1.dCuttingTotalWidth = dTotalWidth;


		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1CuttingCount3()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,999.0, m_stSDIPatternHEAD1.dCuttingCount3);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Cutting Count 3 %lf -> %lf"),m_stSDIPatternHEAD1.dCuttingCount3 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dCuttingCount3 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth1 * m_stSDIPatternHEAD1.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth2 * m_stSDIPatternHEAD1.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth3 * m_stSDIPatternHEAD1.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth4 * m_stSDIPatternHEAD1.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth5 * m_stSDIPatternHEAD1.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth6 * m_stSDIPatternHEAD1.dCuttingCount6;
		m_stSDIPatternHEAD1.dCuttingTotalWidth = dTotalWidth;


		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1CuttingCount4()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,999.0, m_stSDIPatternHEAD1.dCuttingCount4);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Cutting Count 4 %lf -> %lf"),m_stSDIPatternHEAD1.dCuttingCount4 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dCuttingCount4 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth1 * m_stSDIPatternHEAD1.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth2 * m_stSDIPatternHEAD1.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth3 * m_stSDIPatternHEAD1.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth4 * m_stSDIPatternHEAD1.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth5 * m_stSDIPatternHEAD1.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth6 * m_stSDIPatternHEAD1.dCuttingCount6;
		m_stSDIPatternHEAD1.dCuttingTotalWidth = dTotalWidth;


		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1CuttingCount5()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,999.0, m_stSDIPatternHEAD1.dCuttingCount5);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Cutting Count 5 %lf -> %lf"),m_stSDIPatternHEAD1.dCuttingCount5 ,numberdlg.GetResultDouble()));
		
		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth1 * m_stSDIPatternHEAD1.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth2 * m_stSDIPatternHEAD1.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth3 * m_stSDIPatternHEAD1.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth4 * m_stSDIPatternHEAD1.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth5 * m_stSDIPatternHEAD1.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth6 * m_stSDIPatternHEAD1.dCuttingCount6;
		m_stSDIPatternHEAD1.dCuttingTotalWidth = dTotalWidth;
m_stSDIPatternHEAD1.dCuttingCount5 = numberdlg.GetResultDouble();

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1CuttingCount6()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,999.0, m_stSDIPatternHEAD1.dCuttingCount6);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Cutting Count 6 %lf -> %lf"),m_stSDIPatternHEAD1.dCuttingCount6 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dCuttingCount6 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth1 * m_stSDIPatternHEAD1.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth2 * m_stSDIPatternHEAD1.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth3 * m_stSDIPatternHEAD1.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth4 * m_stSDIPatternHEAD1.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth5 * m_stSDIPatternHEAD1.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD1.dCuttingTabWidth6 * m_stSDIPatternHEAD1.dCuttingCount6;
		m_stSDIPatternHEAD1.dCuttingTotalWidth = dTotalWidth;


		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2CuttingCount1()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,999.0, m_stSDIPatternHEAD2.dCuttingCount1);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Cutting Count 1 %lf -> %lf"),m_stSDIPatternHEAD2.dCuttingCount1 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dCuttingCount1 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth1 * m_stSDIPatternHEAD2.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth2 * m_stSDIPatternHEAD2.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth3 * m_stSDIPatternHEAD2.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth4 * m_stSDIPatternHEAD2.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth5 * m_stSDIPatternHEAD2.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth6 * m_stSDIPatternHEAD2.dCuttingCount6;
		m_stSDIPatternHEAD2.dCuttingTotalWidth = dTotalWidth;


		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2CuttingCount2()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,999.0, m_stSDIPatternHEAD2.dCuttingCount2);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Cutting Count 2 %lf -> %lf"),m_stSDIPatternHEAD2.dCuttingCount2 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dCuttingCount2 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth1 * m_stSDIPatternHEAD2.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth2 * m_stSDIPatternHEAD2.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth3 * m_stSDIPatternHEAD2.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth4 * m_stSDIPatternHEAD2.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth5 * m_stSDIPatternHEAD2.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth6 * m_stSDIPatternHEAD2.dCuttingCount6;
		m_stSDIPatternHEAD2.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2CuttingCount3()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,999.0, m_stSDIPatternHEAD2.dCuttingCount3);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Cutting Count 3 %lf -> %lf"),m_stSDIPatternHEAD2.dCuttingCount3 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dCuttingCount3 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth1 * m_stSDIPatternHEAD2.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth2 * m_stSDIPatternHEAD2.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth3 * m_stSDIPatternHEAD2.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth4 * m_stSDIPatternHEAD2.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth5 * m_stSDIPatternHEAD2.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth6 * m_stSDIPatternHEAD2.dCuttingCount6;
		m_stSDIPatternHEAD2.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2CuttingCount4()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,999.0, m_stSDIPatternHEAD2.dCuttingCount4);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Cutting Count 4 %lf -> %lf"),m_stSDIPatternHEAD2.dCuttingCount4 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dCuttingCount4 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth1 * m_stSDIPatternHEAD2.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth2 * m_stSDIPatternHEAD2.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth3 * m_stSDIPatternHEAD2.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth4 * m_stSDIPatternHEAD2.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth5 * m_stSDIPatternHEAD2.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth6 * m_stSDIPatternHEAD2.dCuttingCount6;
		m_stSDIPatternHEAD2.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2CuttingCount5()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,999.0, m_stSDIPatternHEAD2.dCuttingCount5);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Cutting Count 5 %lf -> %lf"),m_stSDIPatternHEAD2.dCuttingCount5 ,numberdlg.GetResultDouble()));
		
		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth1 * m_stSDIPatternHEAD2.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth2 * m_stSDIPatternHEAD2.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth3 * m_stSDIPatternHEAD2.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth4 * m_stSDIPatternHEAD2.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth5 * m_stSDIPatternHEAD2.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth6 * m_stSDIPatternHEAD2.dCuttingCount6;
		m_stSDIPatternHEAD2.dCuttingTotalWidth = dTotalWidth;m_stSDIPatternHEAD2.dCuttingCount5 = numberdlg.GetResultDouble();

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2CuttingCount6()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,999.0, m_stSDIPatternHEAD2.dCuttingCount6);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Cutting Count 6 %lf -> %lf"),m_stSDIPatternHEAD2.dCuttingCount6 ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dCuttingCount6 = numberdlg.GetResultDouble();

		double dTotalWidth = 0.0;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth1 * m_stSDIPatternHEAD2.dCuttingCount1;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth2 * m_stSDIPatternHEAD2.dCuttingCount2;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth3 * m_stSDIPatternHEAD2.dCuttingCount3;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth4 * m_stSDIPatternHEAD2.dCuttingCount4;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth5 * m_stSDIPatternHEAD2.dCuttingCount5;
		dTotalWidth += m_stSDIPatternHEAD2.dCuttingTabWidth6 * m_stSDIPatternHEAD2.dCuttingCount6;
		m_stSDIPatternHEAD2.dCuttingTotalWidth = dTotalWidth;

		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead1Totalwidth()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,9999.0, m_stSDIPatternHEAD1.dCuttingTotalWidth);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD1 Total Width %lf -> %lf"),m_stSDIPatternHEAD1.dCuttingTotalWidth ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD1.dCuttingTotalWidth = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::ClickCttextHead2Totalwidth()
{
	CNumberKeyPad numberdlg;
	numberdlg.SetRange(0.0,9999.0, m_stSDIPatternHEAD2.dCuttingTotalWidth);

	if(numberdlg.DoModal()==IDOK)
	{		
		CWriteLog* log = NULL;
		log->WriteString(CWriteLog::MakeFormatString(_T("SDI HEAD2 Total Width %lf -> %lf"),m_stSDIPatternHEAD2.dCuttingTotalWidth ,numberdlg.GetResultDouble()));
		m_stSDIPatternHEAD2.dCuttingTotalWidth = numberdlg.GetResultDouble();
		UpdateData(FALSE);
	}
}


void CDlgPatternEdit_S::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CUserDialogEx::OnCancel();
}



