// RecipeChange.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "RecipeChange.h"
#include "afxdialogex.h"


// CRecipeChange ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRecipeChange, CDialogEx)

CRecipeChange::CRecipeChange(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRecipeChange::IDD, pParent)
{

}

CRecipeChange::~CRecipeChange()
{
}

void CRecipeChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRecipeChange, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRecipeChange::OnBnClickedOk)
END_MESSAGE_MAP()


// CRecipeChange �޽��� ó�����Դϴ�.


void CRecipeChange::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}
