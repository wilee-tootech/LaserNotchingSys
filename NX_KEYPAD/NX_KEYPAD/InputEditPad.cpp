// InputEditPad.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "InputEditPad.h"
#include "afxdialogex.h"
#include "ExtDllState.h"
#include "./EXTERN/cttextctrl.h"
#include "resource.h"


// CInputEditPad ��ȭ �����Դϴ�.
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


// CInputEditPad �޽��� ó�����Դϴ�.


void CInputEditPad::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CExtDllState State;
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CExtDllState State;
	GetDlgItemText(IDD_EDIT_NEW_DATA,m_strNewData);
	OnOK();
}


void CInputEditPad::ClickCtpushctrlCancel()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CExtDllState State;
	OnCancel();
}


INT_PTR CInputEditPad::DoModal()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CExtDllState State;
	return CDialogEx::DoModal();
}


BOOL CInputEditPad::OnInitDialog()
{
	CExtDllState State;

	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

BOOL CInputEditPad::Create(CWnd* pParentWnd)
{
	CExtDllState State;
	return Create(MAKEINTRESOURCE(IDD_INPUT_EDIT_DLG),pParentWnd);
}

BOOL CInputEditPad::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CExtDllState State;
	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


HBRUSH CInputEditPad::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}
