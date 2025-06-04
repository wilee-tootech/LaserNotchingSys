// DlgRecipeDeleteCheck.cpp : ���� �����Դϴ�.
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
#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ���
#include <afxext.h>         // MFC Ȯ��
#include <afxcmn.h>         // Windows ���� ��Ʈ�ѿ� ���� MFC ����
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


// CDlgRecipeDeleteCheck ��ȭ �����Դϴ�.

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


// CDlgRecipeDeleteCheck �޽��� ó�����Դϴ�.


void CDlgRecipeDeleteCheck::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DeleteRecipe();
	CDialogEx::OnOK();
}


void CDlgRecipeDeleteCheck::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	//// ������ ��� ã�������� �ݺ�
	//while (bWorking)
	//{
	//	bWorking = finder.FindNextFile();
	//	if (!finder.IsDots() && !finder.IsDirectory())
	//	{
	//		fileCount++;
	//	}
	//}
	//finder.Close();

	//// sort ���� ����
	//// ������ ���� �迭�� �ҷ�����
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
		// ���� �α� �����
		CWriteLog* log = NULL;
		log->WriteString("OnFileDelete() - " + m_strSelectRecipe);

		// �Ѵ� ���� ������ ���� �޽��� ����
		CDlgDeleteRecipeSucc* pDlgRecipeDeleteCheck = new CDlgDeleteRecipeSucc();
		if (!::IsWindow(pDlgRecipeDeleteCheck->m_hWnd))
		{
			pDlgRecipeDeleteCheck->Create(IDD_DLG_SUCC_DELETE);  // ���̾�α� ����
			pDlgRecipeDeleteCheck->ShowWindow(SW_HIDE);          // ó������ ����
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
	
