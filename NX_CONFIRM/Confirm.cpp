// Confirm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Confirm.h"
#include "afxdialogex.h"
#include "ExtDllState.h"
#include "resource.h"

#include "./EXTERN/cttextctrl.h"
#include "./EXTERN/FileMgr.h"

// CConfirm ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CConfirm, CDialogEx)

CConfirm::CConfirm(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONFIRM, pParent)
{
	CExtDllState Stats;
}

CConfirm::~CConfirm()
{
	CExtDllState Stats;
}

void CConfirm::DoDataExchange(CDataExchange* pDX)
{
	CExtDllState Stats;
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CConfirm, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CConfirm �޽��� ó�����Դϴ�.

void CConfirm::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CExtDllState Stats;
	CDialogEx::OnShowWindow(bShow, nStatus);

	if( m_bOnlyOk )
		GetDlgItem( IDC_BUTTON_CONFIRM_NO )->EnableWindow( false );
	else 
		GetDlgItem( IDC_BUTTON_CONFIRM_NO )->EnableWindow( true );

	CCttextctrl* cttext;
	cttext = (CCttextctrl*)GetDlgItem(IDC_CONFIRM_CAPTION2);
	cttext->SetForeColor(m_stTitle.m_ColorTilte);

	CStatic* StaticPiture;
	StaticPiture = (CStatic*)GetDlgItem(IDC_STATIC_PICTURE);

	CImage Image;

	if(!Image.IsNull())
		Image.Destroy();

	Image.Load(m_stTitle.m_strImagePath);

	StaticPiture->SetBitmap(Image);
	

	GetDlgItem( IDC_CONFIRM_CAPTION2 )->SetWindowText( m_stTitle.m_strTitle );

// 	cttext = (CCttextctrl*)GetDlgItem(IDC_CONFIRM_CAPTION);
// 	cttext->SetForeColor(m_ColorCaption);

	GetDlgItem( IDC_CONFIRM_CAPTION )->SetWindowText( m_strCaption );

	if(!Image.IsNull())
		Image.Destroy();
}


BEGIN_EVENTSINK_MAP(CConfirm, CDialogEx)
	ON_EVENT(CConfirm, IDC_BUTTON_CONFIRM_YES, DISPID_CLICK, CConfirm::ClickButtonConfirmYes, VTS_NONE)
	ON_EVENT(CConfirm, IDC_BUTTON_CONFIRM_NO, DISPID_CLICK, CConfirm::ClickButtonConfirmNo, VTS_NONE)
END_EVENTSINK_MAP()

void CConfirm::ClickButtonConfirmYes()
{
	CExtDllState Stats;
	OnOK();
}

void CConfirm::ClickButtonConfirmNo()
{
	CExtDllState Stats;
	OnCancel();
}

void CConfirm::SetCaption( CString strTemp, bool bOnlyOk, /*COLORREF a_ColorCaption,*/ UINT a_MsgStatus )
{
	CExtDllState Stats;
	m_strCaption = strTemp;	
	
	m_bOnlyOk = bOnlyOk;

	//m_ColorCaption = a_ColorCaption;

	//////////////////////////////////////////////////////////////////////////
	CFileMgr* FileMgr = new CFileMgr;
	CString strImgPath = TEXT("");
	strImgPath = FileMgr->GetNowExePath();
	delete FileMgr;

	switch (a_MsgStatus)
	{

	case E_NONE:
		m_stTitle.m_strImagePath			= _T("");
		m_stTitle.m_strTitle				= _T("");
		m_stTitle.m_ColorTilte				= DEF_COLOR_NONE;
		break;

	case E_QUESTION:
		m_stTitle.m_strImagePath		    = strImgPath = FileMgr->GetNowExePath() + DEF_IMAGE_QUESTION;
		m_stTitle.m_strTitle				= _T("QUESTION");
		m_stTitle.m_ColorTilte				= DEF_COLOR_QUESTION;
		break;

	case E_WARNING:
		m_stTitle.m_strImagePath		    = strImgPath = FileMgr->GetNowExePath() + DEF_IMAGE_WARNING;
		m_stTitle.m_strTitle				= _T("WARNING");
		m_stTitle.m_ColorTilte				= DEF_COLOR_WARNING;
		break;

	case E_ERROR:
		m_stTitle.m_strImagePath		    = strImgPath = FileMgr->GetNowExePath() + DEF_IMAGE_ERROR;
		m_stTitle.m_strTitle				= _T("ERROR");
		m_stTitle.m_ColorTilte				= DEF_COLOR_ERROR;
		break;

	}

}

INT_PTR CConfirm::DoModal()
{
	CExtDllState Stats;
	
	return CDialogEx::DoModal();
}
BOOL CConfirm::Create(CWnd* pParentWnd /* = NULL */)
{
	return Create(MAKEINTRESOURCE(IDD_CONFIRM),pParentWnd);
}
BOOL CConfirm::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CExtDllState State;
	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


BOOL CConfirm::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CConfirm::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
// 	TCHAR szBuff[MAX_PATH] = { 0, };
// 
// 	CFileMgr* FileMgr = new CFileMgr;
// 	CString strImgPath = TEXT("");
// 	strImgPath = FileMgr->GetNowExePath();
// 	delete FileMgr;
// 
// 	//}}
// 	CDC MemDC;
// 	HBITMAP hSrcImage, hOldSrcImage;
// 	int bx, by;
// 	BITMAP bitSize;
// 	CRect rt;
// 	CStatic* pLoadImg = (CStatic*)GetDlgItem(IDC_STATIC_PICTURE);
// 	pLoadImg->GetWindowRect(&rt);
// 	ScreenToClient(&rt);
// 
// 	MemDC.CreateCompatibleDC(&dc);
// 
// 	strImgPath = FileMgr->GetNowExePath();
// 	PathRemoveFileSpec((LPTSTR)(LPCTSTR)strImgPath);
// 	_stprintf_s(szBuff, _T("%s\\%s"),(LPTSTR)(LPCTSTR)strImgPath, (LPSTR)(LPCTSTR)m_stTitle.m_strImagePath);
// 
// 	hSrcImage = (HBITMAP)::LoadImage(
// 		AfxGetInstanceHandle(),
// 		szBuff,
// 		IMAGE_BITMAP,
// 		0,
// 		0,
// 		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE 
// 		);
// 
// 	dc.SetStretchBltMode(COLORONCOLOR);
// 	hOldSrcImage = (HBITMAP)MemDC.SelectObject(hSrcImage);
// 	GetObject(hSrcImage,sizeof(BITMAP), &bitSize);
// 
// 	bx = bitSize.bmWidth;
// 	by = bitSize.bmHeight;
// 
// 
// 	dc.TransparentBlt(rt.left,
// 		rt.top,
// 		rt.Width(),
// 		rt.Height(),
// 		&MemDC,
// 		0,
// 		0,
// 		bx,
// 		by,
// 		RGB(255,255,255));
// 
// 	MemDC.SelectObject(hOldSrcImage);
// 
// 	DeleteObject(hSrcImage);
// 	DeleteObject(MemDC);
}


BOOL CConfirm::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
