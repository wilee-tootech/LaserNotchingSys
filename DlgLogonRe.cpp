// DlgLogonRe.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgLogonRe.h"
#include "afxdialogex.h"


// CDlgLogonRe ��ȭ �����Դϴ�.

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


// CDlgLogonRe �޽��� ó�����Դϴ�.


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