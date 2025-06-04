// DlgWaitForMES.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgWaitForMES.h"
#include "afxdialogex.h"


// CDlgWaitForMES 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgWaitForMES, CDialogEx)

CDlgWaitForMES::CDlgWaitForMES(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgWaitForMES::IDD, pParent)
{

}

CDlgWaitForMES::~CDlgWaitForMES()
{
}

void CDlgWaitForMES::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgWaitForMES, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CDlgWaitForMES::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgWaitForMES::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgWaitForMES 메시지 처리기입니다.


void CDlgWaitForMES::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CDlgWaitForMES::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

void CDlgWaitForMES::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) // 타이머 ID
    {
        OnCancel(); // 대화 상자 닫기
        KillTimer(1); // 타이머 중지
    }

    CDialogEx::OnTimer(nIDEvent);
}

BOOL CDlgWaitForMES::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    CenterWindow();

    return TRUE;
}
