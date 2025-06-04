// InforRecipeConfigPanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "InforRecipeConfigPanel.h"

#include "./RECIPE_MODULE/RecipeManager.h"
#include "./RUN_MODULE/RunningDefine.h"
//
#include "./NX_CONFIRM/Confirm.h"
#include "./NX_KEYPAD/AlphaKeyPad.h"
#include "./NX_KEYPAD/NumberKeyPad.h"
#include "./Include/EXTERN/FileMgr.h"


//
//#include "../SETUP/SetupManager.h"
//#include "../SETUP/SetupDefine.h"
//

// CInforRecipeConfigPanel

IMPLEMENT_DYNCREATE(CInforRecipeConfigPanel, CProjectBaseView)

CInforRecipeConfigPanel::CInforRecipeConfigPanel()
	: CProjectBaseView(CInforRecipeConfigPanel::IDD)
	, m_nRadio_RecipeView(0)
{
	m_pDlgPatternEdit = NULL;
	/*m_pDlgRecipeMotion	= NULL;
	m_pDlgRecipeLaser	= NULL;
	m_pDlgRecipeSocket	= NULL;
	m_pDlgRecipeVision  = NULL;*/
}

CInforRecipeConfigPanel::~CInforRecipeConfigPanel()
{
	if(m_pDlgPatternEdit)
	{
		m_pDlgPatternEdit->DestroyWindow();
		delete m_pDlgPatternEdit;
		m_pDlgPatternEdit = NULL;
	}

	/*if(m_pDlgScannerParameter)
	{
		m_pDlgScannerParameter->DestroyWindow();
		delete m_pDlgScannerParameter;
		m_pDlgScannerParameter = NULL;
	}
*/
	

	/*
	if(m_pDlgRecipeLaser)
	{
		m_pDlgRecipeLaser->DestroyWindow();
		delete m_pDlgRecipeLaser;
		m_pDlgRecipeLaser = NULL;
	}

	if(m_pDlgRecipeSocket)
	{
		m_pDlgRecipeSocket->DestroyWindow();
		delete m_pDlgRecipeSocket;
		m_pDlgRecipeSocket = NULL;
	}

	if(m_pDlgRecipeVision)
	{
		m_pDlgRecipeVision->DestroyWindow();
		delete m_pDlgRecipeVision;
		m_pDlgRecipeVision = NULL;
	}*/

}

void CInforRecipeConfigPanel::DoDataExchange(CDataExchange* pDX)
{
	CProjectBaseView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RECIPE, m_iRecipeList);
	
}

BEGIN_MESSAGE_MAP(CInforRecipeConfigPanel, CProjectBaseView)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_RECIPE_MOTION, IDC_RADIO_RECIPE_VISION,&CInforRecipeConfigPanel::OnBnClickedRadioRecipeView)
	ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_RADIO_RECIPE_MOTION, &CInforRecipeConfigPanel::OnBnClickedRadioRecipeMotion)
	ON_STN_CLICKED(IDC_STATIC_RECIPE_RECT, &CInforRecipeConfigPanel::OnStnClickedStaticRecipeRect)
END_MESSAGE_MAP()


// CInforRecipeConfigPanel 진단입니다.

