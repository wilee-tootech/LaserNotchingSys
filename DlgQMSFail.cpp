// DlgQMSFail.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgQMSFail.h"
#include "afxdialogex.h"


// CDlgQMSFail ��ȭ �����Դϴ�.

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


// CDlgQMSFail �޽��� ó�����Դϴ�.


void CDlgQMSFail::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}
