// DlgQMSFail.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgQMSFail.h"
#include "afxdialogex.h"


// CDlgQMSFail 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgQMSFail, CDialogEx)

CDlgQMSFail::CDlgQMSFail(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgQMSFail::IDD, pParent)
{

}

CDlgQMSFail::~CDlgQMSFail()
{
}

void CDlgQMSFail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgQMSFail, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgQMSFail::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgQMSFail 메시지 처리기입니다.


void CDlgQMSFail::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