#ifdef _DEBUG
void CInforRecipeConfigPanel::AssertValid() const
{
	CProjectBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CInforRecipeConfigPanel::Dump(CDumpContext& dc) const
{
	CProjectBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInforRecipeConfigPanel 메시지 처리기입니다.
void CInforRecipeConfigPanel::LoadRecipe()
{
	
	LOGFONT lf;

	this->GetFont()->GetLogFont(&lf);

	lf.lfHeight = 15;
	lf.lfWeight = FW_BOLD;

	wsprintf(lf.lfFaceName, _T("%s"), TEXT("Tahoma"));

	CFont NewFont;

	NewFont.CreateFontIndirect(&lf);

	CWnd* pWnd = this->GetWindow(GW_CHILD);

	while (pWnd)
	{
		pWnd->SetFont(&NewFont);
		pWnd = pWnd->GetNextWindow();
	}

	NewFont.Detach();

	//////////////////////////////////////////////////////////////////////////
	
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	
	_iniUtil.LoadStringValueByKey( _T("Settings"), _T("SiteName"), sitePath, m_patternMode);

	GetDlgItem(IDC_STATIC_RECIPE_RECT)->GetWindowRect(m_rect);
	ScreenToClient(m_rect);
	if(m_patternMode == "SDI")
	{
		m_pDlgPatternEdit_S = new CDlgPatternEdit_S(this);
		m_pDlgPatternEdit_S->Create(IDD_DLG_SDI_PATTERN, this);
		m_pDlgPatternEdit_S->MoveWindow(m_rect, TRUE);
		m_pDlgPatternEdit_S->ShowWindow(SW_SHOW); 

	}
	else if(m_patternMode == "SDI_POUCH")
	{
		m_pDlgPatternEdit_P = new CDlgPouchEdit(this);
		m_pDlgPatternEdit_P->Create(IDD_DLG_POUCH_EDIT, this);
		m_pDlgPatternEdit_P->MoveWindow(m_rect, TRUE);
		m_pDlgPatternEdit_P->ShowWindow(SW_SHOW); 

	}
	else 
	{
		m_pDlgPatternEdit = new CDlgPatternEdit(this);
		m_pDlgPatternEdit->Create(IDD_DLG_PATTERN_EDIT, this);
		m_pDlgPatternEdit->MoveWindow(m_rect, TRUE);
		m_pDlgPatternEdit->ShowWindow(SW_SHOW); 
	}

	Init();
}

void CInforRecipeConfigPanel::OnInitialUpdate()
{
	CProjectBaseView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    SetScrollSizes(MM_TEXT, CSize(0, 0));
    ShowScrollBar(SB_BOTH, FALSE);

	m_background.LoadBitmap(IDB_BITMAP_MAIN_BG);
	LoadRecipe();
	/*
	m_pDlgRecipeLaser = new CInforRecipeLaserDlg(this);

	m_pDlgRecipeLaser->Create(IDD_DLG_RECIPE_LASER, this);

	m_pDlgRecipeLaser->MoveWindow(m_rect, TRUE);


	m_pDlgRecipeSocket = new CInforRecipeSocketDlg(this);

	m_pDlgRecipeSocket->Create(IDD_DLG_RECIPE_SOCKET, this);

	m_pDlgRecipeSocket->MoveWindow(m_rect, TRUE);


	m_pDlgRecipeVision = new CInforRecipeVisionDlg(this);

	m_pDlgRecipeVision->Create(IDD_DLG_RECIPE_VISION, this);

	m_pDlgRecipeVision->MoveWindow(m_rect, TRUE);*/


	//////////////////////////////////////////////////////////////////////////

	Init();
}

void CInforRecipeConfigPanel::UpdateInfo()
{
	OpenRecipeList();
	if(m_patternMode == "SDI")
	{
		m_pDlgPatternEdit_S->LoadValue();
	}
	else if(m_patternMode == "SDI_POUCH") 
	{
		m_pDlgPatternEdit_P->LoadValue();
	}
	//else
	//	m_pDlgPatternEdit->LoadValue();


}



void CInforRecipeConfigPanel::Init()
{
	OpenRecipeList();
}

void CInforRecipeConfigPanel::OpenRecipeList()
{
	int nCnt = m_iRecipeList.GetCount();

	for( int i=0; i<nCnt; i++ )
		m_iRecipeList.DeleteString(0);

	TCHAR* szList = RecipeMgr->RecipePath.GetDirView();
	TCHAR* szContext = NULL;


	TCHAR* token = _tcstok_s(szList,TEXT("?") ,&szContext);
	m_iRecipeList.AddString( token ) ;
	while( token )
	{	
		token = _tcstok_s(NULL,TEXT("?") ,&szContext);
		if( token != NULL )
		{			
			m_iRecipeList.AddString( token ) ;			
		}
	}	
	int nCursePos = m_iRecipeList.FindString( 0, RecipeMgr->RecipePath.GetSelectedModle() );
	m_iRecipeList.SetCurSel( nCursePos );

	RecipeMgr->OpenLogPath();

	//////////////////////////////////////////////////////////////////////////

	//OpenSpread
	//{{


	//}}


	//OpenPosition Select
	//{{
	

	//}}

	//////////////////////////////////////////////////////////////////////////

	//GetDlgItem(IDC_EDIT__RECIPE_SELECTED)->SetWindowTextW( RecipeMgr->RecipePath.GetSelectedModle() );	 
	GetDlgItem(IDC_EDIT__RECIPE_SELECTED)->SetWindowText( RecipeMgr->RecipePath.GetSelectedModle() );	


	IniUtil _iniUtil;
	_iniUtil.SetRecipe( RecipeMgr->RecipePath.GetSelectedModle()); 
	 CString paramPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);

    SingleScannerParameter HEAD1ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD1Parameter();
	SingleScannerParameter HEAD2ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD2Parameter();
	
	_iniUtil.LoadParameterIni( _T("HEAD1"), paramPath, HEAD1ScannerParameter);
	_iniUtil.LoadParameterIni( _T("HEAD2"), paramPath, HEAD2ScannerParameter);



	CDualScannerParameter* dsParameter = CDualScannerParameter::GetInstance();
	dsParameter->SetData(HEAD2ScannerParameter,HEAD1ScannerParameter);

	CString patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
	
	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
	_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);
}

