// RecipeDownloadSucc.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "RecipeDownloadSucc.h"
#include "afxdialogex.h"


// CRecipeDownloadSucc ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRecipeDownloadSucc, CDialogEx)

CRecipeDownloadSucc::CRecipeDownloadSucc(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRecipeDownloadSucc::IDD, pParent)
{

}

CRecipeDownloadSucc::~CRecipeDownloadSucc()
{
}

void CRecipeDownloadSucc::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRecipeDownloadSucc, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRecipeDownloadSucc::OnBnClickedOk)
END_MESSAGE_MAP()


// CRecipeDownloadSucc �޽��� ó�����Դϴ�.


void CRecipeDownloadSucc::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ShowWindow(SW_HIDE);
	CDialogEx::OnOK();
}

BOOL CRecipeDownloadSucc::OnInitDialog()
{
    CDialog::OnInitDialog();
	CenterWindow();
    return TRUE; // TRUE�� ��ȯ�ϸ� ���̾�αװ� ��� ����˴ϴ�.
}