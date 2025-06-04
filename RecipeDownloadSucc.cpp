// RecipeDownloadSucc.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "RecipeDownloadSucc.h"
#include "afxdialogex.h"


// CRecipeDownloadSucc 대화 상자입니다.

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


// CRecipeDownloadSucc 메시지 처리기입니다.


void CRecipeDownloadSucc::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
	CDialogEx::OnOK();
}

BOOL CRecipeDownloadSucc::OnInitDialog()
{
    CDialog::OnInitDialog();
	CenterWindow();
    return TRUE; // TRUE를 반환하면 다이얼로그가 계속 실행됩니다.
}