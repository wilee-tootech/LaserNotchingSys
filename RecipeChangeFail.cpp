// RecipeChangeFail.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "RecipeChangeFail.h"
#include "afxdialogex.h"


// CRecipeChangeFail ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRecipeChangeFail, CDialogEx)

CRecipeChangeFail::CRecipeChangeFail(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRecipeChangeFail::IDD, pParent)
{

}

CRecipeChangeFail::~CRecipeChangeFail()
{
}

void CRecipeChangeFail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRecipeChangeFail, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRecipeChangeFail::OnBnClickedOk)
END_MESSAGE_MAP()


// CRecipeChangeFail �޽��� ó�����Դϴ�.


void CRecipeChangeFail::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}
