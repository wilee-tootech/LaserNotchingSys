// DlgRecipeDeleteFail.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgRecipeDeleteFail.h"
#include "afxdialogex.h"


// CDlgRecipeDeleteFail ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgRecipeDeleteFail, CDialogEx)

CDlgRecipeDeleteFail::CDlgRecipeDeleteFail(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRecipeDeleteFail::IDD, pParent)
{

}

CDlgRecipeDeleteFail::~CDlgRecipeDeleteFail()
{
}

void CDlgRecipeDeleteFail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRecipeDeleteFail, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgRecipeDeleteFail::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgRecipeDeleteFail �޽��� ó�����Դϴ�.


void CDlgRecipeDeleteFail::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}