BEGIN_EVENTSINK_MAP(CInforRecipeConfigPanel, CProjectBaseView)
//	ON_EVENT(CInforRecipeConfigPanel, IDC_BUTTON_RECIPE_OPEN, DISPID_CLICK, CInforRecipeConfigPanel::ClickButtonRecipeOpen, VTS_NONE)
	ON_EVENT(CInforRecipeConfigPanel, IDC_BUTTON_RECIPE_SAVE, DISPID_CLICK, CInforRecipeConfigPanel::ClickButtonRecipeSave, VTS_NONE)
	ON_EVENT(CInforRecipeConfigPanel, IDC_BUTTON_RECIPE_CREATE, DISPID_CLICK, CInforRecipeConfigPanel::ClickButtonRecipeCreate, VTS_NONE)
	ON_EVENT(CInforRecipeConfigPanel, IDC_BUTTON__RECIPE_DELETE, DISPID_CLICK, CInforRecipeConfigPanel::ClickButton, VTS_NONE)
	ON_EVENT(CInforRecipeConfigPanel, IDC_BUTTON__RECIPE_CHANGE_NAME, DISPID_CLICK, CInforRecipeConfigPanel::ClickButtonRecipeChangeName, VTS_NONE)
	ON_EVENT(CInforRecipeConfigPanel, IDC_CTPUSH_SETTING_PATH, DISPID_CLICK, CInforRecipeConfigPanel::ClickCtpushSettingPath, VTS_NONE)
	ON_EVENT(CInforRecipeConfigPanel, IDC_BUTTON_RECIPE_OPEN, DISPID_CLICK, CInforRecipeConfigPanel::ClickButtonRecipeOpen, VTS_NONE)
END_EVENTSINK_MAP()


void CInforRecipeConfigPanel::ClickButtonRecipeOpen()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CConfirm Confirm;
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();

	int nIndex = m_iRecipeList.GetCurSel();	

	TCHAR szName[MAX_PATH];
	memset(szName, NULL, _countof(szName));
	CString strTemp = TEXT( "Would you like to Open : ");
	m_iRecipeList.GetText(nIndex, szName );

	strTemp.Append( szName );
	strTemp.Append( TEXT(" ?") );

	Confirm.SetCaption( strTemp, FALSE, CConfirm::E_QUESTION );

	if( Confirm.DoModal() == IDOK )
	{
		IniUtil _iniUtil;
		_iniUtil.SetRecipe(szName);
		RecipeMgr->RecipePath.ChangeModel( szName );
		
		SingleScannerParameter HEAD1ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD1Parameter();
		SingleScannerParameter HEAD2ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD2Parameter();
		CString ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
		_iniUtil.LoadParameterIni( _T("HEAD1"), ParamPath, HEAD1ScannerParameter);
		_iniUtil.LoadParameterIni( _T("HEAD2"), ParamPath, HEAD2ScannerParameter);

		FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
		CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
		_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);

		CString patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);

		if(m_patternMode == "SDI")
		{
			_iniUtil.LoadSDIPatternIni(_T("HEAD1"), patternPath, m_pDlgPatternEdit_S->m_stSDIPatternHEAD1);
			_iniUtil.LoadSDIPatternIni(_T("HEAD2"), patternPath, m_pDlgPatternEdit_S->m_stSDIPatternHEAD2);
			OpenRecipeList();
			m_pDlgPatternEdit_S->LoadValue();

		}
		else if(m_patternMode == "SDI_POUCH")
		{
			_iniUtil.LoadPouchPatternIni(_T("HEAD1"), patternPath, m_pDlgPatternEdit_P->m_Pouch_Parameter_Data);
			OpenRecipeList();
			m_pDlgPatternEdit_P->_iniUtil.SetRecipe(szName);
			m_pDlgPatternEdit_P->LoadValue();

		}

	
		//SetupMgr->RecipePath.ChangeModel( szName );
		
		//LoadRecipe();
		//FileMgr.WriteSystemLogEvent(_T("Recipe Open Click"));
		pMainFrm->AddLogData(_T("Recipe Open Click"));
		
	}
}

