// InputEditPad.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "InputEditPad.h"
#include "afxdialogex.h"
#include "ExtDllState.h"
#include "./EXTERN/cttextctrl.h"
#include "resource.h"


// CInputEditPad 대화 상자입니다.
#define INPUT_EDIT_FONT_SIZE 15L

IMPLEMENT_DYNAMIC(CInputEditPad, CDialogEx)

CInputEditPad::CInputEditPad(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INPUT_EDIT_DLG, pParent)
{
	CExtDllState State;
}

CInputEditPad::~CInputEditPad()
{
	CExtDllState State;
}

void CInputEditPad::DoDataExchange(CDataExchange* pDX)
{
	CExtDllState State;
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDD_EDIT_NEW_DATA, m_editNewData);
}

void CInputEditPad::Init()
{
	CExtDllState State;
	m_strOldData	= TEXT("");
	m_strNewData	= TEXT("");
	
}

BEGIN_MESSAGE_MAP(CInputEditPad, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CInputEditPad 메시지 처리기입니다.


void CInputEditPad::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CExtDllState State;
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(bShow)
	{
		CCttextctrl* pOldData = (CCttextctrl*)GetDlgItem(IDC_CTTEXTCTRL_OLD_DATA);
		pOldData->SetCaption(m_strOldData);

		CRect rtEdit;
		int nVerticalSize;

		m_editNewData.GetRect(rtEdit);
		if((rtEdit.bottom - rtEdit.top) > INPUT_EDIT_FONT_SIZE)
		{
			nVerticalSize = rtEdit.bottom - rtEdit.top - INPUT_EDIT_FONT_SIZE;
			nVerticalSize /= 2;
		}
		else
		{
			nVerticalSize = 2;
		}

		rtEdit.left+=5; 
		rtEdit.right-=5;
		rtEdit.top += nVerticalSize;
		rtEdit.bottom -= nVerticalSize;

		m_editNewData.SetRect(rtEdit);
			
	}
}
BEGIN_EVENTSINK_MAP(CInputEditPad, CDialogEx)
	ON_EVENT(CInputEditPad, IDC_CTPUSHCTRL_APPLY, DISPID_CLICK, CInputEditPad::ClickCtpushctrlApply, VTS_NONE)
	ON_EVENT(CInputEditPad, IDC_CTPUSHCTRL_CANCEL, DISPID_CLICK, CInputEditPad::ClickCtpushctrlCancel, VTS_NONE)
END_EVENTSINK_MAP()


void CInputEditPad::ClickCtpushctrlApply()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CExtDllState State;
	GetDlgItemText(IDD_EDIT_NEW_DATA,m_strNewData);
	OnOK();
}


void CInputEditPad::ClickCtpushctrlCancel()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CExtDllState State;
	OnCancel();
}


INT_PTR CInputEditPad::DoModal()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CExtDllState State;
	return CDialogEx::DoModal();
}


BOOL CInputEditPad::OnInitDialog()
{
	CExtDllState State;

	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	LOGFONT LogFont;

	this->GetFont()->GetLogFont(&LogFont);

	wsprintf(LogFont.lfFaceName, _T("%s"), TEXT("Tahoma"));

	LogFont.lfHeight = INPUT_EDIT_FONT_SIZE;
	LogFont.lfWeight = FW_BOLD;

	CFont Font;
	Font.CreateFontIndirect(&LogFont);

	CWnd* pWnd = this->GetWindow(GW_CHILD);

	while(pWnd)
	{
		pWnd->SetFont(&Font);
		pWnd = pWnd->GetNextWindow();
	}

	Font.Detach();


	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CInputEditPad::Create(CWnd* pParentWnd)
{
	CExtDllState State;
	return Create(MAKEINTRESOURCE(IDD_INPUT_EDIT_DLG),pParentWnd);
}

BOOL CInputEditPad::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CExtDllState State;
	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


HBRUSH CInputEditPad::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
