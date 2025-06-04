// DlgEditPocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgEditPocket.h"
#include "afxdialogex.h"


// CDlgEditPocket 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgEditPocket, CDialogEx)

CDlgEditPocket::CDlgEditPocket(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgEditPocket::IDD, pParent)
{

}

CDlgEditPocket::~CDlgEditPocket()
{
}

void CDlgEditPocket::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgEditPocket, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgEditPocket::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgEditPocket 메시지 처리기입니다.


void CDlgEditPocket::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