// 레시피 저장 버튼
void CInforRecipeConfigPanel::ClickButtonRecipeSave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CConfirm Confirm;	
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();

	//TCHAR szName[MAX_PATH];
	CString strTemp = TEXT( "Would you like to Save : ");

	strTemp.Append( RecipeMgr->RecipePath.GetSelectedModle() );
	strTemp.Append( TEXT(" ?") );

	Confirm.SetCaption( strTemp, FALSE, CConfirm::E_QUESTION );

	if( Confirm.DoModal() == IDOK )
	{
		_iniUtil.SetRecipe( RecipeMgr->RecipePath.GetSelectedModle()); 

		if(m_patternMode == "SDI")
			m_pDlgPatternEdit_S->UpDatePattern(RecipeMgr->RecipePath.GetSelectedModle());
		else if(m_patternMode == "SDI_POUCH")
			m_pDlgPatternEdit_P->UpDatePattern(RecipeMgr->RecipePath.GetSelectedModle());

		// Field, Param 저장도 같이
		//m_pDlgScannerParameter->SaveIniData();
		/*_iniUtil.SaveParameterIni(_T("HEAD1"), patternPath, HEAD1Param);
		_iniUtil.SaveParameterIni(_T("HEAD2"), patternPath, HEAD2Param);*/
	}	
	OpenRecipeList();
}


void CInforRecipeConfigPanel::ClickButtonRecipeCreate()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CConfirm Confirm;
	CString strTemp = TEXT( "Would you like to Create New Recipe ? ");
	Confirm.SetCaption( strTemp, FALSE, CConfirm::E_QUESTION );

	if( Confirm.DoModal() == IDOK )
	{
		
		CAlphaKeyPad AlphaKeyPad;
		AlphaKeyPad.SetStrOldData(_T(""));
		if( AlphaKeyPad.DoModal() == IDOK )
		{
			CString strTemp = AlphaKeyPad.m_strNewData;
			
			RecipeMgr->RecipePath.NewItem( (LPTSTR)(LPCTSTR) strTemp );
			RecipeMgr->RecipePath.ChangeModel( (LPTSTR)(LPCTSTR)strTemp );
			OpenRecipeList();

			// XML 에도 동일하게 레시피 만들어주기
			// 제목 strTemp
			// 테스트용으로 레시피 만드는건데 XML 만드는게 맞나? - 일단 보류

		}
	}	
}


