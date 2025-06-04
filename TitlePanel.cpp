// TitlePanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "TitlePanel.h"

#include "./Include/EXTERN/cttextctrl.h"
#include "./RUN_MODULE/RunningDefine.h"
//#include "../DIGITAL/Digital.h"
#include "./NX_LOGIN/Login.h"
// #include "./NX_LOGIN/GuiLogin.h"
#include "./RECIPE_MODULE/RecipeManager.h"
#include "FieldParameter.h"

// CTitlePanel
IMPLEMENT_DYNCREATE(CTitlePanel, CProjectBaseView)

CTitlePanel::CTitlePanel()
	: CProjectBaseView(CTitlePanel::IDD)
{

}

CTitlePanel::~CTitlePanel()
{
}

void CTitlePanel::DoDataExchange(CDataExchange* pDX)
{
	CProjectBaseView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTitlePanel, CProjectBaseView)
	ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CTitlePanel 진단입니다.

#ifdef _DEBUG
void CTitlePanel::AssertValid() const
{
	CProjectBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CTitlePanel::Dump(CDumpContext& dc) const
{
	CProjectBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTitlePanel 메시지 처리기입니다.

void CTitlePanel::ResizeControls(float scale)
{
    if (m_originalRects.empty())
        return;

    int index = 0;
    CWnd* pWnd = GetWindow(GW_CHILD); // 첫 번째 자식 컨트롤
    while (pWnd && index < m_originalRects.size())
    {
        CRect newRect = m_originalRects[index];

        // 개별적으로 크기 조정 (가로: scaleX, 세로: scaleY)
        newRect.left   = static_cast<int>(newRect.left * scale);
        newRect.top    = static_cast<int>(newRect.top);
        newRect.right  = static_cast<int>(newRect.right * scale);
        newRect.bottom = static_cast<int>(newRect.bottom);

        pWnd->MoveWindow(&newRect);

        pWnd = pWnd->GetNextWindow(GW_HWNDNEXT); // 다음 컨트롤
        index++;
    }

    // 다이얼로그 자체 크기도 개별적으로 조정
    CRect newDlgRect = m_originalDlgRect;
    newDlgRect.right  = static_cast<int>(newDlgRect.right * scale);
    newDlgRect.bottom = static_cast<int>(newDlgRect.bottom);
    SetWindowPos(NULL, 0, 0, newDlgRect.Width(), newDlgRect.Height(), SWP_NOMOVE | SWP_NOZORDER);
}



void CTitlePanel::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CProjectBaseView::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	Init();

	/*CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_originalDlgRect = rect;


	CWnd* pWnd = GetWindow(GW_CHILD);
	while (pWnd)
	{
		CRect rect;
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);
		m_originalRects.push_back(rect);

		pWnd = pWnd->GetNextWindow(GW_HWNDNEXT);
	}
	ResizeControls(0.7f);*/
}
void CTitlePanel::UpdateCommStatus(BOOL bMES, BOOL bLASER1, BOOL bLASER2)
{
	CCttextctrl* pStatusLaser0 = (CCttextctrl*)GetDlgItem(IDC_CT_TITLE_MES_COMM_STATUS);
	if(bMES == TRUE)
		pStatusLaser0->SetBackColor(clLimeGreen);
	else
		pStatusLaser0->SetBackColor(clDarkGray);

	CCttextctrl* pStatusLaser1 = (CCttextctrl*)GetDlgItem(IDC_CT_TITLE_LASER1_COMM_STATUS);
	if(bLASER1 == TRUE)
		//pStatusLaser1->SetForeColor(clLimeGreen);
			pStatusLaser1->SetBackColor(clLimeGreen);
	else
		pStatusLaser1->SetBackColor(clDarkGray);

	CCttextctrl* pStatusLaser2 = (CCttextctrl*)GetDlgItem(IDC_CT_TITLE_LASER2_COMM_STATUS);
	if(bLASER2 == TRUE)
		pStatusLaser2->SetBackColor(clLimeGreen);
	else
		pStatusLaser2->SetBackColor(clDarkGray);
}


void CTitlePanel::UpdateEncInfo(CString str)
{
	double fieldKX;
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	if(pFieldParameter->GetKX() < 0)
	{
		fieldKX = -pFieldParameter->GetKX();
	} else
	{
		fieldKX = pFieldParameter->GetKX();		
	}

	CDsp *pDsp = CDsp::GetInstance();
	CString encoderValue;
	LONG HEAD1EncoderX,HEAD1EncoderY;
	HEAD1EncoderX=0;HEAD1EncoderY=0;

	pDsp->GetEncodeHEAD1(HEAD1EncoderX,HEAD1EncoderY);
	

	encoderValue.Format("H1_0 %.3f mm", HEAD1EncoderY / fieldKX);
	
	SetDlgItemText(IDC_CT_TITLE_ENC,encoderValue);
}


void CTitlePanel::Display()
{
	UpdateEncInfo("");

	if(!RunMgr) return;
	if(m_TimeCounter.GetDelayTime(ENUM_TIME_COUNTER_MODE_GETTICK) > 1000)
	{
		m_TimeCounter.SetTime(ENUM_TIME_COUNTER_MODE_GETTICK);
		m_bTwinkel =  !m_bTwinkel;
	}
	CString strTitle, strEQCode;

	IniUtil _iniUtil;
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("EQCode"), sitePath, strEQCode);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("LastRecipe"), sitePath, strTitle);

	//1. S/W version
	CCttextctrl*pVersion = (CCttextctrl*)GetDlgItem(IDC_TILTEL_TITILE_VALUE);
	pVersion->SetCaption(m_strSW_Version);

	//2. Recipe
	CCttextctrl*pRecipe = (CCttextctrl*)GetDlgItem(IDC_TILTEL_RECIPE_VALUE);
	pRecipe->SetCaption( strEQCode );

	

	//3. user mode

	if(Login) 
	{
		//m_strUserMode = UserLogin->GetCurrentUserName();
		switch(Login->GetCurrentUserLevel())
		{
		case LOGIN_DEVELOPER:
			m_strUserMode = "DEVELOPER";
			break;
		case LOGIN_SUPERVISOR:
			m_strUserMode = "SUPERVISOR";
			break;
		case LOGIN_MAINTENANCE:
			m_strUserMode = "MAINTENANCE";
			break;
		case LOGIN_OPERATOR:
			m_strUserMode = "OPERATOR";
			break;
		}
		CCttextctrl* pUserMode = (CCttextctrl*)GetDlgItem(IDC_TILTEL_USERMODE_VALUE);
		pUserMode->SetCaption(m_strUserMode);
	}

	//4. Run mode Status
	switch(RunMgr->GetRunMode())
	{
	case INIT:
		m_strRunMode = "INIT";
		break;
	case JAM: 
		m_strRunMode = "JAM";
		break;
	case READY:
		m_strRunMode = "READY";
		break;
	case AUTO:
		m_strRunMode = "AUTO";
		break;
	case STOP:
		m_strRunMode = "STOP";
		break;
	default:
		m_strRunMode = _T("");
		break;
	}

	CCttextctrl* pRunMode = (CCttextctrl*)GetDlgItem(IDC_TILTEL_STATUS_VALUE);
	DWORD dwFontColor = pRunMode->GetBackColor();
	dwFontColor = m_bTwinkel ? clBlack : dwFontColor;

	pRunMode->SetForeColor(dwFontColor);
	pRunMode->SetCaption(m_strRunMode);


	//time display
	m_strTime = m_FileMgr.GetDateTime_HOUR_MIN_SEC();
	CCttextctrl* pTime = (CCttextctrl*)GetDlgItem(IDC_TILTEL_TIME_VALUE);
	pTime->SetCaption(m_strTime);

	CCttextctrl* pRecipeTitle = (CCttextctrl*)GetDlgItem(IDC_CUR_RECIPENAME);
	pRecipeTitle->SetCaption( strTitle );

	//light bar

