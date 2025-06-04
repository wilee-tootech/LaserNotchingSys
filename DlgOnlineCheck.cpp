// DlgOnlineCheck.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgOnlineCheck.h"
#include "afxdialogex.h"


// CDlgOnlineCheck 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgOnlineCheck, CDialogEx)

CDlgOnlineCheck::CDlgOnlineCheck(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgOnlineCheck::IDD, pParent)
{

}

CDlgOnlineCheck::~CDlgOnlineCheck()
{
}

void CDlgOnlineCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgOnlineCheck, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgOnlineCheck::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgOnlineCheck 메시지 처리기입니다.


void CDlgOnlineCheck::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
