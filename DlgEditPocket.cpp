// DlgEditPocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgEditPocket.h"
#include "afxdialogex.h"


// CDlgEditPocket ��ȭ �����Դϴ�.

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


// CDlgEditPocket �޽��� ó�����Դϴ�.


void CDlgEditPocket::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}
