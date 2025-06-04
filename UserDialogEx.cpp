// UserDialogEx.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "../BeamEditor6.h"
#include "UserDialogEx.h"
#include "afxdialogex.h"

#include "../EXTERN/CColorDefine.h"



// CUserDialogEx ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUserDialogEx, CDialogEx)

CUserDialogEx::CUserDialogEx(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserDialogEx::IDD, pParent)
{

}

CUserDialogEx::CUserDialogEx(int IDD, CWnd* pParent)
	: CDialogEx(IDD, pParent)
{
	
}

CUserDialogEx::~CUserDialogEx()
{
}

void CUserDialogEx::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserDialogEx, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CUserDialogEx �޽��� ó�����Դϴ�.


HBRUSH CUserDialogEx::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.

	//
	// #define CTLCOLOR_MSGBOX         0
	// #define CTLCOLOR_EDIT           1
	// #define CTLCOLOR_LISTBOX        2
	// #define CTLCOLOR_BTN            3
	// #define CTLCOLOR_DLG            4
	// #define CTLCOLOR_SCROLLBAR      5
	// #define CTLCOLOR_STATIC         6


	//
	// #define WHITE_BRUSH         0
	// #define LTGRAY_BRUSH        1
	// #define GRAY_BRUSH          2
	// #define DKGRAY_BRUSH        3
	// #define BLACK_BRUSH         4
	// #define NULL_BRUSH          5
	// #define HOLLOW_BRUSH        NULL_BRUSH
	// #define WHITE_PEN           6
	// #define BLACK_PEN           7
	// #define NULL_PEN            8
	// #define OEM_FIXED_FONT      10
	// #define ANSI_FIXED_FONT     11
	// #define ANSI_VAR_FONT       12
	// #define SYSTEM_FONT         13
	// #define DEVICE_DEFAULT_FONT 14
	// #define DEFAULT_PALETTE     15
	// #define SYSTEM_FIXED_FONT   16

	//
	switch (nCtlColor)
	{

	case CTLCOLOR_DLG:
		if(*pWnd == *this)
		{
			//hbr = static_cast<HBRUSH>(GetStockObject((2)));
		}
		break;

	case CTLCOLOR_STATIC:
		{
			pDC->SetTextColor(RGB(55, 82, 110));
			pDC->SetBkMode(TRANSPARENT);
			hbr = static_cast<HBRUSH>(GetStockObject((2)));
		}
		break;

		// 	case CTLCOLOR_BTN:
		// 		{
		// 			pDC->SetBkMode(TRANSPARENT);
		// 			hbr = static_cast<HBRUSH>(GetStockObject((1)));
		// 		}
		// 		break;

	}

	return hbr;
}


BOOL CUserDialogEx::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rect;

	GetClientRect(&rect);

	CBrush myBrush(CustomColor::colorItemBackGraund);    // dialog background color <- ��� �ٲٸ� ��.

	CBrush *pOld = pDC->SelectObject(&myBrush);

	BOOL bRes  = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);

	pDC->SelectObject(pOld);    // restore old brush

	return bRes;                // CDialog::OnEraseBkgnd(pDC);

	//return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL CUserDialogEx::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

// 	ModifyStyle(WS_BORDER, WS_CLIPCHILDREN); //Remove the titilebar from the frame using the ModifyStyle
// 	ModifyStyleEx(WS_EX_CLIENTEDGE,0);			//Remove the border

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

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CUserDialogEx::OnNcPaint()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnNcPaint()��(��) ȣ������ ���ʽÿ�.

	//����� Dlg �Ӽ� Border Thin & Client Eege
	CDC* pDC = GetWindowDC();

	int nFrm = 5;
	CRect rcWindow;
	GetWindowRect( &rcWindow );

	OffsetRect(&rcWindow, -rcWindow.left, -rcWindow.top );

	//Paint the frame
	pDC->FillSolidRect(rcWindow, RGB(128, 128, 128));

	ReleaseDC( pDC );
}


void CUserDialogEx::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CRect rt;
	GetWindowRect(&rt);
	//GetWindowRect( &rt );

	CRgn rgn;
	rgn.CreateRoundRectRgn(0,0,rt.Width(),rt.Height(), 0, 0);
	SetWindowRgn((HRGN)rgn, TRUE);
}