// 	if(Digital)
// 	{
// 		CCttextctrl* pLightBar_R = (CCttextctrl*)GetDlgItem(IDC_CT_TITLE_LIGHT_BAR_R);
// 		CCttextctrl* pLightBar_Y = (CCttextctrl*)GetDlgItem(IDC_CT_TITLE_LIGHT_BAR_Y);
// 		CCttextctrl* pLightBar_G = (CCttextctrl*)GetDlgItem(IDC_CT_TITLE_LIGHT_BAR_G);
// 		Y_TOWER_LAMP_RED	? pLightBar_R->SetBackColor(clRed	) : pLightBar_R->SetBackColor(clMaroon);
// 		Y_TOWER_LAMP_YELLOW ? pLightBar_Y->SetBackColor(clYellow) : pLightBar_Y->SetBackColor(clOlive );
// 		Y_TOWER_LAMP_GREEN	? pLightBar_G->SetBackColor(clLime	) : pLightBar_G->SetBackColor(clGreen );
// 	}



}

void CTitlePanel::Init()
{
	m_TimeCounter.SetTime(ENUM_TIME_COUNTER_MODE_GETTICK);

	m_dwThreadColor	= clBlack;
	m_bTwinkel		= FALSE;
	m_strRunMode	= TEXT("");
	m_strUserMode	= TEXT("");
	m_strTime		= TEXT("");
//	m_strSW_Version	= theApp.m_strProductVersion;

	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();
	m_strSW_Version	= pApp->m_strProductVersion;

	//
	//m_background.LoadBitmap(IDB_BITMAP_TITLE_BG);
	m_background.LoadBitmap(IDB_BITMAP_TITLE_BG);
}

BOOL CTitlePanel::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if(!m_background.m_hObject) return TRUE;

	CRect rect;
	GetClientRect(&rect);

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dc.SelectObject(&m_background);

	BITMAP bmap;
	m_background.GetBitmap(&bmap);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, bmap.bmWidth, bmap.bmHeight, SRCCOPY);

	dc.SelectObject(pOldBitmap);
	return TRUE;
	//return CProjectBaseView::OnEraseBkgnd(pDC);
}
BEGIN_EVENTSINK_MAP(CTitlePanel, CProjectBaseView)
	ON_EVENT(CTitlePanel, IDC_TILTEL_USERMODE_VALUE, DISPID_CLICK, CTitlePanel::ClickTiltelUsermodeValue, VTS_NONE)
END_EVENTSINK_MAP()


void CTitlePanel::ClickTiltelUsermodeValue()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	/*CGuiLogin LoginDlg;
	if(LoginDlg.DoModal() == IDOK)
	{
		m_pMainFrame->PostMessage(WM_LOGIN_UPDATE);
	}
	else
	{

	}*/
}
