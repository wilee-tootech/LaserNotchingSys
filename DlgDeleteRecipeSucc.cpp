// DlgDeleteRecipeSucc.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgDeleteRecipeSucc.h"
#include "afxdialogex.h"


// CDlgDeleteRecipeSucc ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgDeleteRecipeSucc, CDialogEx)

CDlgDeleteRecipeSucc::CDlgDeleteRecipeSucc(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDeleteRecipeSucc::IDD, pParent)
{

}

CDlgDeleteRecipeSucc::~CDlgDeleteRecipeSucc()
{
}

void CDlgDeleteRecipeSucc::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDeleteRecipeSucc, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgDeleteRecipeSucc::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgDeleteRecipeSucc �޽��� ó�����Դϴ�.


void CDlgDeleteRecipeSucc::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}

BOOL CDlgDeleteRecipeSucc::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CenterWindow();

	return TRUE;
}
	
