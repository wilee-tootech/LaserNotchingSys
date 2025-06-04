// DlgRecipeDeleteCheck.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgRecipeDeleteCheck.h"
#include "afxdialogex.h"
#include "stdafx.h"
#include "BeamEditor6.h"
#include "afxdialogex.h"
#include "Device.h"
#include "TransUnit.h"
#include "DlgUserLogin.h"
#include "Include\EXTERN\cttextctrl.h"
#include "DlgDualScannerParameter.h"
#include "FieldParameter.h"
#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소
#include <afxext.h>         // MFC 확장
#include <afxcmn.h>         // Windows 공통 컨트롤에 대한 MFC 지원
#include <afxdialogex.h>
#include <atlfile.h> 
#include <afx.h>
#include <cstring>
#include <vector>
#include "MainFrm.h"
#include "Control\fpspread8.h"
#include "PointerContainer.h"
#include "DlgDeleteRecipeSucc.h"
#include "WriteLog.h"
#include "InfoMESPanel.h"
#include "./RECIPE_MODULE/RecipeManager.h"


// CDlgRecipeDeleteCheck 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgRecipeDeleteCheck, CDialogEx)

CDlgRecipeDeleteCheck::CDlgRecipeDeleteCheck(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRecipeDeleteCheck::IDD, pParent)
{

}

CDlgRecipeDeleteCheck::~CDlgRecipeDeleteCheck()
{
}

void CDlgRecipeDeleteCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRecipeDeleteCheck, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgRecipeDeleteCheck::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgRecipeDeleteCheck::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgRecipeDeleteCheck 메시지 처리기입니다.


void CDlgRecipeDeleteCheck::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DeleteRecipe();
	CDialogEx::OnOK();
}


void CDlgRecipeDeleteCheck::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

BOOL CDlgRecipeDeleteCheck::DeleteRecipe()
{
	BOOL deleteSuccess;
	deleteSuccess = FALSE;

	CFileDoc fd;
	CString strPath = fd.GetCurrentDirectoryA();
	CString folderPath = _T(strPath + "\\MES\\PARAM\\");
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	//CInfoMESPanel* pInfoMES = CInfoMESPanel::GetInstance();

	//CDlgMES* pDlgMES = pFrame->GetDlgMES();
	//pDlgMES->RecipeViewInIt();

	CString deleteMES;
	deleteMES.Format("%s%s%s%s", strPath, "\\MES\\PARAM\\", m_strSelectRecipe, ".xml");
	// deleteMrk.Format("%s%s%s%s", strPath, "\\mrk\\", m_strSelectRecipe, ".mrk");

	BOOL deleteSuccessMES = ::DeleteFile(deleteMES);
	if(deleteSuccessMES)
	{
		RecipeMgr->RecipePath.DeleteItem( m_strSelectRecipe.GetBuffer() );
	}
	CFileFind finder;
	BOOL bWorking = finder.FindFile(folderPath + "\\*.xml");
	int fileCount = 0;

	//// 파일을 모두 찾을때까지 반복
	//while (bWorking)
	//{
	//	bWorking = finder.FindNextFile();
	//	if (!finder.IsDots() && !finder.IsDirectory())
	//	{
	//		fileCount++;
	//	}
	//}
	//finder.Close();

	//// sort 위로 정렬
	//// 파일의 제목만 배열로 불러오기
	//CStringArray fileNames;
	//bWorking = finder.FindFile(folderPath + "\\*.xml");

	//while (bWorking)
	//{
	//	bWorking = finder.FindNextFile();
	//	if (!finder.IsDots() && !finder.IsDirectory())
	//	{
	//		fileNames.Add(finder.GetFileName());
	//	}
	//}
	//finder.Close();


	if(deleteSuccessMES)
	{
		// 삭제 로그 남기고
		CWriteLog* log = NULL;
		log->WriteString("OnFileDelete() - " + m_strSelectRecipe);

		// 둘다 삭제 성공시 삭제 메시지 띄우기
		CDlgDeleteRecipeSucc* pDlgRecipeDeleteCheck = new CDlgDeleteRecipeSucc();
		if (!::IsWindow(pDlgRecipeDeleteCheck->m_hWnd))
		{
			pDlgRecipeDeleteCheck->Create(IDD_DLG_SUCC_DELETE);  // 다이얼로그 생성
			pDlgRecipeDeleteCheck->ShowWindow(SW_HIDE);          // 처음에는 숨김
		}
	}
	return deleteSuccessMES;
}

BOOL CDlgRecipeDeleteCheck::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CenterWindow();

	return TRUE;
}
	