void CInforRecipeConfigPanel::ClickButton()
{
	// 레시피 삭제
	// XML 파일도 같이 삭제해야 함
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	IniUtil _iniutil;
	CFileDoc fd;
	CString strDeleteRecipeName, deleteMES;
	CString strPath = fd.GetCurrentDirectoryA();
	CConfirm Confirm;
	CString strTemp = TEXT( "Would you like to delete Selected Item : ");

	CString strLastRecipe = _T("");
	CString sitePath = _iniutil.ReplacePathVariables(_iniutil.PATH_INI_SITE);
	_iniutil.LoadStringValueByKey(_T("Settings"),_T("LastRecipe"), sitePath, strLastRecipe);

	m_iRecipeList.GetCurSel(); // Index
	m_iRecipeList.GetText(m_iRecipeList.GetCurSel(), strDeleteRecipeName); // 현재 클릭한 레시피 제목

	strTemp.Append( strDeleteRecipeName );
	//strTemp.Append( RecipeMgr->RecipePath.GetSelectedModle() );
	strTemp.Append( TEXT(" ?") );

	Confirm.SetCaption( strTemp, FALSE, CConfirm::E_QUESTION );

	// 현재적용중 인지 및 마지막 다운로드 레시피인지 체크
	// 해당된다면 삭제 못하게 -> 권한체크 후 삭제할 수 있도록
	if( strDeleteRecipeName != RecipeMgr->RecipePath.GetSelectedModle() && strDeleteRecipeName != strLastRecipe )
	{
		if( Confirm.DoModal() ==  IDOK )
		{	
			// 삭제할때 MES\\PARAM\\ 폴더에 같은 레시피도 삭제 해야함
			RecipeMgr->RecipePath.DeleteItem( strDeleteRecipeName.GetBuffer() ); // 현재 적용된 레시피를 삭제하려함 -> 클릭한 레시피 기준으로 변경해야함
			deleteMES.Format("%s%s%s%s", strPath, "\\MES\\PARAM\\", strDeleteRecipeName, ".xml");
			BOOL deleteSuccessMES = ::DeleteFile(deleteMES); // XML 파일 삭제
			CString strTemp;
			OpenRecipeList();
		}
	} else
	{
		// 현재 적용중 레시피
	}
}


void CInforRecipeConfigPanel::ClickButtonRecipeChangeName()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CConfirm Confirm;
	CString strTemp = TEXT( "Would you like to Change Name Recipe : ");
	strTemp.Append( RecipeMgr->RecipePath.GetSelectedModle() );

	Confirm.SetCaption( strTemp, FALSE, CConfirm::E_QUESTION );

	if( Confirm.DoModal() ==  IDOK )
	{	
		CAlphaKeyPad AlphaKeyPad;
		AlphaKeyPad.SetStrOldData(RecipeMgr->RecipePath.GetSelectedModle());
		if( AlphaKeyPad.DoModal() == IDOK )
		{
			CString strNew = AlphaKeyPad.m_strNewData;
			RecipeMgr->RecipePath.ChangeName( (LPTSTR)(LPCTSTR)strNew );

			OpenRecipeList();
		}
	}
}

void CInforRecipeConfigPanel::OnBnClickedRadioRecipeView(UINT msg)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*switch (msg)
	{
	case IDC_RADIO_RECIPE_MOTION:
		m_pDlgRecipeMotion->ShowWindow(SW_SHOW); 
		m_pDlgRecipeLaser->ShowWindow(SW_HIDE);
		m_pDlgRecipeSocket->ShowWindow(SW_HIDE);
		m_pDlgRecipeVision->ShowWindow(SW_HIDE);
		break;

	case IDC_RADIO_RECIPE_LASER:
		m_pDlgRecipeMotion->ShowWindow(SW_HIDE); 
		m_pDlgRecipeLaser->ShowWindow(SW_SHOW);
		m_pDlgRecipeSocket->ShowWindow(SW_HIDE);
		m_pDlgRecipeVision->ShowWindow(SW_HIDE);
		break;

	case IDC_RADIO_RECIPE_SOCKET:
		m_pDlgRecipeMotion->ShowWindow(SW_HIDE); 
		m_pDlgRecipeLaser->ShowWindow(SW_HIDE);
		m_pDlgRecipeSocket->ShowWindow(SW_SHOW);
		m_pDlgRecipeVision->ShowWindow(SW_HIDE);
		break;

	case IDC_RADIO_RECIPE_VISION:
		m_pDlgRecipeMotion->ShowWindow(SW_HIDE); 
		m_pDlgRecipeLaser->ShowWindow(SW_HIDE);
		m_pDlgRecipeSocket->ShowWindow(SW_HIDE);
		m_pDlgRecipeVision->ShowWindow(SW_SHOW);
		break;



	default:
		break;
	}*/
}


void CInforRecipeConfigPanel::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CProjectBaseView::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(bShow)
	{

	}
}


void CInforRecipeConfigPanel::ClickCtpushSettingPath()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//m_DlgRecipePath.DoModal();
}


BOOL CInforRecipeConfigPanel::OnEraseBkgnd(CDC* pDC)
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


void CInforRecipeConfigPanel::OnBnClickedRadioRecipeMotion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CInforRecipeConfigPanel::OnStnClickedStaticRecipeRect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

