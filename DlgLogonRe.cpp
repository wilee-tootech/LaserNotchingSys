// DlgLogonRe.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgLogonRe.h"
#include "afxdialogex.h"


// CDlgLogonRe 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgLogonRe, CDialogEx)

CDlgLogonRe::CDlgLogonRe(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLogonRe::IDD, pParent)
{

}

CDlgLogonRe::~CDlgLogonRe()
{
}

void CDlgLogonRe::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgLogonRe, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgLogonRe::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgLogonRe 메시지 처리기입니다.


void CDlgLogonRe::OnBnClickedOk()
{
	CDialogEx::OnOK();
}




void CDlgLogonRe::FailContentTextPutIt()
{
}

void CDlgLogonRe::SuccContentTextPutIt()
{
}