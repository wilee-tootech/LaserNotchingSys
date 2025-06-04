// RecipeChange.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "RecipeChange.h"
#include "afxdialogex.h"


// CRecipeChange 대화 상자입니다.

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


// CRecipeChange 메시지 처리기입니다.


void CRecipeChange::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
