// RecipeChangeFail.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "RecipeChangeFail.h"
#include "afxdialogex.h"


// CRecipeChangeFail 대화 상자입니다.

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


// CRecipeChangeFail 메시지 처리기입니다.


void CRecipeChangeFail::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
