// DlgOnlineCheck.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgOnlineCheck.h"
#include "afxdialogex.h"


// CDlgOnlineCheck ��ȭ �����Դϴ�.

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


// CDlgOnlineCheck �޽��� ó�����Դϴ�.


void CDlgOnlineCheck::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}
